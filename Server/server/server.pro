QT -= gui
QT += core
QT += network
QT += websockets

LIBS += -lpq -lpqxx

TARGET = server
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        clientsocket.cpp \
#        database.cpp \
#        encrypting.cpp \
    database.cpp \
    encrypting.cpp \
        main.cpp \
        server.cpp

QMAKE_CXXFLAGS += -O2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    clientsocket.h \
#    database.h \
#    encrypting.h \
    database.h \
    encrypting.h \
    server.h
