#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QList>
#include <QDir>
#include <QFile>

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    //Setters
    void updateFilesOnFolder(const QString);
    void updateFilesOnEdit(const QString);
    void updateFilesOnRead(const QString);
    //Getters
    QList< QString > getFilesOnFolder() const;
    QList< QString > getFilesOnEdit() const;
    QList< QString > getFilesOnRead() const;

signals:

public slots:
    void uploadFile(); //exclusive use from de Server
    void editFile(QString);
    void readFile(QString);

private:
    QFile *file;
    QList< QString > filesOnFolder;
    QList< QString > filesOnEdit;
    QList< QString > filesOnRead;
};

#endif // FILEMANAGER_H
