#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtWebEngineWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebEngineView *view = new QWebEngineView(this);
    QUrl url = QUrl("http://baidu.com");
    view->load(url);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    file = new QFile();
    file->setFileName("/Users/gd/b.pcm");
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);

    QAudioFormat fmt;
    fmt.setSampleRate(16000);
    fmt.setChannelCount(1);
    fmt.setSampleSize(16);
    fmt.setCodec("audio/pcm");

    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    //qDebug(info.supportedCodecs().join());
    if (!info.isFormatSupported(fmt))
                {
                    qDebug( "Default format not supported, trying to use the nearest.");
                }
    input = new QAudioInput(fmt, this);
    input->start(file);
}

void MainWindow::on_pushButton_2_clicked()
{
    input->stop();
    file->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile *file = new QFile();
    file->setFileName("/Users/gd/b.pcm");
         file->open(QIODevice::ReadOnly);
    QAudioFormat format;
         format.setSampleRate(16000);
         format.setChannelCount(1);
         format.setSampleSize(16);
         format.setCodec("audio/pcm");
         format.setByteOrder(QAudioFormat::LittleEndian);
         format.setSampleType(QAudioFormat::UnSignedInt);

         QAudioOutput *output = new QAudioOutput(format);
         output->start(file);
}
