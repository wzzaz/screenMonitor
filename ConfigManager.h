#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QMutex>
#include <QObject>
#include "AppConfig.h"

class ConfigManager : public QObject
{
    Q_OBJECT
private:
    ConfigManager();

public:

    static ConfigManager* instance();

    Q_INVOKABLE void insert(QString group, QString key, QString val);

    Q_INVOKABLE QString value(QString group, QString key, QString default_val = "");

    void remove(QString group, QString key);

private:

    AppConfig * m_config;

    static QMutex m_mutex;

    static ConfigManager * m_instance;
};

#endif // CONFIGMANAGER_H
