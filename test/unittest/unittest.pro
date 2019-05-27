#-------------------------------------------------
#
# Project created by QtCreator 2019-05-27T10:37:13
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = unittest_leveleditor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($$PWD/../../src/app/app.pri)
include($$PWD/testapp/testapp.pri)

SOURCES += \
    tst_main.cpp

HEADERS += \
    macro_for_test.h

