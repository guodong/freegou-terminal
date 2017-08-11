#include "mainwindow.h"
#include <QApplication>
#include <QAudioInput>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebSockets/QWebSocketServer>
#include <QWebChannel>
#include <QDialog>
#include "wsclient.h"
#include "websocketclientwrapper.h"
#include "bridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    wsclient client(QUrl(QStringLiteral("ws://192.168.10.5:8887")), true);
    QObject::connect(&client, &wsclient::closed, &a, &QCoreApplication::quit);

    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode);

    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    Bridge bridge(&client);
    channel.registerObject(QStringLiteral("bridge"), &bridge);

    MainWindow w;
    client.setMainWindow(&w);
    w.showMaximized();
    //w.showFullScreen();



    return a.exec();
}
