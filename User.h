#ifndef USER_H
#define USER_H

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QDebug>
#include <QSqlQuery>
#include <QVariantMap>
#include "Message.h"
#include "DBConnection.h"


class User : public QObject
{
    Q_OBJECT
    Q_ENUMS(Service)        // metadata declaration
public:
    explicit User(qintptr handle);
    void  processRequest(QVariantMap);
    bool clientAuthentication(const QString, const QString);
    void sendResponse();

    void setNickname(const QString);
    QString getNickname() const;

    enum Service
        {
            clientListUpdate, logIn, newChat, newMessage, newFile, readFile, editFile
        };

signals:
    void error(QAbstractSocket::SocketError);
    void newAuthenticatedClient(QString, QString);
    void newChatRequest(QStringList, QString);
    void newMessageArrived(QString, QString, QString, QDate);
    void clientDisconnected(QString);
    void clientDisconnected();
    
public slots:
    void processClient();
    void displayError(QAbstractSocket::SocketError);
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onClientListUpdated(QStringList);

private:
    QTcpSocket *socket;
    qintptr sockHandle;
    DBConnection *dbHandle;
    QString nickname;

    //Atributo que indica si hay bytes para leer
    qint64 bytesExpected;
    //Array de bytes con la informacion recibida del cliente
    QByteArray buffer;

};

#endif // USER_H
