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
    Q_ENUMS(Strategy)

    // RW
    Q_PROPERTY(Team team READ getTeam WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(Strategy strategy READ getStrategy WRITE setStrategy NOTIFY strategyChanged)
    Q_PROPERTY(bool startCalibration READ getStartCalibration WRITE setStartCalibration NOTIFY startCalibrationChanged)
    Q_PROPERTY(bool skipCalageBordure READ getSkipCalageBordure WRITE setSkipCalageBordure NOTIFY skipCalageBordureChanged)
    Q_PROPERTY(bool modeManuel READ getModeManuel WRITE setModeManuel NOTIFY modeManuelChanged)

    // RO
    Q_PROPERTY(bool au READ getAu NOTIFY auChanged)
    Q_PROPERTY(bool alim12v READ getAlim12v NOTIFY alim12vChanged)
    Q_PROPERTY(bool alim5vp READ getAlim5vp NOTIFY alim5vpChanged)
    Q_PROPERTY(bool inMatch READ getInMatch NOTIFY inMatchChanged)
    Q_PROPERTY(bool tirette READ getTirette NOTIFY tiretteChanged)
    Q_PROPERTY(bool i2c READ getI2c NOTIFY i2cChanged)
    Q_PROPERTY(bool lidar READ getLidar NOTIFY lidarChanged)
    Q_PROPERTY(bool phare READ getPhare NOTIFY phareChanged)
    Q_PROPERTY(bool balise READ getBalise NOTIFY baliseChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged)

    static RobotModel* instance;

public:
    RobotModel(QObject *parent = nullptr);

    enum Team { UNKNOWN, JAUNE, BLEU };
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

    bool getSkipCalageBordure();
    void setSkipCalageBordure(bool value);

    bool getModeManuel();
    void setModeManuel(bool value);

    // RO
    bool getInMatch();
    void setInMatch(bool value);

    bool getI2c();
    void setI2c(bool value);

    bool getLidar();
    void setLidar(bool value);

    bool getAu();
    void setAu(bool value);

    bool getAlim12v();
    void setAlim12v(bool value);

    bool getAlim5vp();
    void setAlim5vp(bool value);

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
    void i2cChanged(bool newValue);
    void lidarChanged(bool newValue);
    void alim12vChanged(bool newValue);
    void alim5vpChanged(bool newValue);
    void auChanged(bool newValue);
    void baliseChanged(bool newValue);
    void messageChanged(QString message);
    void phareChanged(bool newValue);
    void scoreChanged(int newValue);
    void startCalibrationChanged(bool newValue);
    void inMatchChanged(bool newValue);
    void strategyChanged(Strategy strategy);
    void teamChanged(Team newTeam);
    void tiretteChanged(bool newValue);
    void skipCalageBordureChanged(bool newValue);
    void modeManuelChanged(bool newValue);

public slots:

private:
    Team team;
    Strategy strategy;
    bool inMatch, au, alim12v, alim5vp, tirette, startCalibration, phare, balise, i2c, lidar, modeManuel, skipCalageBordure;
    int score;
    QString message;

};

#endif // ROBOTMODEL_H
