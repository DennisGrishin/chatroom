#ifndef CLIENTW_H
#define CLIENTW_H

#include <QWidget>

class QTcpSocket;

namespace Ui {
class ClientW;
}

class ClientW : public QWidget
{
    Q_OBJECT

public:
    explicit ClientW(QWidget *parent = nullptr);
    ~ClientW();

private:
    Ui::ClientW *ui;
    QTcpSocket* socket;


private slots:
    void onConnect();
    void onDisconnect();
    void onSend();
    void onConnected();
    void onDisconnected();
    void onReadyRead();
};

#endif // CLIENTW_H
