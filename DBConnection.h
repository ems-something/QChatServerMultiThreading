#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

//Singleton Class
class DBConnection : public QObject
{
    Q_OBJECT
public:
    explicit DBConnection(QObject *parent = nullptr, QString connectionName = "");
    bool connectToDB();
    void disconnectFromDB();
    QSqlDatabase getDB() const;

signals:

public slots:

private:
    QSqlDatabase db;

};

#endif // DBCONNECTION_H
