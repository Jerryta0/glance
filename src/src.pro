#-------------------------------------------------
#
# Project created by QtCreator 2020-06-07T19:42:04
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
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

CONFIG += c++11

SOURCES += \
    MainWindow.cpp \
    bean/JsonFileOfMind.cpp \
    bean/MindNodeModel.cpp \
    common/GolbalVar.cpp \
    custom/EditMd.cpp \
    custom/FolderTreeView.cpp \
    custom/MdGraphicsTextItem.cpp \
    custom/MindNodeWidget.cpp \
    custom/MindScrollArea.cpp \
    custom/QTabPageWidget.cpp \
    custom/TextEditor.cpp \
    custom/mdgraphicsview.cpp \
        main.cpp

HEADERS += \
    MainWindow.h \
    bean/JsonFileOfMind.h \
    bean/MindNodeModel.h \
    common/GolbalVar.h \
    custom/EditMd.h \
    custom/FolderTreeView.h \
    custom/MdGraphicsTextItem.h \
    custom/MdGraphicsView.h \
    custom/MindNodeWidget.h \
    custom/MindScrollArea.h \
    custom/QTabPageWidget.h \
    custom/TextEditor.h \
    common/systemConsts.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    res.qrc


# 国际化
TRANSLATIONS = myI18N_zh_CN.ts
# 动态库
DISTFILES +=



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/Hoedown/release/ -lHoedown
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/Hoedown/debug/ -lHoedown
else:unix: LIBS += -L$$OUT_PWD/../lib/Hoedown/ -lHoedown

INCLUDEPATH += $$PWD/../lib/Hoedown
DEPENDPATH += $$PWD/../lib/Hoedown
