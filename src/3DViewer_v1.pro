QT       += core gui opengl openglwidgets
include(QtGifImage/gifimage/qtgifimage.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    model/model.cc \
#    model/moving.cc \
    model/connect.cc \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    options.cpp

HEADERS += \
#    model/model.h \
#    model/moving.h \
    model/connect.h \
    glview.h \
    mainwindow.h \
    options.h

FORMS += \
    mainwindow.ui \
    options.ui

macx:ICON = $${PWD}/icon/3DviewerLogo.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
