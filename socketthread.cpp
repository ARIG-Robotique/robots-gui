#include <QGuiApplication>
#include "socketthread.h"
#include "robotmodel.h"
#include "paramsmodel.h"

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

        ParamsModel* paramsModel = ParamsModel::getInstance();
        RobotModel* robotModel = RobotModel::getInstance();

        JsonResult result;
        if (query.action == ACTION_ECHO) {
            result.status = RESPONSE_OK;
            result.data = query.data;

        } else if (query.action == ACTION_SET_PARAMS) {
            if (debug) {
                spdlog::info("Réception des paramètres");
            }

            json data = query.data;

            paramsModel->setName(QString::fromStdString(data["name"]));
            paramsModel->setPrimary(data["primary"]);

            QList<TeamAndColor> teams;
            auto rawTeams = data["teams"].get<map<string, string>>();
            for (auto const &t : rawTeams) {
                teams.append(TeamAndColor(QString::fromStdString(t.first), QString::fromStdString(t.second)));
            }
            paramsModel->setTeams(teams);

            QStringList strategies;
            auto rawStrategies = data["strategies"].get<list<string>>();
            for (auto const &s : rawStrategies) {
                strategies.push_back(QString::fromStdString(s));
            }
            paramsModel->setStrategies(strategies);
            robotModel->setStrategy(strategies.at(0));

            QStringList options;
            auto rawOptions = data["options"].get<list<string>>();
            for (auto const &o : rawOptions) {
                options.push_back(QString::fromStdString(o));
                robotModel->setOption(QString::fromStdString(o), false);
            }
            paramsModel->setOptions(options);

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_GET_CONFIG) {
            if (debug) {
                spdlog::info("Demande de récupération d'état");
            }

            result.status = RESPONSE_OK;
            result.data["exit"] = robotModel->getExit();
            if (!robotModel->getTeam().isEmpty()) {
                result.data["team"] = robotModel->getTeam().toStdString();
            }
            if (!robotModel->getStrategy().isEmpty()) {
                result.data["strategy"] = robotModel->getStrategy().toStdString();
            }
            result.data["startCalibration"] = robotModel->getStartCalibration();
            result.data["modeManuel"] = robotModel->getModeManuel();
            result.data["safeAvoidance"] = robotModel->getSafeAvoidance();
            result.data["skipCalageBordure"] = robotModel->getSkipCalageBordure();
            result.data["updatePhoto"] = robotModel->getUpdatePhoto();
            result.data["etalonnageBalise"] = robotModel->getEtalonnageBalise();
            result.data["etalonnageOk"] = robotModel->getEtalonnageOk();
            result.data["twoRobots"] = robotModel->getTwoRobots();
            result.data["options"] = json({});

            QVariantMap::const_iterator i = robotModel->getOptions().constBegin();
            while (i != robotModel->getOptions().constEnd()) {
                result.data["options"][i.key().toStdString()] = i.value().toBool();
                ++i;
            }

        } else if (query.action == ACTION_UPDATE_STATE) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant l'initialisation");
            }

            json data = query.data;

            robotModel->setInMatch(false);
            robotModel->setI2c(data["i2c"]);
            robotModel->setLidar(data["lidar"]);
            robotModel->setAu(data["au"]);
            robotModel->setAlim12v(data["alim12v"]);
            robotModel->setAlim5vp(data["alim5vp"]);
            robotModel->setTirette(data["tirette"]);
            robotModel->setOtherRobot(data["otherRobot"]);
            robotModel->setBalise(data["balise"]);
            if (data["message"].is_null()) {
                robotModel->setMessage("");
            } else {
                robotModel->setMessage(QString::fromStdString(data["message"]));
            }

            if (robotModel->getOtherRobot()) {
                robotModel->setTwoRobots(true);

                if (!paramsModel->getPrimary()) {
                    if (!data["team"].is_null()) {
                        robotModel->setTeam(QString::fromStdString(data["team"]));
                    }
                    if (!data["strategy"].is_null()) {
                        robotModel->setStrategy(QString::fromStdString(data["strategy"]));
                    }

                    for (auto &opt : data["options"].items()) {
                        robotModel->setOption(QString::fromStdString(opt.key()), opt.value());
                    }
                }
            }


            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_MATCH) {
            if (debug) {
                spdlog::info("Reception de mise à jour de l'état du robot pendant le match");
            }

            json data = query.data;

            robotModel->setInMatch(true);
            robotModel->setScore(data["score"]);
            if (data["message"].is_null()) {
                robotModel->setMessage("");
            } else {
                robotModel->setMessage(QString::fromStdString(data["message"]));
            }

            result.status = RESPONSE_OK;

        } else if (query.action == ACTION_UPDATE_PHOTO) {
            if (debug) {
                spdlog::info("Reception d'une photo de la balise");
            }

            json data = query.data;

            robotModel->setUpdatePhoto(false);
            robotModel->setEtalonnageBalise(false);
            if (data["message"].is_null()) {
                robotModel->setPhotoMessage("");
            } else {
                robotModel->setPhotoMessage(QString::fromStdString(data["message"]));
            }
            if (data["photo"].is_null()) {
                robotModel->setPhoto("");
            } else {
                robotModel->setPhoto(QString::fromStdString(data["photo"]));
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
