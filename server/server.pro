QT -= gui
QT += core
QT += network
QT += websockets

LIBS += -lpqxx -lpq -L /root/lpqxx -lboost_system -L/root/cryptopp -lcryptopp

INCLUDEPATH += /root/cryptopp

TARGET = server
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/chatmanager.cpp \
        src/clientsocket.cpp \
	src/database.cpp \
    src/databasechats.cpp \
	src/databaseproject.cpp \
	src/encrypting.cpp \
	src/main.cpp \
	src/requestholder.cpp \
	src/server.cpp

QMAKE_CXXFLAGS += -O2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/chatmanager.h \
    include/clientsocket.h \
    include/database.h \
    include/databasechats.h \
    include/databaseproject.h \
    include/encrypting.h \
    include/requestholder.h \
    include/responsetemplate.h \
    include/server.h
