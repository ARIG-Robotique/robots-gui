#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QString>

class RobotModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(Team)
    Q_ENUMS(Steps)
    Q_ENUMS(Strategy)

    // RW
    Q_PROPERTY(Team team READ getTeam WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(Strategy strategy READ getStrategy WRITE setStrategy NOTIFY strategyChanged)
    Q_PROPERTY(bool startCalibration READ getStartCalibration WRITE setStartCalibration NOTIFY startCalibrationChanged)

    // RO
    Q_PROPERTY(Steps step READ getStep NOTIFY stepChanged)
    Q_PROPERTY(bool au READ getAu NOTIFY auChanged)
    Q_PROPERTY(bool alim12v READ getAlim12v NOTIFY alim12vChanged)
    Q_PROPERTY(bool alim5vp READ getAlim5vp NOTIFY alim5vpChanged)
    Q_PROPERTY(bool alim5vl READ getAlim5vl NOTIFY alim5vlChanged)
    Q_PROPERTY(bool tirette READ getTirette NOTIFY tiretteChanged)
    Q_PROPERTY(bool phare READ getPhare NOTIFY phareChanged)
    Q_PROPERTY(bool balise READ getBalise NOTIFY baliseChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged)

    static RobotModel* instance;

public:
    RobotModel(QObject *parent = nullptr);

    enum Team { BLUE, YELLOW };
    enum Steps { CONFIGURATION, MATCH, END_MATCH };
    enum Strategy { STRAT1, STRAT2, STRAT3 };

    static QObject* singletonProvider(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);
    static RobotModel* getInstance();

    // RW
    Team getTeam();
    void setTeam(Team team);

    bool getStartCalibration();
    void setStartCalibration(bool value);

    Strategy getStrategy();
    void setStrategy(Strategy strategy);

    // RO
    Steps getStep();
    void setStep(Steps step);

    bool getAu();
    void setAu(bool value);

    bool getAlim12v();
    void setAlim12v(bool value);

    bool getAlim5vp();
    void setAlim5vp(bool value);

    bool getAlim5vl();
    void setAlim5vl(bool value);

    bool getTirette();
    void setTirette(bool value);

    bool getPhare();
    void setPhare(bool value);

    bool getBalise();
    void setBalise(bool value);

    int getScore();
    void setScore(int value);

    QString getMessage();
    void setMessage(QString message);

signals:
    void alim12vChanged(bool newValue);
    void alim5vpChanged(bool newValue);
    void alim5vlChanged(bool newValue);
    void auChanged(bool newValue);
    void baliseChanged(bool newValue);
    void messageChanged(QString message);
    void phareChanged(bool newValue);
    void scoreChanged(int newValue);
    void startCalibrationChanged(bool newValue);
    void stepChanged(Steps newStep);
    void strategyChanged(Strategy strategy);
    void teamChanged(Team newTeam);
    void tiretteChanged(bool newValue);

public slots:

private:
    Team team;
    Steps step;
    Strategy strategy;
    bool au, alim12v, alim5vp, alim5vl, tirette, startCalibration, phare, balise;
    int score;
    QString message;

};

#endif // ROBOTMODEL_H
