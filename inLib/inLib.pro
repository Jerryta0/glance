#-------------------------------------------------
#
# Project created by QtCreator 2020-06-07T19:45:29
#
#-------------------------------------------------

QT       += widgets

TARGET = inLib
TEMPLATE = lib

DEFINES += INLIB_LIBRARY

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
        inlib.cpp

HEADERS += \
        inlib.h \
        inlib_global.h  

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# 新建c++库-共享库(动态库)
