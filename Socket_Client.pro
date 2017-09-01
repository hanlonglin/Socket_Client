#-------------------------------------------------
#
# Project created by QtCreator 2017-08-31T13:55:08
#
#-------------------------------------------------

QT       += core gui
QT       += network

RC_ICONS = qq.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Socket_Client
TEMPLATE = app

VERSION= 1.0.0.2

SOURCES += main.cpp\
        mainwindow.cpp \
    chatwindow.cpp \
    tcptools.cpp

HEADERS  += mainwindow.h \
    chatwindow.h \
    tcptools.h \
    common.h

FORMS    += mainwindow.ui \
    chatwindow.ui
