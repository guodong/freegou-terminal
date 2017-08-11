#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QBuffer>
#include <QAudioInput>
#include "wsclient.h"

class Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Bridge(wsclient *c, QObject *parent = nullptr);

signals:
    /*!
        This signal is emitted from the C++ side and the text displayed on the HTML client side.
    */
    void sendText(const QString &text);

public slots:
    /*!
        This slot is invoked from the HTML client side and the text displayed on the server side.
    */
    void startRecord();
    void stopRecord();

private:
    QBuffer buf;
    QAudioInput *input;
    wsclient *client;
};

#endif // BRIDGE_H
