#ifndef SocketClient_H
#define SocketClient_H

#include <QTimer>
#include <QObject>
#include <QWebSocket>

class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = nullptr);

    bool isConnected() { return mp_socket->state() == QAbstractSocket::ConnectedState; }

    void uploadFile(QString fileName, QString buf);

signals:

public slots:
    void slot_socketError(QAbstractSocket::SocketError error);
    void slot_connected();
    void slot_disconnected();
    void slot_textMessageReceived(QString);

private slots:
    void reConnect();

private:
    QWebSocket *mp_socket;

    QString m_ip;
    QString m_port;
    QUrl m_url;

    QTimer *mp_reConnectTimer;
};

#endif // SocketClient_H
