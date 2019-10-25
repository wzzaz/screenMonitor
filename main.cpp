#include <QApplication>
#include <QQmlContext>
#include <QSettings>
#include <QDebug>
#include "monitortimer.h"
#include "ConfigManager.h"

const QString screenshot_interval = "5000";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QString appName = QApplication::applicationName();
    QString appPath = QApplication::applicationFilePath();
    appPath = appPath.replace("/","\\");

    QSettings *settings = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                                        QSettings::NativeFormat);

    QString val = settings->value(appName).toString();
    qDebug() << "val:" << val;
    if(val != appPath)
        settings->setValue(appName,appPath);

    ConfigManager *config = ConfigManager::instance();

    MonitorTimer *monitorTimer = new MonitorTimer;
    monitorTimer->startMonitor(config->value("timer", "screenshot_interval", screenshot_interval).toInt());

    return app.exec();
}
