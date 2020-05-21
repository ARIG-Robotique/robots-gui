#include "robotmodel.h"
#include "common.h"

RobotModel* RobotModel::instance = nullptr;

RobotModel* RobotModel::getInstance() {
    if (instance == nullptr) {
        instance = new RobotModel();
    }
    return instance;
}

QObject* RobotModel::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine)

    auto instance = RobotModel::getInstance();
    engine->setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

RobotModel::RobotModel(QObject *parent) : QObject(parent) {
    // RW
    this->setExit(false);
    this->setTeam(UNKNOWN);
    this->setStrategy(STRAT1);
    this->setStartCalibration(false);
    this->setModeManuel(false);
    this->setSkipCalageBordure(false);
    this->setUpdatePhoto(false);
    this->setEtalonnageBalise(false);

    // RO
    this->setScore(0);
    this->setI2c(false);
    this->setLidar(false);
    this->setInMatch(false);
    this->setAu(false);
    this->setAlim12v(false);
    this->setAlim5vp(false);
    this->setTirette(false);
    this->setPhare(false);
    this->setBalise(false);
    this->setMessage("Démarrage en cours ...");
}

// QML RW datas //
// ------------ //

bool RobotModel::getExit() {
    return this->exit;
}
void RobotModel::setExit(bool exit) {
    this->exit = exit;
    emit exitChanged(exit);
}

RobotModel::Team RobotModel::getTeam() {
    return this->team;
}
void RobotModel::setTeam(Team team) {
    this->team = team;
    emit teamChanged(team);
}

bool RobotModel::getStartCalibration() {
    return this->startCalibration;
}
void RobotModel::setStartCalibration(bool value) {
    this->startCalibration = value;
    emit startCalibrationChanged(value);
}

RobotModel::Strategy RobotModel::getStrategy() {
    return this->strategy;
}
void RobotModel::setStrategy(Strategy strategy) {
    this->strategy = strategy;
    emit strategyChanged(strategy);
}

bool RobotModel::getSkipCalageBordure() {
    return this->skipCalageBordure;
}
void RobotModel::setSkipCalageBordure(bool value) {
    this->skipCalageBordure = value;
    emit skipCalageBordureChanged(value);
}

bool RobotModel::getModeManuel() {
    return this->modeManuel;
}
void RobotModel::setModeManuel(bool value) {
    this->modeManuel = value;
    emit modeManuelChanged(value);
}

bool RobotModel::getUpdatePhoto() {
    return this->updatePhoto;
}
void RobotModel::setUpdatePhoto(bool value) {
    this->updatePhoto = value;
    emit updatePhotoChanged(value);
}

bool RobotModel::getEtalonnageBalise() {
    return this->etalonnageBalise;
}
void RobotModel::setEtalonnageBalise(bool value) {
    this->etalonnageBalise = value;
    emit etalonnageBaliseChanged(value);
}

QList<QPoint> RobotModel::getPosEcueil() {
    return this->posEcueil;
}
void RobotModel::setPosEcueil(QList<QPoint> value) {
    this->posEcueil = value;
    emit posEcueilChanged(value);
}
void RobotModel::setPosEcueil(QJSValue value) {
    QList<QPoint> points;
    unsigned int length = value.property("length").toUInt();
    for (unsigned int i = 0; i < length; i++) {
        points.push_back(value.property(i).toVariant().toPoint());
    }
    setPosEcueil(points);
}

QList<QPoint> RobotModel::getPosBouees() {
    return this->posBouees;
}
void RobotModel::setPosBouees(QList<QPoint> value) {
    this->posBouees = value;
    emit posBoueesChanged(value);
}
void RobotModel::setPosBouees(QJSValue value) {
    QList<QPoint> points;
    unsigned int length = value.property("length").toUInt();
    for (unsigned int i = 0; i < length; i++) {
        points.push_back(value.property(i).toVariant().toPoint());
    }
    setPosBouees(points);
}

// QML RO datas //
// ------------ //

bool RobotModel::getInMatch() {
   return this->inMatch;
}
void RobotModel::setInMatch(bool value) {
    this->inMatch = value;
    emit inMatchChanged(value);
}

bool RobotModel::getI2c() {
    return this->i2c;
}
void RobotModel::setI2c(bool value) {
    this->i2c = value;
    emit i2cChanged(value);
}

bool RobotModel::getLidar() {
    return this->lidar;
}
void RobotModel::setLidar(bool value) {
    this->lidar = value;
    emit lidarChanged(value);
}

bool RobotModel::getAu() {
    return this->au;
}
void RobotModel::setAu(bool value) {
    this->au = value;
    emit auChanged(value);
}

bool RobotModel::getAlim12v(){
    return this->alim12v;
}
void RobotModel::setAlim12v(bool value){
    this->alim12v = value;
    emit alim12vChanged(value);
}

bool RobotModel::getAlim5vp(){
    return this->alim5vp;
}
void RobotModel::setAlim5vp(bool value){
    this->alim5vp = value;
    emit alim5vpChanged(value);
}

bool RobotModel::getTirette() {
    return this->tirette;
}
void RobotModel::setTirette(bool value) {
    this->tirette = value;
    emit tiretteChanged(value);
}

bool RobotModel::getPhare() {
    return this->phare;
}
void RobotModel::setPhare(bool value) {
    this->phare = value;
    emit phareChanged(value);
}

bool RobotModel::getBalise() {
    return this->balise;
}
void RobotModel::setBalise(bool value) {
    this->balise = value;
    emit baliseChanged(value);
}

int RobotModel::getScore(){
    return this->score;
}
void RobotModel::setScore(int value){
    this->score = value;
    emit scoreChanged(value);
}

QString RobotModel::getMessage() {
    return this->message;
}
void RobotModel::setMessage(QString message) {
    this->message = message;
    emit messageChanged(message);
}

QString RobotModel::getPhoto() {
    return this->photo;
}
void RobotModel::setPhoto(QString value) {
    this->photo = value;
    emit photoChanged(value);
}

QList<QString> RobotModel::getCouleurEcueil() {
    return this->couleurEcueil;
}
void RobotModel::setCouleurEcueil(QList<QString> value) {
    this->couleurEcueil = value;
    emit couleurEcueilChanged(value);
}

QList<QString> RobotModel::getCouleurBouees() {
    return this->couleurBouees;
}
void RobotModel::setCouleurBouees(QList<QString> value) {
    this->couleurBouees = value;
    emit couleurBoueesChanged(value);
}
