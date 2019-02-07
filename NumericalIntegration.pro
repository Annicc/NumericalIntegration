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

SOURCES += \
        main.cpp \
    mainwindow.cpp \
    numericalintegration.cpp \
    expression.cpp

HEADERS += \
    exprtk.hpp \
    mainwindow.h \
    numericalintegration.h \
    expression.h

FORMS += \
    mainwindow.ui

win32-msvc*{
    QMAKE_CXXFLAGS += -bigobj
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
