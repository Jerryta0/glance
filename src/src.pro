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
    bean/document.cpp \
    custom/EditMd.cpp \
    custom/FolderTreeView.cpp \
    custom/MdGraphicsTextItem.cpp \
    custom/PreviewPage.cpp \
    custom/QTabPageWidget.cpp \
    custom/TextEditor.cpp \
    custom/mdgraphicsview.cpp \
    custom/mindscrollarea.cpp \
        main.cpp \
    custom/mindnodewidget.cpp

HEADERS += \
    MainWindow.h \
    bean/JsonFileOfMind.h \
    bean/MindNodeModel.h \
    bean/document.h \
    custom/EditMd.h \
    custom/FolderTreeView.h \
    custom/MdGraphicsTextItem.h \
    custom/MdGraphicsView.h \
    custom/MindNodeWidget.h \
    custom/MindScrollArea.h \
    custom/PreviewPage.h \
    custom/QTabPageWidget.h \
    custom/TextEditor.h \
    common/systemConsts.h


FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# add lib需要的东西
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../inLib/release/ -linLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../inLib/debug/ -linLib
else:unix: LIBS += -L$$OUT_PWD/../inLib/ -linLib

INCLUDEPATH += $$PWD/../inLib
DEPENDPATH += $$PWD/../inLib

RESOURCES += \
    res.qrc


# 国际化
TRANSLATIONS = myI18N_zh_CN.ts

DISTFILES +=


