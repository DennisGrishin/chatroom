#ifndef SERVERW_H
#define SERVERW_H

#include <QWidget>


namespace Ui {
class ServerW;
}

class QTcpServer;
class QTcpSocket;

class ServerW : public QWidget
{
    Q_OBJECT

public:
    explicit ServerW(QWidget *parent = nullptr);
    ~ServerW();

private:
    Ui::ServerW *ui;
    QTcpServer* server;
    QTcpSocket* socket;
    //QHash<QTcpSocket*,QString> sockets;

private slots:
    void onNewConnection();
    void onStart();
    void onStop();
    void onSend();
    void onConnected();
    void onDisconnected();
    void onReadyRead();
};

#endif // SERVERW_H
