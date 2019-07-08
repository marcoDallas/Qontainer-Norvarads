#-------------------------------------------------
#
# Project created by QtCreator 2018-12-16T23:23:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qontainer
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
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    container/container.cpp \
    container/deepptr.cpp \
    hierarchy/norvarad.cpp \
    hierarchy/nvdaconfused.cpp \
    hierarchy/nvdattack.cpp \
    hierarchy/nvddefense.cpp \
    hierarchy/nvddevo.cpp \
    hierarchy/nvdmaster.cpp \
    mv/mainwindow.cpp \
    mv/model.cpp \
    main.cpp \
    mv/centralwidget.cpp \
    mv/listview.cpp \
    mv/insertview.cpp \
    mv/listmodeladapter.cpp \
    mv/proxymodeladapter.cpp \
    mv/xmlutil.cpp

HEADERS += \
    container/container.h \
    container/deepptr.h \
    hierarchy/norvarad.h \
    hierarchy/nvdaconfused.h \
    hierarchy/nvdattack.h \
    hierarchy/nvddefense.h \
    hierarchy/nvddevo.h \
    hierarchy/nvdmaster.h \
    mv/mainwindow.h \
    mv/model.h \
    mv/centralwidget.h \
    mv/listview.h \
    mv/insertview.h \
    mv/listmodeladapter.h \
    mv/proxymodeladapter.h \
    mv/xmlutil.h

INCLUDEPATH += \
    container/ \
    hierarchy/ \
    mv/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
