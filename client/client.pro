QT       += core
QT       += network
QT       += sql
QT       -= gui

#LIBD += -L/Users/maksimstein/Desktop/cryptopp/cryptopp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/add_user.cpp \
    src/add_user_window.cpp \
    src/delete_user.cpp \
    src/network_manager.cpp \
    src/add_project.cpp \
    src/add_task.cpp \
    src/auth_window.cpp \
    src/client.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/project_chat.cpp \
    src/project_settings.cpp \
    src/projectwindow.cpp \
    src/query_handler.cpp \
    src/reg_window.cpp \
    src/response_handler.cpp \
    src/socketwrapper.cpp \

HEADERS += \
    include/add_task.h \
    include/add_user.h \
    include/add_user_window.h \
    include/auth_window.h \
    include/client.h \
    include/delete_user.h \
    include/mainwindow.h \
    include/network_manager.h \
    include/project_settings.h \
    include/projectwindow.h \
    include/query_handler.h \
    include/reg_window.h \
    include/response_handler.h \
    include/response_types.h \
    include/socketwrapper.h \
    include/add_project.h \
    include/projectwindow.h \
    include/add_task.h \
    include/project_chat.h

FORMS += \
    include/add_user_window.ui \
    include/add_task.ui \
    include/add_user.ui \
    include/auth_window.ui \
    include/delete_user.ui \
    include/mainwindow.ui \
    include/project_chat.ui \
    include/project_settings.ui \
    include/projectwindow.ui \
    include/reg_window.ui \
    include/add_project.ui/ \
    include/projectwindow.ui \
    include/add_task.ui \

#win64:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    img/MessLess.ico \
    img/settings.png

RC_ICONS = MessLess.ico
