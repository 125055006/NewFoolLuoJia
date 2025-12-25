QT       += core gui network sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../common

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
    CampusFeedback.cpp \
    SchoolCalendarWidget.cpp \
    borrowbook.cpp \
    bus.cpp \
    campusinfowidget.cpp \
    choosecourse.cpp \
    consultscore.cpp \
    facility.cpp \
    facilityreservation.cpp \
    main.cpp \
    mentalheal.cpp \
    messagecenter.cpp \
    movie.cpp \
    myclient.cpp \
    phonebooklogic.cpp \
    register.cpp \
    resetps.cpp \
    service.cpp \
    stu_comment.cpp \
    stuacti.cpp \
    stuactijoin.cpp \
    stuactirec.cpp \
    stubank.cpp \
    student.cpp \
    studorm.cpp \
    studentinfoedit.cpp \
    ../common/studentmanager.cpp\
    stumenu.cpp \
    userfilemanager.cpp \
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
    CampusFeedback.h \
    SchoolCalendarWidget.h \
    borrowbook.h \
    bus.h \
    campusinfowidget.h \
    choosecourse.h \
    consultscore.h \
    facility.h \
    facilityreservation.h \
    mentalheal.h \
    messagecenter.h \
    movie.h \
    myclient.h \
    phonebooklogic.h \
    register.h \
    resetps.h \
    service.h \
    stu_comment.h \
    stuacti.h \
    stuactijoin.h \
    stuactirec.h \
    stubank.h \
    student.h \
    studorm.h \
    studentinfoedit.h \
    ../common/studentmanager.h\
    stumenu.h \
    userfilemanager.h \
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
    CampusFeedback.ui \
    SchoolCalendarWidget.ui \
    borrowbook.ui \
    bus.ui \
    campusinfowidget.ui \
    choosecourse.ui \
    consultscore.ui \
    facility.ui \
    facilityreservation.ui \
    mentalheal.ui \
    messagecenter.ui \
    movie.ui \
    phonebooklogic.ui \
    register.ui \
    resetps.ui \
    service.ui \
    stu_comment.ui \
    stuacti.ui \
    stuactijoin.ui \
    stuactirec.ui \
    stubank.ui \
    student.ui \
    studorm.ui \
    studentinfoedit.ui \
    stumenu.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    bus.qrc

SUBDIRS += \
    ../../CampusInfoWidget/CampusInfoWidget.pro
