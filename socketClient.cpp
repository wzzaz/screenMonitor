#include "SocketClient.h"
#include "ConfigManager.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

const int reconnect_interval = 5000;

SocketClient::SocketClient(QObject *parent) : QObject(parent)
{
    mp_socket = new QWebSocket;

    connect(mp_socket, SIGNAL(connected()), this, SLOT(slot_connected()));
    connect(mp_socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
    connect(mp_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(slot_textMessageReceived(QString)));
    connect(mp_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_socketError(QAbstractSocket::SocketError)));

    m_url = QString("ws://%1:%2").arg("127.0.0.1").arg("3000");
    mp_socket->open(m_url);

    mp_reConnectTimer = new QTimer(this);
    mp_reConnectTimer->setSingleShot(false);
    mp_reConnectTimer->setInterval(reconnect_interval);
    connect(mp_reConnectTimer, SIGNAL(timeout()), this, SLOT(reConnect()));
}

void SocketClient::uploadFile(QString fileName, QString buf)
{
    QJsonObject json;
    json.insert("file", fileName);
    json.insert("bin", buf);

    QJsonDocument docu;
    docu.setObject(json);
    QByteArray jsonByte = docu.toJson(QJsonDocument::Compact);
    QString messageJson(jsonByte);
    mp_socket->sendTextMessage(jsonByte);
}

void SocketClient::slot_socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "socket error: " << error;
}

void SocketClient::slot_connected()
{
    qDebug() << "...connect";
    mp_reConnectTimer->stop();
}

void SocketClient::slot_disconnected()
{
    qDebug() << "...disconnected";
    if( !mp_reConnectTimer->isActive() ) {
        mp_reConnectTimer->start();
    }
}

void SocketClient::slot_textMessageReceived(QString msg)
{
    qDebug() << "slot_textMessageReceived:" << msg;
}

void SocketClient::reConnect()
{
    if( !isConnected() ) {
        qDebug() << "...reconnect";
        mp_socket->open(m_url);
    }
}
