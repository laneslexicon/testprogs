#-------------------------------------------------
#
# Project created by QtCreator 2013-05-05T10:34:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testgraphics
TEMPLATE = app
LIBS -=   -lboost_thread-mt -lboost_system -lboost_filesystem
LIBS += -L $$[QT_INSTALL_LIBS]
MOC_DIR = ./moc
OBJECTS_DIR = ./obj
CONFIG += debug
QMAKE_CXXFLAGS += -Wunused-parameter
#RESOURCES=simple.qrc
#DEFINES += QT_NO_CAST_FROM_ASCII
SOURCES += testgraphics.cpp
