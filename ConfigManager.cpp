#include "ConfigManager.h"

#include <QDebug>

QMutex ConfigManager::m_mutex;
ConfigManager * ConfigManager::m_instance;

ConfigManager::ConfigManager()
{
    m_config = new AppConfig();
}

ConfigManager *ConfigManager::instance()
{
    if ( m_instance == nullptr )
    {
        m_mutex.lock();
        if( m_instance == nullptr )
        {
            m_instance = new ConfigManager();
        }
        m_mutex.unlock();
    }

    return m_instance;
}

void ConfigManager::insert(QString group, QString key, QString val)
{
    m_config->insert(group,key,val);
}

QString ConfigManager::value(QString group, QString key, QString default_val)
{
    qDebug() << "ConfigManager::value" << m_config->value(group,key,default_val);
    return m_config->value(group,key,default_val);
}

void ConfigManager::remove(QString group, QString key)
{
    m_config->remove(group,key);
}
