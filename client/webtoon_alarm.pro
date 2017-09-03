#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T15:54:11
#
#-------------------------------------------------

QT += core gui
QT += websockets
QT -= gui
QT += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webtoon_alarm
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle


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
    client.cpp \
    webtoon.cpp \
    favorite.cpp \
    linkbutton.cpp \
    favoritebutton.cpp \
    filedownloader.cpp

HEADERS += \
        mainwindow.h \
    client.h \
    webtoon.h \
    favorite.h \
    linkbutton.h \
    favoritebutton.h \
    filedownloader.h

FORMS += \
        mainwindow.ui

# for boost library
#INCLUDEPATH += C:\boost_1_64_0\boost_1_64_0
#LIBS += -L C:\boost_1_64_0\boost_1_64_0\stage\lib\libboost_chrono-mgw53-mt-1_64.a
#LIBS += -L C:\boost_1_64_0\boost_1_64_0\stage\lib\libboost_filesystem-mgw53-mt-1_64.a
#LIBS += -L C:\boost_1_64_0\boost_1_64_0\stage\lib\libboost_system-mgw53-mt-1_64.a
#LIBS += -L C:\boost_1_64_0\boost_1_64_0\stage\lib\libboost_thread-mgw53-mt-1_64.a
#LIBS += -L C:\boost_lib\boost\bin.v2\libs\chrono\build\gcc-mingw-5.3.0\release\link-static\threading-multi\libboost_chrono-mgw53-mt-1_64.a
#LIBS += -L C:\boost_lib\boost\bin.v2\libs\thread\build\gcc-mingw-5.3.0\release\link-static\threading-multi\libboost_thread-mgw53-mt-1_64.a
#LIBS += -L C:\boost_lib\boost\bin.v2\libs\system\build\gcc-mingw-5.3.0\release\link-static\threading-multi\libboost_system-mgw53-mt-1_64.a
#LIBS += -L C:\boost_lib\boost\bin.v2\libs\filesystem\build\gcc-mingw-5.3.0\release\link-static\threading-multi\libboost_filesystem-mgw53-mt-1_64.a
