#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T15:26:52
#
#-------------------------------------------------

CONFIG  += warn_off

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phaze-3
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    chapter.cpp \
    client_socket.cpp \
    command.cpp \
    editor.cpp \
    tools.cpp \
    user.cpp \
    user_interface.cpp \
    utility.cpp \
    version.cpp \
    register.cpp \
    mainwindow.cpp \
    addbook.cpp \
    addchapter.cpp

HEADERS  += login.h \
    chapter.h \
    client_socket.h \
    command.h \
    editor.h \
    exeption.h \
    network_exception.h \
    tools.h \
    user.h \
    user_interface.h \
    utility.h \
    version.h \
    register.h \
    mainwindow.h \
    addbook.h \
    addchapter.h
FORMS    += login.ui \
    register.ui \
    mainwindow.ui \
    addbook.ui \
    addchapter.ui
