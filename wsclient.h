#ifndef WSCLIENT_H
#define WSCLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QDebug>

class wsclient : public QObject
{
    Q_OBJECT
public:
    explicit wsclient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

    void sendBinary(const QByteArray &data);
signals:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;

};

#endif // WSCLIENT_H
