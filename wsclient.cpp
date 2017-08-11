#include "wsclient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

wsclient::wsclient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &wsclient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &wsclient::closed);
    m_webSocket.open(QUrl(url));
}

void wsclient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &wsclient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));

}

void wsclient::sendBinary(const QByteArray &data)
{
    m_webSocket.sendBinaryMessage(data);
}

void wsclient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    //m_webSocket.close();
}
