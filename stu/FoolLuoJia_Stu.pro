QT       += core gui network sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../common

SOURCES += \
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
    student.cpp \
    studentinfoedit.cpp \
    ../common/studentmanager.cpp\
    stumenu.cpp \
    userfilemanager.cpp \
    widget.cpp

HEADERS += \
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
    student.h \
    studentinfoedit.h \
    ../common/studentmanager.h\
    stumenu.h \
    userfilemanager.h \
    widget.h

FORMS += \
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
    student.ui \
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
