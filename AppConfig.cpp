#include "AppConfig.h"

#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <QSettings>
#include <QApplication>
#include <QCoreApplication>

AppConfig::AppConfig()
{
    initialize();
}

AppConfig::~AppConfig()
{
    if( m_conf_settings ) {
        delete m_conf_settings;
        m_conf_settings = nullptr;
    }
}

void AppConfig::insert(QString group, QString key, QString val)
{
    m_conf_settings->beginGroup(group);
    m_conf_settings->setValue(key,val);
    m_conf_settings->endGroup();
}

QString AppConfig::value(QString group, QString key, QString default_val)
{
    QString val;
    m_conf_settings->beginGroup(group);
    val = m_conf_settings->value(key,QVariant(default_val)).toString();
    m_conf_settings->endGroup();
    return val;
}

void AppConfig::remove(QString group, QString key)
{
    m_conf_settings->beginGroup(group);
    m_conf_settings->remove(key);
    m_conf_settings->endGroup();
}

void AppConfig::initialize()
{
    QString app_dir_path= QCoreApplication::applicationDirPath();
    QString conf_name = QString("%1.conf").arg( QApplication::applicationName() );
    QString conf_path = app_dir_path + "/" + conf_name;

    if( !QFile::exists(conf_path) ) {
        create_file(app_dir_path, conf_name);
    }

    m_conf_settings = new QSettings(conf_path, QSettings::IniFormat);
    m_conf_settings->setIniCodec(QTextCodec::codecForName("utf-8"));
}

void AppConfig::create_file(QString file_path, QString file_name)
{
    QDir temp_dir;
    QString current_dir = temp_dir.currentPath();
    if(!temp_dir.exists(file_path))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        temp_dir.mkpath(file_path);
    }
    QFile temp_file;
    temp_dir.setCurrent(file_path);
    qDebug()<<temp_dir.currentPath();
    if(QFile::exists(file_name))
    {
        qDebug()<<QObject::tr("文件存在");
        return ;
    }
    temp_file.setFileName(file_name);
    if(!temp_file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
    }
    temp_file.close();
    temp_dir.setCurrent(current_dir);
    qDebug()<<temp_dir.currentPath();
}

