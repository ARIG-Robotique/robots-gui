#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ctime>

#include "common.h"
#include "sockethelper.h"
#include "socketthread.h"
#include "robotmodel.h"
#include "spdlog/sinks/basic_file_sink.h"

int main(int argc, char *argv[])
{
    // construit la date d'execution
    time_t now = time(nullptr);
    tm *ptm = localtime(&now);
    char timeBuffer[15];
    strftime(timeBuffer, 15, "%Y%m%d%H%M%S", ptm);

    const string outputDir = "logs";
    const string outputPrefix = outputDir + string(timeBuffer);

    // configuration du logger
    auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(outputPrefix + ".log");
    spdlog::default_logger()->sinks().push_back(file_sink);
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_level(spdlog::level::info);  

    spdlog::info("Démarrage de l'application");

    // Configuration de la Socket
    SocketHelper socket(SOCKET_INET);
    socket.setPort(9000);
    SocketThread socketThread;
    socketThread.setSocketHelper(&socket);
    socketThread.start();

    // Enregistrement du model
    qmlRegisterType<RobotModel>("org.arig.robotmodel", 1, 0, "RobotModel");

    // QML Application
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
