#include "Chat.h"

Chat::Chat( QStringList users, QString groupName)
    : chatName(groupName),  members(users)
{

}

void Chat::processChat()
{


}


void Chat::onNewMessageArrived(QString from, QString to, QString body, QDate date)
{


}


void Chat::membersDisconnected()
{


}
