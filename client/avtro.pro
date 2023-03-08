QT       += core
QT       += network
QT       += sql
QT       -= gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/auth_window.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/projectwindow.cpp \
    src/reg_window.cpp

HEADERS += \
    include/auth_window.h \
    include/mainwindow.h \
    include/projectwindow.h \
    include/reg_window.h \
    include/projectwindow.h

FORMS += \
    include/auth_window.ui \
    include/mainwindow.ui \
    include/projectwindow.ui \
    include/reg_window.ui \
    include/projectwindow.ui

#win64:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
