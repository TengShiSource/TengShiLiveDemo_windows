#-------------------------------------------------
#
# Project created by QtCreator 2021-05-18T07:58:12
#
#-------------------------------------------------

QT       += core gui \
            network \
            avwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TengShiLiveDemo
TEMPLATE = app

RC_FILE += icon.rc

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
    HistoryClassDialog.cpp \
    HistoryCourse.cpp \
    VideoDialog.cpp \
    VideoInfos.cpp \
        main.cpp \
        mainwindow.cpp \
    appSetupDialog.cpp \
    config.cpp \
    util.cpp \
    NetWork.cpp \
    courseCreateDialog.cpp \
    global.cpp \
    helpAppConfigdialog.cpp

HEADERS += \
    HistoryClassDialog.h \
    HistoryCourse.h \
    VideoDialog.h \
    VideoInfos.h \
        mainwindow.h \
    appSetupDialog.h \
    config.h \
    util.h \
    NetWork.h \
    courseCreateDialog.h \
    global.h \
    helpAppConfigdialog.h

FORMS += \
    HistoryClassDialog.ui \
    VideoDialog.ui \
        mainwindow.ui \
    appSetupDialog.ui \
    courseCreateDialog.ui \
    helpAppConfigdialog.ui

RESOURCES += \
    images.qrc

win32: LIBS += -L$$PWD/lib/ -lQtAV1

win32: LIBS += -L$$PWD/lib/ -lQtAVWidgets1

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
