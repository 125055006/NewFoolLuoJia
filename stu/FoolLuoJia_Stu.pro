QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    borrowbook.cpp \
    choosecourse.cpp \
    consultscore.cpp \
    main.cpp \
    mentalheal.cpp \
    movie.cpp \
    myclient.cpp \
    resetps.cpp \
    service.cpp \
    stu_comment.cpp \
    student.cpp \
    stumenu.cpp \
    widget.cpp

HEADERS += \
    borrowbook.h \
    choosecourse.h \
    consultscore.h \
    mentalheal.h \
    movie.h \
    myclient.h \
    resetps.h \
    service.h \
    stu_comment.h \
    student.h \
    stumenu.h \
    widget.h

FORMS += \
    borrowbook.ui \
    choosecourse.ui \
    consultscore.ui \
    mentalheal.ui \
    movie.ui \
    resetps.ui \
    service.ui \
    stu_comment.ui \
    student.ui \
    stumenu.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
