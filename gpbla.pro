#-------------------------------------------------
#
# Project created by QtCreator 2018-02-19T11:08:53
#
#-------------------------------------------------

QT       += core gui
QT       += location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gpbla
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addmap.cpp \
    addbla.cpp \
    addaim.cpp \
    addobject.cpp \
    UAV.cpp \
    PVO.cpp \
    Point.cpp \
    Object.cpp \
    MapImage.cpp \
    Map.cpp \
    Image.cpp \
    GeoObject.cpp \
    ChangeHeight.cpp \
    Aim.cpp \
    warningadding.cpp \
    saveflight.cpp

HEADERS += \
        mainwindow.h \
    addmap.h \
    addbla.h \
    addaim.h \
    addobject.h \
    UAV.h \
    PVO.h \
    Point.h \
    Object.h \
    MapImage.h \
    Map.h \
    Image.h \
    GeoObject.h \
    ChangeHeight.h \
    Aim.h \
    warningadding.h \
    saveflight.h

FORMS += \
        mainwindow.ui \
    addmap.ui \
    addbla.ui \
    addaim.ui \
    addobject.ui \
    warningadding.ui \
    warningadding.ui \
    saveflight.ui
