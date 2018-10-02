#include "serverw.h"
#include "ui_serverw.h"

#include <QTcpServer>
#include <QTcpSocket>

ServerW::ServerW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerW),
    socket(nullptr)
{
    ui->setupUi(this);

    connect(ui->start_pb, &QPushButton::clicked,this,&ServerW::onStart);
    connect(ui->stop_pb, &QPushButton::clicked,this,&ServerW::onStop);
    connect(ui->send_pb, &QPushButton::clicked,this,&ServerW::onSend);

    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection,this,&ServerW::onNewConnection);
}

ServerW::~ServerW()
{
    delete ui;
}

void ServerW::onStart()
{
    int port = ui->port_le->text().toInt();

    if (server->listen(QHostAddress::Any, port)) {
        ui->start_pb->setEnabled(false);
        ui->stop_pb->setEnabled(true);
        ui->port_le->setEnabled(false);
        ui->main_textedit->append(QString(u8"Запуск сервера на порту %1").arg(port));
    }
}

void ServerW::onStop()
{
    server->close();
    ui->start_pb->setEnabled(true);
    ui->stop_pb->setEnabled(false);
    ui->port_le->setEnabled(true);
    ui->main_textedit->append(QString(u8"Остановка сервера"));
}

void ServerW::onSend()
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

void ServerW::onConnected()
{
    ui->message_le->setEnabled(true);
    ui->send_pb->setEnabled(true);
}

void ServerW::onDisconnected()
{
    ui->message_le->setEnabled(false);
    ui->send_pb->setEnabled(false);
    socket->deleteLater();
    socket = NULL;
}

void ServerW::onReadyRead()
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

void ServerW::onNewConnection()
{
    QTcpSocket* socket = server->nextPendingConnection();
    connect(socket,&QTcpSocket::connected, this, &ServerW::onConnected);
    connect(socket,&QTcpSocket::disconnected, this, &ServerW::onDisconnected);
    connect(socket,&QTcpSocket::readyRead, this, &ServerW::onReadyRead);

    ui->message_le->setEnabled(true);
    ui->send_pb->setEnabled(true);
}
