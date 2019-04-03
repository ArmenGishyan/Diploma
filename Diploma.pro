#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T13:45:25
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Diploma
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
        main.cpp \
        mainwindow.cpp \
    command.cpp \
    graph.cpp \
    point.cpp \
    polygons.cpp \
    editor.cpp \
    graphicsview.cpp \
    gaction.cpp \
    gstyledialog.cpp \
    ggraphicsshapesitem.cpp \
    ggraphicsitems.cpp \

HEADERS += \
        mainwindow.h \
    command.h \
    graph.h \
    point.h \
    polygons.h \
    shape.h \
    editor.h \
    graphicsview.h \
    gaction.h \
    gstyledialog.h \
    shortestpathproblem.h \
    ggraphicsshapesitem.h \
    ggraphicsitems.h

FORMS += \
        mainwindow.ui
RESOURCES += ./resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
