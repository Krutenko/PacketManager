#include "packetmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PacketManager w;
    w.show();

    return a.exec();
}
