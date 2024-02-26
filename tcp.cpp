#include "tcp.h"
#pragma execution_character_set("utf-8")
TCP::TCP()
{
   tcp_socket = new QTcpSocket();
   tcp_server = new QTcpServer();
}

TCP::~TCP()
{

}

void TCP::listenPort(const QHostAddress address, const quint16 port)
{
    if(!tcp_server->isListening()){
        qDebug()<<"关闭端口监听";
        tcp_server->close();
    }
    if(!tcp_server->listen(address, port))
    {
        qDebug()<<"监听启动失败："<<tcp_server->errorString();
    }
    connect(tcp_server,&QTcpServer::newConnection,this,&TCP::OneNewConnection);
    qDebug()<<"开始监听端口:";
    qDebug()<<"IP地址:"<<tcp_server->serverAddress().toString()<<",端口号:"<<QString::number(tcp_server->serverPort());
}

void TCP::OneNewConnection()
{
    tcp_socket = tcp_server->nextPendingConnection();
    qDebug()<<"新客户端连接";
    qDebug()<<"IP地址:"<<tcp_socket->peerAddress();
    qDebug()<<"端口号:"<<QString::number(tcp_socket->peerPort());
    connect(tcp_socket,&QTcpSocket::readyRead,this,&TCP::ReadData);
    connect(tcp_socket,&QTcpSocket::disconnected,this,&TCP::ClientDisconnect);
    emit connected();
}

void TCP::ReadData()
{
    QByteArray data(tcp_socket->readAll());
    if(!data.isEmpty())
    {
       emit newData(data);
    }

}

void TCP::ClientDisconnect()
{
    qDebug()<<"clientdisconnect";
    emit disconnected();
}


bool TCP::WriteSocket(QByteArray message)
{
    if(tcp_socket!=NULL)
    {
        if(tcp_socket->write(message)!=-1)
        {
            tcp_socket->flush();
            return true;
        }
    }
    return false;
}
