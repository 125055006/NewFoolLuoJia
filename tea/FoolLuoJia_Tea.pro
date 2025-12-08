QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbooks.cpp \
    addscore.cpp \
    getcomment.cpp \
    main.cpp \
    myserver.cpp \
    onlinelib.cpp \
    record.cpp \
    stucheck.cpp \
    widget.cpp

HEADERS += \
    addbooks.h \
    addscore.h \
    getcomment.h \
    myserver.h \
    onlinelib.h \
    record.h \
    stucheck.h \
    widget.h

FORMS += \
    addbooks.ui \
    addscore.ui \
    getcomment.ui \
    onlinelib.ui \
    record.ui \
    stucheck.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
