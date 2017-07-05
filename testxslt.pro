#-------------------------------------------------
#gcc -o test_xslt -L /opt/lib -lxml2 -lxslt -I/opt/include/libxml2 test.c
#
#-------------------------------------------------

QT       += core sql xml

QT       -= gui
CONFIG   += debug
TARGET = testxslt
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -pthread -Wunused-parameter -g
INCLUDEPATH += /usr/local/include/libxml2 /usr/include/libxml2
INCLUDEPATH += /usr/local/include
LIBS += -L $$[QT_INSTALL_LIBS]  -lxml2 -lxslt
OBJECTS_DIR = ./obj
MOC_DIR = ./moc

SOURCES += testxslt.cpp
