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
            result.data["skipCalageBordure"] = model->getSkipCalageBordure();
            result.data["updatePhoto"] = model->getUpdatePhoto();
            result.data["doubleDepose"] = model->getDoubleDepose();
            result.data["safeAvoidance"] = model->getSafeAvoidance();
            result.data["deposePartielle"] = model->getDeposePartielle();
            result.data["etalonnageBalise"] = model->getEtalonnageBalise();
            result.data["posEcueil"] = json();

            for (const QPoint &pt : model->getPosEcueil()) {
                result.data["posEcueil"].emplace_back(json({pt.x(), pt.y()}));
            }
            if (!model->getPosBouees().empty()) {
                result.data["posBouees"] = json();
                for (const QPoint &pt : model->getPosBouees()) {
                    result.data["posBouees"].emplace_back(json({pt.x(), pt.y()}));
                }
            }

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
            model->setPhare(data["phare"]);
            model->setBalise(data["balise"]);
            string message = data["message"];
            model->setMessage(message.c_str());

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
            model->setPhoto(QString::fromStdString(data));

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_ETALONNAGE) {
            if (debug) {
                spdlog::info("Reception du résultat d'étalonnage");
            }

            json data = query.data;
            RobotModel* model = RobotModel::getInstance();

            QList<QString> ecueil;
            for (auto &c : data["ecueil"]) {
                ecueil.push_back(QString::fromStdString(c));
            }
            QList<QString> bouees;
            if (data["bouees"] != nullptr) {
                for (auto &c : data["bouees"]) {
                    bouees.push_back(QString::fromStdString(c));
                }
            }

            model->setCouleurEcueil(ecueil);
            model->setCouleurBouees(bouees);
            model->setEtalonnageBalise(false);

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
