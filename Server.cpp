#include "Server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{

}

Q_INVOKABLE void Server::init()
{

    if(listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server: started";
    }
    else
    {
        qDebug() << "Server: not started!";
    }
}


//Setter de la GUI
void Server::setView(QObject *v)
{
    view = v;
}


void Server::onNewAuthenticatedClient(QString nickname, QString handle)
{

    usersList.insert(nickname, handle);

    emit clientListUpdated(usersList.keys());
}


void Server::onNewChatRequest(QStringList members, QString groupName)
{

    QThread *chatThread = new QThread;
    Chat *chat = new Chat(members, groupName);
    chat->moveToThread(chatThread);

    for(int i = 0; i < members.size(); i++)
    {

        if(clients.contains(members.at(i)))
        {

            connect(clients[usersList.value(members.at(i))], SIGNAL(newMessageArrived(QString, QString, QString, QDate)),
                    chat, SLOT(onNewMessageArrived(QString, QString, QString, QDate)));
        }

    }

    connect(chatThread, SIGNAL(started()), chat, SLOT(processChat()));
    connect(chat, SIGNAL(membersDisconnected()), chatThread, SLOT(quit()));
    connect(chat, SIGNAL(membersDisconnected()), chat, SLOT(deleteLater()));
    connect(chatThread, SIGNAL(finished()), chatThread, SLOT(deleteLater()));

   chatThread->start();
}


void Server::onClientDisconnected(QString nickname)
{

    clients.remove(usersList.value(nickname));

    emit clientListUpdated(usersList.keys());
}


void Server::incomingConnection(qintptr handle)
{
    //at the incoming connection, make a client
    QThread *clientThread = new QThread;
    User *client = new User(handle);
    client->moveToThread(clientThread);

    connect(clientThread, SIGNAL(started()), client, SLOT(processClient()));
    connect(this, SIGNAL(clientListUpdated(QStringList)), client, SLOT(onClientListUpdated(QStringList)), Qt::QueuedConnection);
    connect(client, SIGNAL(newAuthenticatedClient(QString, QString)), this, SLOT(onNewAuthenticatedClient(QString, QString)), Qt::BlockingQueuedConnection);
    connect(client, SIGNAL(newChatRequest(QStringList, QString)), this, SLOT(onNewChatRequest(QStringList, QString)), Qt::BlockingQueuedConnection);
    connect(client, SIGNAL(clientDisconnected(QString)), this, SLOT(onClientDisconnected(QString)), Qt::BlockingQueuedConnection);
    connect(client, SIGNAL(clientDisconnected()), clientThread, SLOT(quit()));
    connect(client, SIGNAL(clientDisconnected()), client, SLOT(deleteLater()));
    connect(clientThread, SIGNAL(finished()), clientThread, SLOT(deleteLater()));

    clients.insert(QString::number((handle)), client);

   clientThread->start();

}
