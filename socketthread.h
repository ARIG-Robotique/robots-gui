#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include "sockethelper.h"
#include "robotmodel.h"

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread();
    ~SocketThread() Q_DECL_OVERRIDE;

    void setSocketHelper(SocketHelper *helper);
    void setRobotModel(RobotModel *robotModel);
    void abortExecution();

signals:
    void photoReceived(string photo);
    //void statusReceived(StatusRobot status);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    bool abort;
    SocketHelper *helper;
    RobotModel *robotModel;
};

#endif // SOCKETTHREAD_H
