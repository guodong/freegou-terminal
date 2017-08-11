#include "bridge.h"
#include <QDebug>
#include <QAudioInput>
#include <QBuffer>
#include "wsclient.h"

Bridge::Bridge(wsclient *c, QObject *parent) : QObject(parent)
{
    client = c;
}

void Bridge::startRecord()
{
    if (buf) {
        free(buf);
    }
    buf = new QBuffer();
    buf->open(QIODevice::WriteOnly | QIODevice::Truncate);
    QAudioFormat fmt;
    fmt.setSampleRate(16000);
    fmt.setChannelCount(1);
    fmt.setSampleSize(16);
    fmt.setCodec("audio/pcm");

    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    if (!info.isFormatSupported(fmt)) {
        qDebug( "Default format not supported, trying to use the nearest.");
    }
    input = new QAudioInput(fmt, this);
    input->start(buf);
}

void Bridge::stopRecord()
{
    input->stop();
    client->sendBinary(buf->data());
    delete buf;
    buf = nullptr;
}
