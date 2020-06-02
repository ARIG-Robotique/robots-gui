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
    Q_ENUMS(Team)
    Q_ENUMS(Strategy)

    // RW
    Q_PROPERTY(bool exit READ getExit WRITE setExit NOTIFY exitChanged)
    Q_PROPERTY(Team team READ getTeam WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(Strategy strategy READ getStrategy WRITE setStrategy NOTIFY strategyChanged)
    Q_PROPERTY(bool startCalibration READ getStartCalibration WRITE setStartCalibration NOTIFY startCalibrationChanged)
    Q_PROPERTY(bool skipCalageBordure READ getSkipCalageBordure WRITE setSkipCalageBordure NOTIFY skipCalageBordureChanged)
    Q_PROPERTY(bool modeManuel READ getModeManuel WRITE setModeManuel NOTIFY modeManuelChanged)
    Q_PROPERTY(bool updatePhoto READ getUpdatePhoto WRITE setUpdatePhoto NOTIFY updatePhotoChanged)
    Q_PROPERTY(bool etalonnageBalise READ getEtalonnageBalise WRITE setEtalonnageBalise NOTIFY etalonnageBaliseChanged)
    // posEccueil && posBouees pas déclarées car on utilise des getter/setters spécifiques

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
    Q_PROPERTY(QString photo READ getPhoto NOTIFY photoChanged)
    Q_PROPERTY(QList<QString> couleurEcueil READ getCouleurEcueil NOTIFY couleurEcueilChanged)
    Q_PROPERTY(QList<QString> couleurBouees READ getCouleurBouees NOTIFY couleurBoueesChanged)

    static RobotModel* instance;
    RobotModel(QObject *parent = nullptr);

public:
    enum Team { UNKNOWN, JAUNE, BLEU };
    enum Strategy { BASIC_NORD, BASIC_SUD, AGGRESSIVE, FINALE };

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

    bool getUpdatePhoto();
    void setUpdatePhoto(bool value);

    bool getEtalonnageBalise();
    void setEtalonnageBalise(bool value);

    QList<QPoint> getPosEcueil();
    void setPosEcueil(QList<QPoint> value);
    Q_INVOKABLE void setPosEcueilForQML(QJSValue value);
    Q_INVOKABLE QList<QVariant> getPosEcueilForQML();

    QList<QPoint> getPosBouees();
    void setPosBouees(QList<QPoint> value);
    Q_INVOKABLE void setPosBoueesForQML(QJSValue value);
    Q_INVOKABLE QList<QVariant> getPosBoueesForQML();

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

    QString getPhoto();
    void setPhoto(QString value);

    QList<QString> getCouleurEcueil();
    void setCouleurEcueil(QList<QString> value);

    QList<QString> getCouleurBouees();
    void setCouleurBouees(QList<QString> value);

signals:
    // RW
    void exitChanged(bool newValue);
    void teamChanged(Team newTeam);
    void strategyChanged(Strategy strategy);
    void startCalibrationChanged(bool newValue);
    void skipCalageBordureChanged(bool newValue);
    void modeManuelChanged(bool newValue);
    void updatePhotoChanged(bool newValue);
    void etalonnageBaliseChanged(bool newValue);
    void posEcueilChanged(QList<QPoint> newValue);
    void posBoueesChanged(QList<QPoint> newValue);

    // RO
    void i2cChanged(bool newValue);
    void lidarChanged(bool newValue);
    void alim12vChanged(bool newValue);
    void alim5vpChanged(bool newValue);
    void auChanged(bool newValue);
    void baliseChanged(bool newValue);
    void messageChanged(QString message);
    void phareChanged(bool newValue);
    void scoreChanged(int newValue);
    void inMatchChanged(bool newValue);
    void tiretteChanged(bool newValue);
    void photoChanged(QString newValue);
    void couleurEcueilChanged(QList<QString> newValue);
    void couleurBoueesChanged(QList<QString> newValue);

public slots:

private:
    // RW
    Team team;
    Strategy strategy;
    bool exit, startCalibration, modeManuel, skipCalageBordure, updatePhoto, etalonnageBalise;
    QList<QPoint> posEcueil, posBouees;

    // RO
    int score;
    bool inMatch, au, alim12v, alim5vp, tirette, phare, balise, i2c, lidar;
    QString message, photo;
    QList<QString> couleurEcueil, couleurBouees;

};

#endif // ROBOTMODEL_H
