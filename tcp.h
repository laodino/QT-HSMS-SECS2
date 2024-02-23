#ifndef TCP_H
#define TCP_H
#include <QTcpServer>
#include <QTcpSocket>

class TCP: public QObject
{
    Q_OBJECT
private:
  //  void CreateConnection(SECS_CFG &sc);

   void OneNewConnection();

   void ReadData();

   void ClientDisconnect();



   QTcpServer * tcp_server;
   QTcpSocket * tcp_socket;
signals:
   void connected();
   void disconnected();
   void newData(QByteArray data);

public:
    TCP();
    ~TCP();

     void  listenPort(quint16 port);

       bool WriteSocket(QByteArray message);
};

#endif // TCP_H
