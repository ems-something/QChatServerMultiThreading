#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QStringList>
#include "Message.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    Chat(QStringList members = {""}, QString groupName = "");

signals:

public slots:
    void processChat();
    void onNewMessageArrived(QString, QString, QString, QDate);
    void membersDisconnected();

private:
    QString chatName; //2 users chat, chatName = DEFAULT_NAME
    QStringList members; //chat members
    QList< Message > messages; //message list
};

#endif // CHAT_H
