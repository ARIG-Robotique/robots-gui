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
            result.datas = query.datas;

        } else if (query.action == ACTION_GET_CONFIG) {
            if (debug) {
                spdlog::info("Demande de récupération d'état");
            }
            RobotModel* model = RobotModel::getInstance();

            result.status = RESPONSE_OK;
            result.datas["exit"] = model->getExit();
            result.datas["team"] = model->getTeam();
            result.datas["startCalibration"] = model->getStartCalibration();
            result.datas["strategy"] = model->getStrategy();
            result.datas["modeManuel"] = model->getModeManuel();
            result.datas["skipCalageBordure"] = model->getSkipCalageBordure();
            result.datas["updatePhoto"] = model->getUpdatePhoto();
            result.datas["doubleDepose"] = model->getDoubleDepose();
            result.datas["safeAvoidance"] = model->getSafeAvoidance();
            result.datas["deposePartielle"] = model->getDeposePartielle();
            result.datas["etalonnageBalise"] = model->getEtalonnageBalise();
            result.datas["posEcueil"] = json();

            for (const QPoint &pt : model->getPosEcueil()) {
                result.datas["posEcueil"].emplace_back(json({pt.x(), pt.y()}));
            }
            if (!model->getPosBouees().empty()) {
                result.datas["posBouees"] = json();
                for (const QPoint &pt : model->getPosBouees()) {
                    result.datas["posBouees"].emplace_back(json({pt.x(), pt.y()}));
                }
            }

        } else if (query.action == ACTION_UPDATE_STATE) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant l'initialisation");
            }

            json datas = query.datas;
            RobotModel* model = RobotModel::getInstance();
            model->setInMatch(false);
            model->setI2c(datas["i2c"]);
            model->setLidar(datas["lidar"]);
            model->setAu(datas["au"]);
            model->setAlim12v(datas["alim12v"]);
            model->setAlim5vp(datas["alim5vp"]);
            model->setTirette(datas["tirette"]);
            model->setPhare(datas["phare"]);
            model->setBalise(datas["balise"]);
            string message = datas["message"];
            model->setMessage(message.c_str());

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_MATCH) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant le match");
            }

            json datas = query.datas;
            RobotModel* model = RobotModel::getInstance();
            model->setInMatch(true);
            model->setScore(datas["score"]);
            model->setMessage(QString::fromStdString(datas["message"]));

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_PHOTO) {
            if (debug) {
                spdlog::info("Reception d'une photo de la balise");
            }

            json datas = query.datas;
            RobotModel* model = RobotModel::getInstance();
            model->setUpdatePhoto(false);
            model->setPhoto(QString::fromStdString(datas));

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_ETALONNAGE) {
            if (debug) {
                spdlog::info("Reception du résultat d'étalonnage");
            }

            json datas = query.datas;
            RobotModel* model = RobotModel::getInstance();

            QList<QString> ecueil;
            for (auto &c : datas["ecueil"]) {
                ecueil.push_back(QString::fromStdString(c));
            }
            QList<QString> bouees;
            if (datas["bouees"] != nullptr) {
                for (auto &c : datas["bouees"]) {
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
