#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T11:44:06
#
#-------------------------------------------------

QT       += qml quick quickcontrols2 core network
QT       += sql

TARGET = ChatServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

RESOURCES += \
    qml.qrc

SOURCES += main.cpp \
    User.cpp \
    Server.cpp \
    Message.cpp \
    Chat.cpp \
    MessageAdapter.cpp \
    DBConnection.cpp \
    FileManager.cpp

HEADERS += \
    User.h \
    Server.h \
    Message.h \
    Chat.h \
    MessageAdapter.h \
    DBConnection.h \
    FileManager.h

DISTFILES += \
    main.qml \
    Page1.qml \
    Page1Form.ui.qml
