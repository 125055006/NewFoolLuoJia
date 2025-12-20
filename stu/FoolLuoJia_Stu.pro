QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankexpense.cpp \
    bankkr.cpp \
    banksearch.cpp \
    borrowbook.cpp \
    campuslife.cpp \
    choosecourse.cpp \
    consultscore.cpp \
    dormexchange.cpp \
    dormfix.cpp \
    main.cpp \
    myclient.cpp \
    resetps.cpp \
    stu_comment.cpp \
    stuacti.cpp \
    stuactijoin.cpp \
    stuactirec.cpp \
    stubank.cpp \
    student.cpp \
    studorm.cpp \
    stumenu.cpp \
    widget.cpp

HEADERS += \
    bankexpense.h \
    bankkr.h \
    banksearch.h \
    borrowbook.h \
    campuslife.h \
    choosecourse.h \
    consultscore.h \
    dormexchange.h \
    dormfix.h \
    myclient.h \
    resetps.h \
    stu_comment.h \
    stuacti.h \
    stuactijoin.h \
    stuactirec.h \
    stubank.h \
    student.h \
    studorm.h \
    stumenu.h \
    widget.h

FORMS += \
    bankexpense.ui \
    bankkr.ui \
    banksearch.ui \
    borrowbook.ui \
    campuslife.ui \
    choosecourse.ui \
    consultscore.ui \
    dormexchange.ui \
    dormfix.ui \
    resetps.ui \
    stu_comment.ui \
    stuacti.ui \
    stuactijoin.ui \
    stuactirec.ui \
    stubank.ui \
    student.ui \
    studorm.ui \
    stumenu.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
