#include "clientw.h"
#include "ui_clientw.h"

#include <QTcpSocket>

ClientW::ClientW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientW),
    socket(NULL)
{
    ui->setupUi(this);

    connect(ui->connect_pb, &QPushButton::clicked,this,&ClientW::onConnect);
    connect(ui->disconnect_pb, &QPushButton::clicked,this,&ClientW::onDisconnect);
    connect(ui->send_pb, &QPushButton::clicked,this,&ClientW::onSend);
}

ClientW::~ClientW()
{
    delete ui;
}

void ClientW::onConnect()
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected,this,&ClientW::onConnected);
    connect(socket, &QTcpSocket::disconnected,this,&ClientW::onDisconnected);
    connect(socket, &QTcpSocket::readyRead,this,&ClientW::onReadyRead);

    QString address = ui->address_le->text();
    quint16 port = ui->port_le->text().toUInt();
    socket->connectToHost(address, port);
    ui->address_le->setEnabled(false);
    ui->port_le->setEnabled(false);
    ui->connect_pb->setEnabled(false);
    ui->disconnect_pb->setEnabled(true);
}

void ClientW::onDisconnect()
{
    if (socket != NULL) {
        socket->deleteLater();
        socket = NULL;
    }
    ui->address_le->setEnabled(true);
    ui->port_le->setEnabled(true);
    ui->connect_pb->setEnabled(true);
    ui->disconnect_pb->setEnabled(false);
}

void ClientW::onSend()
{
    QString msg = ui->message_le->text();
    if (socket == NULL) {
        return;
    }
    if (!socket->isValid()) {
        return;
    }
    if (!socket->isOpen()) {
        return;
    }
    socket->write(msg.toUtf8());
    socket->flush();
    ui->message_le->clear();
    ui->main_textedit->append(QString(u8"Я: %1").arg(msg));
}

void ClientW::onConnected()
{
    ui->message_le->setEnabled(true);
    ui->send_pb->setEnabled(true);
}

void ClientW::onDisconnected()
{
    ui->message_le->setEnabled(false);
    ui->send_pb->setEnabled(false);
}

void ClientW::onReadyRead()
{
    if (socket == NULL) {
        return;
    }
    if (!socket->isValid()) {
        return;
    }
    if (!socket->isOpen()) {
        return;
    }
    QByteArray ba = socket->readAll();
    ui->main_textedit->append(QString(u8"Я: %1").arg(QString(ba)));
}
