QT       += core gui
QT       += multimedia
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    bullet.cpp \
    enemyplane.cpp \
    gamescene.cpp \
    gameview.cpp \
    main.cpp \
    mainwindow.cpp \
    plane.cpp \
    playerplane.cpp \
    power.cpp \
    shoot.cpp \
    track.cpp \
    wave.cpp

HEADERS += \
    background.h \
    bullet.h \
    enemyplane.h \
    gamescene.h \
    gameview.h \
    mainwindow.h \
    plane.h \
    playerplane.h \
    power.h \
    shoot.h \
    track.h \
    wave.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
