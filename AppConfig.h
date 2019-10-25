#ifndef AppCONFIG_H
#define AppCONFIG_H

#include <QObject>
#include <QSettings>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    AppConfig();
    ~AppConfig();

    void insert(QString group, QString key, QString val);

    QString value(QString group, QString key, QString default_val = "");

    void remove(QString group, QString key);


private:
    void initialize();

    void create_file(QString file_path, QString file_name);

private:

    QSettings *m_conf_settings;
};

#endif // AppCONFIG_H
