#include "paramsmodel.h"
#include "common.h"

ParamsModel* ParamsModel::instance = nullptr;

ParamsModel* ParamsModel::getInstance() {
    if (instance == nullptr) {
        instance = new ParamsModel();
    }
    return instance;
}

ParamsModel::ParamsModel(QObject *parent) : QObject(parent) {
    this->setName("...");
    this->setPrimary(false);
}

QString ParamsModel::getName() {
    return this->name;
}
void ParamsModel::setName(QString name) {
    this->name = name;
    emit nameChanged(name);
}

bool ParamsModel::getPrimary() {
    return this->primary;
}
void ParamsModel::setPrimary(bool primary) {
    this->primary = primary;
    emit primaryChanged(primary);
}

QList<TeamAndColor> ParamsModel::getTeams() {
    return this->teams;
}
void ParamsModel::setTeams(QList<TeamAndColor> teams) {
    this->teams = teams;
    emit teamsChanged(teams);
}

QStringList ParamsModel::getStrategies() {
    return this->strategies;
}
void ParamsModel::setStrategies(QStringList strategies) {
    this->strategies = strategies;
    emit strategiesChanged(strategies);
}

QStringList ParamsModel::getOptions() {
    return this->options;
}
void ParamsModel::setOptions(QStringList options) {
    this->options = options;
    emit optionsChanged(options);
}
