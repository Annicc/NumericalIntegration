#-------------------------------------------------
#
# Project created by QtCreator 2019-02-03T21:58:33
#
#-------------------------------------------------

QT += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumericalIntegration
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

QMAKE_CXXFLAGS += -bigobj

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    mainwindow.cpp \
    numericalintegration.cpp

HEADERS += \
    exprtk.hpp \
    mainwindow.h \
    mainwindow.h \
    numericalintegration.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
