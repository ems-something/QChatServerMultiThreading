#include "FileManager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}


void FileManager::updateFilesOnFolder(const QString)
{


}


void FileManager::updateFilesOnEdit(const QString)
{


}


void FileManager::updateFilesOnRead(const QString)
{


}

QList< QString > FileManager::getFilesOnFolder() const
{

    return filesOnFolder;
}


QList< QString > FileManager::getFilesOnEdit() const
{

    return filesOnEdit;
}


QList< QString > FileManager::getFilesOnRead() const
{

    return filesOnRead;
}


void FileManager::uploadFile()
{


}


void FileManager::editFile(QString path)
{


}


void FileManager::readFile(QString path)
{



}
