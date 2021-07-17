#ifndef PARAMSMODEL_H
#define PARAMSMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QString>
#include <QPoint>
#include <QMap>

class TeamAndColor
{
    Q_GADGET

    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString color READ getColor)

private:
    QString name, color;

public:
    TeamAndColor() {}
    TeamAndColor(QString _name, QString _color) : name(_name), color(_color) {}

    QString getName() {
        return name;
    }

    QString getColor() {
        return color;
    }

};

Q_DECLARE_METATYPE(TeamAndColor);

class ParamsModel : public QObject
{
    Q_OBJECT

private:
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(bool primary READ getPrimary NOTIFY primaryChanged)
    Q_PROPERTY(QList<TeamAndColor> teams READ getTeams NOTIFY teamsChanged)
    Q_PROPERTY(QStringList strategies READ getStrategies NOTIFY strategiesChanged)
    Q_PROPERTY(QStringList options READ getOptions NOTIFY optionsChanged)

    static ParamsModel* instance;
    ParamsModel(QObject *parent = nullptr);

public:
    static ParamsModel* getInstance();

    QString getName();
    void setName(QString name);

    bool getPrimary();
    void setPrimary(bool primary);

    QList<TeamAndColor> getTeams();
    void setTeams(QList<TeamAndColor> teams);

    QStringList getStrategies();
    void setStrategies(QStringList strategies);

    QStringList getOptions();
    void setOptions(QStringList options);

signals:
    void nameChanged(QString newValue);
    void primaryChanged(bool newValue);
    void teamsChanged(QList<TeamAndColor> newValue);
    void strategiesChanged(QStringList newValue);
    void optionsChanged(QStringList newValue);

private:
    QString name;
    bool primary;
    QList<TeamAndColor> teams;
    QStringList strategies, options;

};

#endif // PARAMSMODEL_H
