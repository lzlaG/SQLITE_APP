QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mutants.cpp \
    sqlite3.c \
    writeobject.cpp

HEADERS += \
    db.h \
    mainwindow.h \
    mutant.h \
    sqlite3.h \
    writeobject.h

FORMS += \
    mainwindow.ui

INCLUDEPATH+=$SQLITE/include" "LIBS+=-L$SQLITE/lib -lsqlite

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
