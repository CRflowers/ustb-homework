QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    books/HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt \
    books/HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt \
    books/J.K. Rowling - HP 0 - Harry Potter Prequel.txt \
    books/J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt \
    books/J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt \
    books/J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt \
    books/J.K. Rowling - Quidditch Through the Ages.txt \
    books/J.K. Rowling - The Tales of Beedle the Bard.txt
