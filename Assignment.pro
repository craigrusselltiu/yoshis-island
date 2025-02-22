#-------------------------------------------------
#
# Project created by QtCreator 2019-03-27T20:58:31
#
#-------------------------------------------------

QT       += \
    core gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assignment
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    enemy.cpp \
        main.cpp \
        dialog.cpp \
    config.cpp \
    coordinate.cpp \
    character.cpp \
    background.cpp

HEADERS += \
        dialog.h \
    config.h \
    coordinate.h \
    enemy.h \
    image.h \
    character.h \
    background.h \
    imagefactory.h

FORMS += \
        dialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include/"

LIBS      += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win64"

CONFIG += resources_big
