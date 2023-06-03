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
    include/network_manager.cpp \
    src/add_project.cpp \
    src/add_task.cpp \
    src/auth_window.cpp \
    src/client.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/projectwindow.cpp \
    src/query_handler.cpp \
    src/reg_window.cpp \
    src/response_handler.cpp \
    src/socketwrapper.cpp \

HEADERS += \
    include/add_task.h \
    include/auth_window.h \
    include/client.h \
    include/mainwindow.h \
    include/network_manager.h \
    include/projectwindow.h \
    include/query_handler.h \
    include/reg_window.h \
    include/response_handler.h \
    include/response_types.h \
    include/socketwrapper.h \
    include/add_project.h \
    include/projectwindow.h \
    include/add_task.h

FORMS += \
    include/add_task.ui \
    include/auth_window.ui \
    include/mainwindow.ui \
    include/projectwindow.ui \
    include/reg_window.ui \
    include/add_project.ui/ \
    include/projectwindow.ui \
    include/add_task.ui

#win64:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    img/settings.png
