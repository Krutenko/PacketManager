#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QCursor>
#include <QStringList>

#include <vector>
#include <fstream>
#include <regex>
#include "packetsender.h"
#include <Windows.h>

#include "ipdialog.h"
#include "tcpdialog.h"
#include "udpdialog.h"
#include "icmpdialog.h"
#include "unipacket.h"
#include "interfacedialog.h"
#include "qfulltablewidget.h"

using namespace std;

namespace Ui {
class PacketManager;
}

class PacketManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit PacketManager(QWidget *parent = nullptr);
    ~PacketManager();
    vector<uniPacket*> packets;

private slots:
    void loadFile();
    void IPpktmgr();
    void TCPpktmgr();
    void UDPpktmgr();
    void ICMPpktmgr();
    void displayMenu();
    void editPacket();
    void deletePacket();
    void exportPacket();
    void sendPacket();
    void rawPacket();
    void nextPreview();
    void prevPreview();
    void sendPackets();

private:
    Ui::PacketManager *ui;
    QMenu *fileMenu;
    QAction *loadFileAction;
    QGridLayout *mainLayout;
    QPushButton *ipButton;
    QPushButton *tcpButton;
    QPushButton *udpButton;
    QPushButton *icmpButton;
    QLabel *pktLabel;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QFullTableWidget *previewTable;
    QTableWidgetItem *previewTableItem[4][2];
    QMenu *contextMenu;
    QAction *editAction;
    QAction *deleteAction;
    QAction *exportAction;
    QAction *rawAction;
    QAction *sendAction;
    QPushButton *sendButton;
    ipDialog *ipWindow;
    tcpDialog *tcpWindow;
    udpDialog *udpWindow;
    icmpDialog *icmpWindow;
    InterfaceDialog *intWindow;
    vector<pcap_if_t*> interfaces;
    vector<string> intNames;
    int curPacket;
    void displayCurrent(int cur);
};

#endif
