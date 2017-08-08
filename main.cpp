#include "mainwindow.h"
#include <QApplication>
#include <QAudioInput>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QtWebEngine::initialize();


//        QQmlApplicationEngine engine;
//        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return a.exec();
}
