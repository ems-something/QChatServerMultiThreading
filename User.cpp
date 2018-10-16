#include "User.h"

User::User(qintptr handle) :
    sockHandle(handle), nickname("")
{

}

void User::setNickname(const QString nickname)
{

    this->nickname = nickname;
}


QString User::getNickname() const
{

    return nickname;
}


bool User::clientAuthentication(const QString nickname, const QString password)
{

    QString myQuery("SELECT nickname, password FROM users WHERE nickname='");
    myQuery += nickname;
    myQuery += "' and password='";
    myQuery += password;
    myQuery += "';";

    QSqlQuery query(myQuery, dbHandle->getDB());
    query.first();

    QString nick = query.value(0).toString();
    QString pass = query.value(1).toString();


    if((nickname == nick) && (password == pass)){

        qDebug() << "Cliente Autenticado!!" <<endl;

        setNickname(nickname);

        emit newAuthenticatedClient(nickname, QString::number(sockHandle));

        return true;
    }

    return false;

}


void User::processClient()
{

    //Make a new socket
    socket = new QTcpSocket(this);


    qDebug() << "A new socket created!" << endl;

    if(!socket->setSocketDescriptor(sockHandle))
    {
        emit error(socket->error());
        return;
     }

     dbHandle = new DBConnection(this, QString::number(sockHandle));

     dbHandle->connectToDB();

    qDebug() << "Client connected at " << sockHandle << " on thread: " << QThread::currentThreadId() << endl;

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected())); //is it useful?
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

}


void User::onClientListUpdated(QStringList clients)
{

   QVariantMap map;
   QJsonObject object;
   QJsonDocument document;

   clients.removeOne(nickname);

   qDebug() << "clients: " << endl;

   for(int i = 0; i < clients.size(); i++){

       qDebug() << clients.at(i) << endl;
   }

   if(!clients.isEmpty())
   {
       map.insert("service", clientListUpdate);
       map.insert("users", clients);

       //Transformamos la data en un doc JSON
       object = QJsonObject::fromVariantMap(map);
       document.setObject(object);

       //Enviamos la data encapsulada en un doc JSON, al cliente.
       socket->write(document.toJson());

       socket->flush();

   }

}


void User::displayError(QAbstractSocket::SocketError error)
{
    qDebug() << "Error: " << error << endl;
}


void User::onConnected()
{
    qDebug() << "Client connected" << endl;
}


void User::onDisconnected()
{
    qDebug() << "Client disconnected" << endl;

    dbHandle->disconnectFromDB();

    emit clientDisconnected(nickname);
    emit clientDisconnected();
}


void User::onReadyRead()
{

    //Llamada cada vez que un cliente envia datos,
    //lee los paquetes de bytes y los concatena en "buffer"
    /*if((bytesExpected == 0) && (socket->bytesAvailable() >= sizeof(bytesExpected)))
    {
        socket->read((char *)&bytesExpected, sizeof(bytesExpected));

        qDebug() << "Expecting:" << &bytesExpected << endl;
        buffer += bytesExpected;
    }


    if((bytesExpected > 0) && (socket->bytesAvailable() > 0))
    {
        QByteArray chunk = socket->read(qMin(bytesExpected, socket->bytesAvailable()));
        buffer += chunk;
        bytesExpected -= chunk.size();

        qDebug() << "Received chunk of:" << chunk.size() << endl;

        //Una vez leido todos los datos,
        //se llama a data complete,
        //se guarda el archivo,
        //y pasa su proceso resectivo a la cola de procesos.

        if (bytesExpected == 0)
        {
           qDebug() << "Received block of size:" << buffer.size() << endl;
           qDebug() << "Bytes left in socket:" << socket->bytesAvailable() << endl;

            socket->deleteLater();
         }

        if (chunk.contains("}"))
        {
            qDebug() << buffer ;
            processRequest();
        }
    }*/


    //Metodo llamado cada vez que el servidor envia un informacion

    //Llamada cada vez que el servidor envia informacion
    QByteArray bytes = socket->readAll();
    QJsonDocument document = QJsonDocument::fromJson(bytes);
    QVariantMap result = document.toVariant().toMap();

    qDebug() << result << endl;

    processRequest(result);

}


//Metodo llamado cuando se recibio la data completa
void User::processRequest(QVariantMap request)
{

    qDebug() << "inside processRequest()" << endl;

    //logIn, newChat, newMessage, newFile, readFile, editFile


    if (request.contains("service"))
    {
        qDebug() << "Servicio: " << request.value("service").toInt() << endl;

        switch(request.value("service").toInt())
        {

            case logIn:

                qDebug() << "nickname: " << request.value("nickname").toString() <<endl << "password: " << request.value("password").toString() << endl;

                if(request.contains("nickname") && request.contains("password"))
                {

                    qDebug() << "Solicitud de logIn aceptada" << endl;

                    QVariantMap map;
                    QJsonObject object;
                    QJsonDocument document;

                    map.insert("service", logIn);
                    map.insert("nickname", request.value("nickname").toString());
                    map.insert("pass", clientAuthentication(request.value("nickname").toString(), request.value("password").toString()));

                    //Transformamos la data en un doc JSON
                    object = QJsonObject::fromVariantMap(map);
                    document.setObject(object);

                    //Enviamos la data encapsulada en un doc JSON, al cliente.
                    socket->write(document.toJson());

                    socket->flush();

                }

             break;


             case newChat:

                if(request.contains("members") && request.contains("isGroup"))
                {
                    if(request.contains("groupName"))
                    {

                         if(request.value("isGroup").toBool())
                         {
                             emit newChatRequest(request.value("members").toStringList(), request.value("groupName").toString());
                         }
                         else
                         {

                             emit newChatRequest(request.value("members").toStringList(), "DEFAULT_NAME");
                         }
                    }

                }

            break;


            case newMessage:

                if(request.contains("from") && request.contains("to"))
                {
                    if(request.contains("body") && request.contains("date"))
                    {
                        newMessageArrived(request.value("from").toString(), request.value("to").toString(),
                                          request.value("body").toString(), request.value("date").toDate());

                        qDebug() <<"from: " << request.value("from").toString() << endl;

                        qDebug() << "to: " << request.value("to").toString() << endl;

                        qDebug() << "body: " << request.value("body").toString() << endl;

                        qDebug() << "date: " << request.value("date").toString() << endl;
                    }

                }

            break;


            case newFile:

                //if(request.contains("") && request.contains(""))
                {

                    //El flujo de datos correspondiente al archivo recibido,
                    //lo guardamos en un archivo con el mismo nombre,
                    //en la carpeta ../../debug/Archivos de Impresion/
                    /*QFile file(QString(QDir::currentPath()).toLatin1() + "/debug/Archivos de Impresion/" + dataFile->getFileName());
                    file.open(QIODevice::Append);
                    file.write(QByteArray::fromBase64(result["file"].toByteArray()));
                    file.close();*/
                }

            break;


            case readFile:

                //if(request.contains("") && request.contains(""))
                {


                }

            break;


            case editFile:

                //if(request.contains("") && request.contains(""))
                {


                }

            break;


            default:


            break;

        }

    }


    //Actualizamos la GUI
    //qmlUpdateTable();

    //Limpiamos el buffer de datos recibidos
    /*buffer.clear();
    bytesExpected = 0;*/

}


void User::sendResponse()
{



}

