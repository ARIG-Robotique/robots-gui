#include <QGuiApplication>
#include "socketthread.h"
#include "robotmodel.h"

SocketThread::SocketThread() : QThread() {
    abort = false;
    debug = false;
}
SocketThread::~SocketThread() {
    abort = true;
    debug = false;
}

void SocketThread::setSocketHelper(SocketHelper *helper) {
    this->helper = helper;
}

void SocketThread::abortExecution() {
    abort = true;
}

void SocketThread::run() {
    helper->init();

    bool waitConnection = true;
    while (!abort) {
        if (waitConnection) {
            spdlog::debug("Attente de connexion client ...");
            helper->waitConnection();
            waitConnection = false;
        }

        JsonQuery query = helper->getQuery();
        if (query.action == DATA_INVALID) {
            spdlog::warn("Données invalide, la socket client est fermé ?");
            waitConnection = true;
            continue;
        }

        JsonResult result;
        if (query.action == ACTION_ECHO) {
            result.status = RESPONSE_OK;
            result.data = query.data;

        } else if (query.action == ACTION_GET_CONFIG) {
            if (debug) {
                spdlog::info("Demande de récupération d'état");
            }
            RobotModel* model = RobotModel::getInstance();

            result.status = RESPONSE_OK;
            result.data["exit"] = model->getExit();
            result.data["team"] = model->getTeam();
            result.data["startCalibration"] = model->getStartCalibration();
            result.data["strategy"] = model->getStrategy();
            result.data["modeManuel"] = model->getModeManuel();
            result.data["safeAvoidance"] = model->getSafeAvoidance();
            result.data["skipCalageBordure"] = model->getSkipCalageBordure();
            result.data["deposePartielle"] = model->getDeposePartielle();
            result.data["echangeEcueil"] = model->getEchangeEcueil();
            result.data["updatePhoto"] = model->getUpdatePhoto();
            result.data["etalonnageBalise"] = model->getEtalonnageBalise();
            result.data["twoRobots"] = model->getTwoRobots();

        } else if (query.action == ACTION_UPDATE_STATE) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant l'initialisation");
            }

            json data = query.data;
            RobotModel* model = RobotModel::getInstance();
            model->setInMatch(false);
            model->setI2c(data["i2c"]);
            model->setLidar(data["lidar"]);
            model->setAu(data["au"]);
            model->setAlim12v(data["alim12v"]);
            model->setAlim5vp(data["alim5vp"]);
            model->setTirette(data["tirette"]);
            model->setOtherRobot(data["otherRobot"]);
            model->setBalise(data["balise"]);
            string message = data["message"];
            model->setMessage(message.c_str());

            if (model->getOtherRobot()) {
                model->setTwoRobots(true);
            }

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_MATCH) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant le match");
            }

            json data = query.data;
            RobotModel* model = RobotModel::getInstance();
            model->setInMatch(true);
            model->setScore(data["score"]);
            model->setMessage(QString::fromStdString(data["message"]));

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_PHOTO) {
            if (debug) {
                spdlog::info("Reception d'une photo de la balise");
            }

            json data = query.data;
            RobotModel* model = RobotModel::getInstance();
            model->setUpdatePhoto(false);
            model->setEtalonnageBalise(false);
            if (data["message"].is_null()) {
                model->setPhotoMessage("");
            } else {
                model->setPhotoMessage(QString::fromStdString(data["message"]));
            }
            if (data["photo"].is_null()) {
                model->setPhoto("");
            } else {
                model->setPhoto(QString::fromStdString(data["photo"]));
            }

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_EXIT) {
            spdlog::info("Demande d'arret du programe");
            result.status = RESPONSE_OK;
            abort = true;

        } else {
            spdlog::warn("Action {} non supportée", query.action);
            result.status = RESPONSE_ERROR;
            result.errorMessage = "Action non supportée";
        }

        result.action = query.action;
        helper->sendResponse(result);
    }

    // Fermeture de l'application
    QGuiApplication::exit();
}
