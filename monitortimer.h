#ifndef MONITORTIMER_H
#define MONITORTIMER_H

#include <QObject>
#include <QTimer>
#include "socketClient.h"

class MonitorTimer : public QObject
{
    Q_OBJECT
public:
    explicit MonitorTimer(QObject *parent = nullptr);

    Q_INVOKABLE void startMonitor(int interval);

    Q_INVOKABLE void stopMonitor();

signals:

private:
    QString getHiddenFold(QString name);

public slots:
    void slot_screenShot();

private:
    QString m_savePath;

    QTimer *m_timer;

    SocketClient *m_socketClient;
};

#endif // MONITORTIMER_H
