#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T16:29:26
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoxSola
TEMPLATE = app


SOURCES += main.cpp\
        lockvoxsoladialog.cpp \
    mainvoxsoladialog.cpp

HEADERS  += lockvoxsoladialog.h \
    mainvoxsoladialog.h

FORMS    += lockvoxsoladialog.ui \
    mainvoxsoladialog.ui

RESOURCES += \
    MainResources/MainVoxSolaResources.qrc
