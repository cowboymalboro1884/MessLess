QT -= gui
QT += core
QT += network
QT += websockets

LIBS += -lpqxx -lpq -L /root/lpqxx

LIBS += -lboost_system

LIBS += -L/root/cryptopp -lcryptopp
INCLUDEPATH += /root/cryptopp

TARGET = server
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/chat_processor.cpp \
    src/client_handler.cpp \
    src/clientsocket_wrapper.cpp \
    src/main.cpp \
    src/project_processor.cpp \
    src/request_handler.cpp \
    src/server.cpp \
    src/database.cpp \
    src/database_chats.cpp \
    src/database_project.cpp \
    src/encrypting.cpp \
    src/task_processor.cpp \
    src/validating_processor.cpp

QMAKE_CXXFLAGS += -O2

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/client_handler.hpp \
    include/clientsocket_wrapper.hpp \
    include/errors_templates.hpp \
    include/query_types.hpp \
    include/request_handler.hpp \
    include/response_template.hpp \
    include/responses_types.hpp \
    include/server.hpp \
    include/encrypting.hpp \
    include/database.hpp \
    include/database_chats.hpp \
    include/database_project.hpp
