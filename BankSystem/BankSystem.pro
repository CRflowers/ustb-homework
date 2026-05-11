QT       += core gui
QT       += sql         #提供SQL数据库支持

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    accountrecord.cpp \
    accumulator.cpp \
    creditaccount.cpp \
    date.cpp \
    error.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    savingsaccount.cpp

HEADERS += \
    account.h \
    accountrecord.h \
    accumulator.h \
    creditaccount.h \
    date.h \
    error.h \
    login.h \
    mainwindow.h \
    savingsaccount.h

FORMS += \
    error.ui \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
