#include "DBConnection.h"

DBConnection::DBConnection(QObject *parent, QString connectionName) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL", connectionName);
    db.setHostName("localhost");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("postgres");
    db.setDatabaseName("chat_db");

}


QSqlDatabase DBConnection::getDB() const
{

    return db;
}


bool DBConnection::connectToDB()
{
  bool ok = db.open();

  if(ok)
    qDebug() << "Database connection successful" << endl;
  else
  {
      qDebug() << "Error connecting to the database" <<endl;
      qDebug() << db.lastError().text() <<endl;
  }

  return ok;
}


void  DBConnection::disconnectFromDB()
{

    db.close();
}
