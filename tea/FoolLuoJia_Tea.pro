QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../common

SOURCES += \
    addbooks.cpp \
    addscore.cpp \
    campuslife.cpp \
    dormdistribute.cpp \
    dormtofix.cpp \
    answer_mth.cpp \
    getcomment.cpp \
    main.cpp \
    myserver.cpp \
    onlinelib.cpp \
    publishmovie.cpp \
    record.cpp \
    stucheck.cpp \
    teabank.cpp \
    teaclub.cpp \
    teaclubcomi.cpp \
    teaclubpub.cpp \
    teadorm.cpp \
    widget.cpp
    widget.cpp\
    ../common/studentmanager.cpp

HEADERS += \
    addbooks.h \
    addscore.h \
    campuslife.h \
    dormdistribute.h \
    dormtofix.h \
    answer_mth.h \
    getcomment.h \
    myserver.h \
    onlinelib.h \
    publishmovie.h \
    record.h \
    stucheck.h \
    teabank.h \
    teaclub.h \
    teaclubcomi.h \
    teaclubpub.h \
    teadorm.h \
    widget.h
    widget.h\
    ../common/studentmanager.h

FORMS += \
    addbooks.ui \
    addscore.ui \
    campuslife.ui \
    dormdistribute.ui \
    dormtofix.ui \
    answer_mth.ui \
    getcomment.ui \
    onlinelib.ui \
    publishmovie.ui \
    record.ui \
    stucheck.ui \
    teabank.ui \
    teaclub.ui \
    teaclubcomi.ui \
    teaclubpub.ui \
    teadorm.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
