#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QString>
#include <QPoint>

class RobotModel : public QObject
{
    Q_OBJECT

public:
    enum Team { UNKNOWN, JAUNE, BLEU };
    enum Strategy { BASIC, AGGRESSIVE, FINALE };

    Q_ENUM(Team)
    Q_ENUM(Strategy)

private:
    // RW
    Q_PROPERTY(bool exit READ getExit WRITE setExit NOTIFY exitChanged)
    Q_PROPERTY(Team team READ getTeam WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(Strategy strategy READ getStrategy WRITE setStrategy NOTIFY strategyChanged)
    Q_PROPERTY(bool startCalibration READ getStartCalibration WRITE setStartCalibration NOTIFY startCalibrationChanged)
    Q_PROPERTY(bool skipCalageBordure READ getSkipCalageBordure WRITE setSkipCalageBordure NOTIFY skipCalageBordureChanged)
    Q_PROPERTY(bool modeManuel READ getModeManuel WRITE setModeManuel NOTIFY modeManuelChanged)
    Q_PROPERTY(bool safeAvoidance READ getSafeAvoidance WRITE setSafeAvoidance NOTIFY safeAvoidanceChanged)
    Q_PROPERTY(bool deposePartielle READ getDeposePartielle WRITE setDeposePartielle NOTIFY deposePartielleChanged)
    Q_PROPERTY(bool echangeEcueil READ getEchangeEcueil WRITE setEchangeEcueil NOTIFY echangeEcueilChanged)
    Q_PROPERTY(bool updatePhoto READ getUpdatePhoto WRITE setUpdatePhoto NOTIFY updatePhotoChanged)
    Q_PROPERTY(bool etalonnageBalise READ getEtalonnageBalise WRITE setEtalonnageBalise NOTIFY etalonnageBaliseChanged)
    Q_PROPERTY(bool etalonnageOk READ getEtalonnageOk WRITE setEtalonnageOk NOTIFY etalonnageOkChanged)
    Q_PROPERTY(bool twoRobots READ getTwoRobots WRITE setTwoRobots NOTIFY twoRobotsChanged)

    // RO
    Q_PROPERTY(bool au READ getAu NOTIFY auChanged)
    Q_PROPERTY(bool alim12v READ getAlim12v NOTIFY alim12vChanged)
    Q_PROPERTY(bool alim5vp READ getAlim5vp NOTIFY alim5vpChanged)
    Q_PROPERTY(bool inMatch READ getInMatch NOTIFY inMatchChanged)
    Q_PROPERTY(bool tirette READ getTirette NOTIFY tiretteChanged)
    Q_PROPERTY(bool i2c READ getI2c NOTIFY i2cChanged)
    Q_PROPERTY(bool lidar READ getLidar NOTIFY lidarChanged)
    Q_PROPERTY(bool otherRobot READ getOtherRobot NOTIFY otherRobotChanged)
    Q_PROPERTY(bool balise READ getBalise NOTIFY baliseChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(QString message READ getMessage NOTIFY messageChanged)
    Q_PROPERTY(QString photoMessage READ getPhotoMessage NOTIFY photoMessageChanged)
    Q_PROPERTY(QString photo READ getPhoto NOTIFY photoChanged)

    static RobotModel* instance;
    RobotModel(QObject *parent = nullptr);

public:
    static QObject* singletonProvider(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);
    static RobotModel* getInstance();

    // RW
    bool getExit();
    void setExit(bool value);

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

    bool getSafeAvoidance();
    void setSafeAvoidance(bool value);

    bool getDeposePartielle();
    void setDeposePartielle(bool value);

    bool getEchangeEcueil();
    void setEchangeEcueil(bool value);

    bool getUpdatePhoto();
    void setUpdatePhoto(bool value);

    bool getEtalonnageBalise();
    void setEtalonnageBalise(bool value);

    bool getEtalonnageOk();
    void setEtalonnageOk(bool value);

    bool getTwoRobots();
    void setTwoRobots(bool value);

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

    bool getOtherRobot();
    void setOtherRobot(bool value);

    bool getBalise();
    void setBalise(bool value);

    int getScore();
    void setScore(int value);

    QString getMessage();
    void setMessage(QString value);

    QString getPhotoMessage();
    void setPhotoMessage(QString value);

    QString getPhoto();
    void setPhoto(QString value);

signals:
    // RW
    void exitChanged(bool newValue);
    void teamChanged(Team newTeam);
    void strategyChanged(Strategy strategy);
    void startCalibrationChanged(bool newValue);
    void skipCalageBordureChanged(bool newValue);
    void modeManuelChanged(bool newValue);
    void safeAvoidanceChanged(bool newValue);
    void deposePartielleChanged(bool newValue);
    void echangeEcueilChanged(bool newValue);
    void updatePhotoChanged(bool newValue);
    void etalonnageBaliseChanged(bool newValue);
    void etalonnageOkChanged(bool newValue);
    void twoRobotsChanged(bool newValue);

    // RO
    void i2cChanged(bool newValue);
    void lidarChanged(bool newValue);
    void alim12vChanged(bool newValue);
    void alim5vpChanged(bool newValue);
    void auChanged(bool newValue);
    void baliseChanged(bool newValue);
    void messageChanged(QString message);
    void otherRobotChanged(bool newValue);
    void scoreChanged(int newValue);
    void inMatchChanged(bool newValue);
    void tiretteChanged(bool newValue);
    void photoMessageChanged(QString newValue);
    void photoChanged(QString newValue);

public slots:

private:
    // RW
    Team team;
    Strategy strategy;
    bool exit, startCalibration, modeManuel, skipCalageBordure, safeAvoidance, deposePartielle, echangeEcueil, updatePhoto, etalonnageBalise, etalonnageOk, twoRobots;

    // RO
    int score;
    bool inMatch, au, alim12v, alim5vp, tirette, otherRobot, balise, i2c, lidar;
    QString message, photoMessage, photo;

};

#endif // ROBOTMODEL_H
