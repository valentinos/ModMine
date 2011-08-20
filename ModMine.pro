#-------------------------------------------------
#
# Project created by QtCreator 2011-08-20T03:01:09
#
#-------------------------------------------------

QT       += core gui

TARGET = ModMine

TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    menu.cpp \
    easyzip.cpp \
    quazip/zip.c \
    quazip/unzip.c \
    quazip/quazipnewinfo.cpp \
    quazip/quazipfile.cpp \
    quazip/quazip.cpp \
    quazip/quacrc32.cpp \
    quazip/quaadler32.cpp \
    quazip/qioapi.cpp \
    quazip/JlCompress.cpp

HEADERS += \
    mainwindow.h \
    menu.h \
    easyzip.h \
    quazip/zip.h \
    quazip/unzip.h \
    quazip/quazipnewinfo.h \
    quazip/quazip_global.h \
    quazip/quazipfileinfo.h \
    quazip/quazipfile.h \
    quazip/quazip.h \
    quazip/quacrc32.h \
    quazip/quachecksum32.h \
    quazip/quaadler32.h \
    quazip/JlCompress.h \
    quazip/ioapi.h \
    quazip/crypt.h

FORMS += \
    mainwindow.ui \
    menu.ui
