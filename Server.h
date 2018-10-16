#ifndef SERVER_H
#define SERVER_H

#include <QAbstractSocket>
#include <QTcpServer>
#include <QThread>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include "User.h"
#include "Chat.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    Q_INVOKABLE void init();

protected:
    void incomingConnection(qintptr) Q_DECL_OVERRIDE;
    
signals:
    void clientListUpdated(QStringList);
    
public slots:
//Setter de la GUI
    void setView(QObject*);
    void onNewAuthenticatedClient(QString, QString);
    void onNewChatRequest(QStringList, QString);
    void onClientDisconnected(QString);

private:
//Ventana QML (GUI)
    QObject *view;
    QMap< QString, User* > clients;
    QMap< QString, QString > usersList;

};

#endif // SERVER_H
