#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T18:31:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gclient
TEMPLATE = app


SOURCES += main.cpp\
        gclient.cpp \
    msock.cpp

HEADERS  += gclient.h \
    msock.h

FORMS    += gclient.ui
