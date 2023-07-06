#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "FilesTableModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FilesTableModel>("FilesTableModel", 0, 1, "FilesTableModel");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("BackupCleaner", "Main");

    return app.exec();
}
