#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDate>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message();
    //Setters
    void setFrom(const QString);
    void setTo(const QString);
    void setBody(const QString);
    void setDate(const QDate);
    //Getters
    QString getFrom() const;
    QString getTo() const;
    QString getBody() const;
    QDate getDate() const;

private:
     QString from;
     QString to;
     QString body;
     QDate date;

};

#endif // MESSAGE_H
