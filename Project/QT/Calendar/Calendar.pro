QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddatefestival.cpp \
    addweekdayfestival.cpp \
    background.cpp \
    deletfestival.cpp \
    dialogabout.cpp \
    dialoglanguage.cpp \
    findfestival.cpp \
    instruction.cpp \
    main.cpp \
    mainwindow.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\CalendarController.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\Month.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\WeekDay.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\Date.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\Festival.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\DateFestival.cpp \
    D:\\VScode\\cpp(code_runner)\\test\\WeekDayFestival.cpp \
    resetdatefestival.cpp \
    resetweekdayfestival.cpp \
    setting.cpp \
    sortfestival.cpp

HEADERS += \
    adddatefestival.h \
    addweekdayfestival.h \
    background.h \
    deletfestival.h \
    dialogabout.h \
    dialoglanguage.h \
    findfestival.h \
    instruction.h \
    mainwindow.h \
    D:\\VScode\\cpp(code_runner)\\test\\CalendarController.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\Month.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\WeekDay.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\Date.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\Festival.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\DateFestival.hpp \
    D:\\VScode\\cpp(code_runner)\\test\\WeekDayFestival.hpp \
    resetdatefestival.h \
    resetweekdayfestival.h \
    setting.h \
    sortfestival.h

FORMS += \
    adddatefestival.ui \
    addweekdayfestival.ui \
    background.ui \
    deletfestival.ui \
    dialogabout.ui \
    dialoglanguage.ui \
    findfestival.ui \
    instruction.ui \
    mainwindow.ui \
    resetdatefestival.ui \
    resetweekdayfestival.ui \
    setting.ui \
    sortfestival.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
