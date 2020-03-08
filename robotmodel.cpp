#include "robotmodel.h"

RobotModel* RobotModel::instance = nullptr;

RobotModel* RobotModel::getInstance() {
    if (instance == nullptr) {
        new RobotModel();
    }
    return instance;
}

RobotModel::RobotModel(QObject *parent) : QObject(parent) {
    if (instance == nullptr) {
        instance = this;
    }

    this->setTeam(UNKNOWN);
    this->setStrategy(STRAT1);
    this->setInMatch(false);
    this->setAu(false);
    this->setAlim12v(false);
    this->setAlim5vp(false);
    this->setAlim5vl(false);
    this->setTirette(false);
    this->setScore(0);
    this->setMessage("Startup IHM");
}

// QML RW datas //
// ------------ //

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

// QML RO datas //
// ------------ //

bool RobotModel::getInMatch() {
   return this->inMatch;
}
void RobotModel::setInMatch(bool value) {
    this->inMatch = value;
    emit inMatchChanged(value);
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

bool RobotModel::getAlim5vl(){
    return this->alim5vl;
}
void RobotModel::setAlim5vl(bool value){
    this->alim5vl = value;
    emit alim5vlChanged(value);
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
