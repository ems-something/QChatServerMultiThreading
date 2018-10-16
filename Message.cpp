#include "Message.h"

Message::Message()
{

}

void Message::setFrom(const QString from)
{
    this->from = from;
}


void Message::setTo(const QString to)
{
    this->to = to;
}


void Message::setBody(const QString body)
{

    this->body = body;
}


void Message::setDate(const QDate date)
{

    this->date = date;
}


QString Message::getFrom() const
{

    return from;
}


QString Message::getTo() const
{

    return to;
}


QString Message::getBody() const
{

    return body;
}


QDate Message::getDate() const
{

    return date;
}
