#ifndef WEBSOCKETTRANSPORTSERVER_H
#define WEBSOCKETTRANSPORTSERVER_H

#include <QObject>
#include <QWebChannel>
#include <QWebChannelAbstractTransport>

QT_BEGIN_NAMESPACE

class QWebSocketServer;
class WebSocketTransport;
class QWebChannelAbstractTransport;

class WebSocketClientWrapper : public QObject
{
    Q_OBJECT

public:
    WebSocketClientWrapper(QWebSocketServer *server, QObject *parent = 0);

Q_SIGNALS:
    void clientConnected(QWebChannelAbstractTransport* client);

private Q_SLOTS:
    void handleNewConnection();

private:
    QWebSocketServer *m_server;
};

QT_END_NAMESPACE

#endif
