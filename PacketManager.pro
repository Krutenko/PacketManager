#-------------------------------------------------
#
# Project created by QtCreator 2019-09-09T11:19:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacketManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += WIN32
DEFINES += WPCAP
DEFINES += HAVE_REMOTE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

LIBS += user32.lib
LIBS += $$PWD/WpdPack/Lib/wpcap.lib
LIBS += $$PWD/WpdPack/Lib/Packet.lib

INCLUDEPATH += $$PWD/WpdPack/Include

SOURCES += \
        main.cpp \
        packetmanager.cpp \
    ipdialog.cpp \
    tcpdialog.cpp \
    udpdialog.cpp \
    icmpdialog.cpp \
    ippacket.cpp \
    unipacket.cpp \
    tcppacket.cpp \
    udppacket.cpp \
    icmppacket.cpp \
    qfulltablewidget.cpp \
    commonpacket.cpp \
    packetsender.cpp \
    interfacedialog.cpp

HEADERS += \
        packetmanager.h \
    ipdialog.h \
    tcpdialog.h \
    udpdialog.h \
    icmpdialog.h \
    ippacket.h \
    unipacket.h \
    tcppacket.h \
    udppacket.h \
    icmppacket.h \
    qfulltablewidget.h \
    commonpacket.h \
    packetsender.h \
    interfacedialog.h

FORMS += \
        packetmanager.ui \
    ipdialog.ui \
    tcpdialog.ui \
    udpdialog.ui \
    icmpdialog.ui \
    interfacedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
