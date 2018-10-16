#ifndef MESSAGEADAPTER_H
#define MESSAGEADAPTER_H

#include <QObject>
#include <QSqlDatabase>

class MessageAdapter : public QObject
{
    Q_OBJECT
public:
    MessageAdapter(QObject *parent = nullptr);

private:


};

#endif // MESSAGEADAPTER_H
