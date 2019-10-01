#include "packetmanager.h"
#include "ui_packetmanager.h"

PacketManager::PacketManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PacketManager)
{
    int i, j;
    QRect rect;
    QPalette palette;
    ui->setupUi(this);
    fileMenu = new QMenu(this);
    loadFileAction = new QAction(this);
    mainLayout = new QGridLayout(this);
    ipButton = new QPushButton(this);
    tcpButton = new QPushButton(this);
    udpButton = new QPushButton(this);
    icmpButton = new QPushButton(this);
    previewTable = new QFullTableWidget(this);
    pktLabel = new QLabel(this);
    nextButton = new QPushButton(this);
    prevButton = new QPushButton(this);
    contextMenu = new QMenu(this);
    editAction = new QAction(this);
    deleteAction = new QAction(this);
    exportAction = new QAction(this);
    rawAction = new QAction(this);
    sendAction = new QAction(this);
    sendButton = new QPushButton(this);
    pcap_if_t *alldevs, *d;
    alldevs = PacketSender::getInt();
    for(d = alldevs; d != NULL; d = d->next)
    {
        if (d->addresses->next->addr->sa_family == AF_INET)
            interfaces.push_back(d);
    }
    for (i = 0; i < interfaces.size(); i++)
    {
        pcap_addr_t *a;
        int flag = 0;
        a = interfaces[i]->addresses->next;
        string tmp = string(CommonPacket::iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
        istringstream iss(interfaces[i]->description);
        string token;
        while (std::getline(iss, token, '\''))
        {
            if (flag == 1)
                intNames.push_back(token + ' ' + tmp);
            flag++;
        }
    }
    setWindowTitle("Packet Manager");
    rect = QApplication::desktop()->screenGeometry();
    int x = rect.width() * 2 / 10;
    int y = rect.height() * 2 / 10;
    int w = rect.width() * 6 / 10;
    int h = rect.height() * 6 / 10;
    this->QMainWindow::setGeometry(x, y, w, h);
    fileMenu->setTitle("File");
    loadFileAction->setText("Load from file");
    loadFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction(loadFileAction);
    this->menuBar()->addMenu(fileMenu);
    curPacket = -1;
    for (i = 0; i < 9; i++)
        mainLayout->setColumnStretch(i, 1);
    for (i = 0; i < 10; i++)
        mainLayout->setRowStretch(i, 1);
    ipButton->setText("IP");
    tcpButton->setText("TCP");
    udpButton->setText("UDP");
    icmpButton->setText("ICMP");
    pktLabel->setText("0/0");
    pktLabel->setAlignment(Qt::AlignCenter);
    nextButton->setText("Next");
    prevButton->setText("Prev");
    previewTableItem[0][0] = new QTableWidgetItem(QString("Protocol:"));
    previewTableItem[1][0] = new QTableWidgetItem(QString("Interface:"));
    previewTableItem[2][0] = new QTableWidgetItem(QString("Destination:"));
    previewTableItem[3][0] = new QTableWidgetItem(QString("Message:"));
    previewTableItem[0][1] = new QTableWidgetItem(QString(""));
    previewTableItem[1][1] = new QTableWidgetItem(QString(""));
    previewTableItem[2][1] = new QTableWidgetItem(QString(""));
    previewTableItem[3][1] = new QTableWidgetItem(QString(""));
    previewTable->setRowCount(4);
    previewTable->setColumnCount(2);
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++)
        {
            previewTableItem[i][j]->setTextAlignment(Qt::AlignTop);
            previewTableItem[i][j]->setFlags(Qt::NoItemFlags);
            previewTable->setItem(i, j, previewTableItem[i][j]);
        }
    previewTable->horizontalHeader()->setStretchLastSection(1);
    previewTable->horizontalHeader()->hide();
    previewTable->verticalHeader()->setStretchLastSection(1);
    previewTable->verticalHeader()->hide();
    palette = previewTable->palette();
    palette.setBrush(QPalette::Text, QBrush(Qt::black));
    previewTable->setPalette(palette);
    editAction->setText("Edit");
    deleteAction->setText("Delete");
    exportAction->setText("Export to file");
    rawAction->setText("Get raw");
    sendAction->setText("Send");
    contextMenu->addAction(editAction);
    contextMenu->addAction(deleteAction);
    contextMenu->addAction(exportAction);
    contextMenu->addAction(rawAction);
    contextMenu->addAction(sendAction);
    sendButton->setText("Send all");
    sendButton->setEnabled(false);
    nextButton->setEnabled(false);
    prevButton->setEnabled(false);
    mainLayout->addWidget(ipButton, 0, 1);
    mainLayout->addWidget(tcpButton, 0, 3);
    mainLayout->addWidget(udpButton, 0, 5);
    mainLayout->addWidget(icmpButton, 0, 7);
    mainLayout->addWidget(previewTable, 2, 1, 6, 7);
    mainLayout->addWidget(pktLabel, 8, 4);
    mainLayout->addWidget(nextButton, 8, 5);
    mainLayout->addWidget(prevButton, 8, 3);
    mainLayout->addWidget(sendButton, 9, 8);
    ui->centralWidget->setLayout(mainLayout);
    connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(loadFile()));
    connect(ipButton, SIGNAL(released()), this, SLOT(IPpktmgr()));
    connect(tcpButton, SIGNAL(released()), this, SLOT(TCPpktmgr()));
    connect(udpButton, SIGNAL(released()), this, SLOT(UDPpktmgr()));
    connect(icmpButton, SIGNAL(released()), this, SLOT(ICMPpktmgr()));
    connect(previewTable, SIGNAL(rightClicked()), this, SLOT(displayMenu()));
    connect(editAction, SIGNAL(triggered()), this, SLOT(editPacket()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deletePacket()));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportPacket()));
    connect(rawAction, SIGNAL(triggered()), this, SLOT(rawPacket()));
    connect(sendAction, SIGNAL(triggered()), this, SLOT(sendPacket()));
    connect(nextButton, SIGNAL(released()), this, SLOT(nextPreview()));
    connect(prevButton, SIGNAL(released()), this, SLOT(prevPreview()));
    connect(sendButton, SIGNAL(released()), this, SLOT(sendPackets()));
}

void PacketManager::displayCurrent(int cur)
{
    if (cur < -1 || cur >= (int) packets.size())
        return;
    if (cur == -1 && packets.size() != 0)
        return;
    if (packets.size() > 0)
    {
        sendButton->setEnabled(true);
        sendButton->setAutoDefault(true);
        sendButton->setDefault(true);
    }
    else
    {
        sendButton->setEnabled(false);
        sendButton->setAutoDefault(false);
        sendButton->setDefault(false);
    }
    if (packets.size() > 1)
    {
        nextButton->setEnabled(true);
        prevButton->setEnabled(true);
    }
    else
    {
        nextButton->setEnabled(false);
        prevButton->setEnabled(false);
    }
    curPacket = cur;
    int i, intNum = 0;
    string dstStr = "";
    string msgStr = "";
    string pktStr = to_string(curPacket + 1) + "/" + to_string(packets.size());
    if (curPacket == -1)
    {
        previewTableItem[0][1]->setText(QString(""));
        previewTableItem[1][1]->setText(QString(""));
        previewTableItem[2][1]->setText(QString(""));
        previewTableItem[3][1]->setText(QString(""));
        pktLabel->setText(QString::fromStdString(pktStr));
        return;
    }
    switch (packets[curPacket]->protocol)
    {
    case IP_CODE:
    {
        for (i = 0; i < 3; i++)
            dstStr += to_string((int) packets[curPacket]->ip->DestinationAddress[i]) + ".";
        dstStr += to_string((int) packets[curPacket]->ip->DestinationAddress[i]);
        for (i = 0; i < packets[curPacket]->ip->Payload.size(); i++)
        {
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->ip->Payload[i] / 16));
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->ip->Payload[i] % 16));
        }
        while (msgStr[msgStr.size() - 1] == '0')
            msgStr.pop_back();
        intNum = (int) packets[curPacket]->ip->Interface;
        break;
    }
    case TCP_CODE:
    {
        dstStr += to_string((int) packets[curPacket]->tcp->DestinationPort);
        for (i = 0; i < packets[curPacket]->tcp->Payload.size(); i++)
        {
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->tcp->Payload[i] / 16));
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->tcp->Payload[i] % 16));
        }
        while (msgStr[msgStr.size() - 1] == '0')
            msgStr.pop_back();
        intNum = (int) packets[curPacket]->tcp->Interface;
        break;
    }
    case UDP_CODE:
    {
        dstStr += to_string((int) packets[curPacket]->udp->DestinationPort);
        for (i = 0; i < packets[curPacket]->udp->Payload.size(); i++)
        {
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->udp->Payload[i] / 16));
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->udp->Payload[i] % 16));
        }
        while (msgStr[msgStr.size() - 1] == '0')
            msgStr.pop_back();
        intNum = (int) packets[curPacket]->udp->Interface;
        break;
    }
    case ICMP_CODE:
    {
        dstStr.push_back('-');
        for (i = 0; i < packets[curPacket]->icmp->Payload.size(); i++)
        {
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->icmp->Payload[i] / 16));
            msgStr.push_back(CommonPacket::CharToHex(packets[curPacket]->icmp->Payload[i] % 16));
        }
        while (msgStr[msgStr.size() - 1] == '0')
            msgStr.pop_back();
        intNum = (int) packets[curPacket]->icmp->Interface;
        break;
    }
    default:
        return;
    }
    previewTableItem[0][1]->setText(QString::fromStdString(packets[curPacket]->protocolName));
    previewTableItem[1][1]->setText(QString::fromStdString(intNames[intNum]));
    previewTableItem[2][1]->setText(QString::fromStdString(dstStr));
    previewTableItem[3][1]->setText(QString::fromStdString(msgStr));
    pktLabel->setText(QString::fromStdString(pktStr));
    return;
}

void PacketManager::loadFile()
{
    int i;
    bool forall = false, many = false;
    unsigned char idx;
    QStringList filenames = QFileDialog::getOpenFileNames(this, "Open a File", "C:\\", "Packet files (*.pktmgr)");
    if (filenames.isEmpty() || filenames.size() > 32)
        return;
    if (filenames.size() > 1)
        many = true;
    for (i = 0; i < filenames.size(); i++)
    {
        int res;
        ifstream file;
        string pktStr;
        string protStr;
        file.open(filenames.at(i).toStdString());
        file >> pktStr;
        file.close();
        switch ((int) CommonPacket::HexToChar('0', pktStr[0]))
        {
        case IP_CODE:
        {
            protStr = to_string(IP_CODE) + "[0-9a-fA-F]{40,120}\!\![0-9a-fA-F]+";
            break;
        }
        case TCP_CODE:
        {
            protStr = to_string(TCP_CODE) + "[0-9a-fA-F]{40,120}\!\![0-9a-fA-F]+";
            break;
        }
        case UDP_CODE:
        {
            protStr = to_string(UDP_CODE) + "[0-9a-fA-F]{17,}";
            break;
        }
        case ICMP_CODE:
        {
            protStr = to_string(ICMP_CODE) + "[0-9a-fA-F]{17,}";
            break;
        }
        default:
            return;
        }
        regex pktReg(protStr);
        if (!regex_match(pktStr, pktReg))
            return;
        if (!forall)
        {
            intWindow = new InterfaceDialog(intNames, many, this);
            res = intWindow->exec();
            if (res == QDialog::Accepted)
            {
                idx = intWindow->Index;
                forall = intWindow->Forall;
            }
            delete intWindow;
        }
        switch ((int) CommonPacket::HexToChar('0', pktStr[0]))
        {
        case IP_CODE:
        {
            ipPacket *ipTmp = new ipPacket();
            uniPacket *uniTmp = new uniPacket();
            ipTmp->packetFile = pktStr;
            ipTmp->convertFromFile();
            ipTmp->Interface = idx;
            *uniTmp = *ipTmp;
            packets.push_back(uniTmp);
            delete ipTmp;
            break;
        }
        case TCP_CODE:
        {
            tcpPacket *tcpTmp = new tcpPacket();
            uniPacket *uniTmp = new uniPacket();
            tcpTmp->packetFile = pktStr;
            tcpTmp->convertFromFile();
            tcpTmp->Interface = idx;
            *uniTmp = *tcpTmp;
            packets.push_back(uniTmp);
            delete tcpTmp;
            break;
        }
        case UDP_CODE:
        {
            udpPacket *udpTmp = new udpPacket();
            uniPacket *uniTmp = new uniPacket();
            udpTmp->packetFile = pktStr;
            udpTmp->convertFromFile();
            udpTmp->Interface = idx;
            *uniTmp = *udpTmp;
            packets.push_back(uniTmp);
            delete udpTmp;
            break;
        }
        case ICMP_CODE:
        {
            icmpPacket *icmpTmp = new icmpPacket();
            uniPacket *uniTmp = new uniPacket();
            icmpTmp->packetFile = pktStr;
            icmpTmp->convertFromFile();
            icmpTmp->Interface = idx;
            *uniTmp = *icmpTmp;
            packets.push_back(uniTmp);
            delete icmpTmp;
            break;
        }
        default:
            return;
        }
    }
    displayCurrent(packets.size() - 1);
}

void PacketManager::IPpktmgr()
{
    int res;
    ipWindow = new ipDialog(intNames, this);
    res = ipWindow->exec();
    if (res == QDialog::Accepted)
    {
        int i;
        uniPacket *tmp = new uniPacket();
        *tmp = *ipWindow->packet;
        packets.push_back(tmp);
        displayCurrent(packets.size() - 1);
    }
    delete ipWindow;
}

void PacketManager::TCPpktmgr()
{
    int res;
    tcpWindow = new tcpDialog(intNames, this);
    res = tcpWindow->exec();
    if (res == QDialog::Accepted)
    {
        int i;
        uniPacket *tmp = new uniPacket();
        *tmp = *tcpWindow->packet;
        packets.push_back(tmp);
        displayCurrent(packets.size() - 1);
    }
    delete tcpWindow;
}

void PacketManager::UDPpktmgr()
{
    int res;
    udpWindow = new udpDialog(this);
    res = udpWindow->exec();
    if (res == QDialog::Accepted)
    {
        int i;
        uniPacket *tmp = new uniPacket();
        *tmp = *udpWindow->packet;
        packets.push_back(tmp);
        displayCurrent(packets.size() - 1);
    }
    delete udpWindow;
}

void PacketManager::ICMPpktmgr()
{
    int res;
    icmpWindow = new icmpDialog(this);
    res = icmpWindow->exec();
    if (res == QDialog::Accepted)
    {
        int i;
        uniPacket *tmp = new uniPacket();
        *tmp = *icmpWindow->packet;
        packets.push_back(tmp);
        displayCurrent(packets.size() - 1);
    }
    delete icmpWindow;
}

void PacketManager::displayMenu()
{
    if (curPacket != -1)
        contextMenu->popup(this->cursor().pos());
    return;
}

void PacketManager::editPacket()
{
    int res;
    switch (packets[curPacket]->protocol)
    {
    case IP_CODE:
    {
        ipWindow = new ipDialog(intNames, this);
        ipWindow->setPacket(packets[curPacket]->ip);
        res = ipWindow->exec();
        if (res == QDialog::Accepted)
            *packets[curPacket] = *ipWindow->packet;
        delete ipWindow;
        break;
    }
    case TCP_CODE:
    {
        tcpWindow = new tcpDialog(intNames, this);
        tcpWindow->setPacket(packets[curPacket]->tcp);
        res = tcpWindow->exec();
        if (res == QDialog::Accepted)
            *packets[curPacket] = *tcpWindow->packet;
        delete tcpWindow;
        break;
    }
    case UDP_CODE:
    {
        udpWindow = new udpDialog(this);
        udpWindow->setPacket(packets[curPacket]->udp);
        res = udpWindow->exec();
        if (res == QDialog::Accepted)
            *packets[curPacket] = *udpWindow->packet;
        delete udpWindow;
        break;
    }
    case ICMP_CODE:
    {

        break;
    }
    default:
        return;
    }
}

void PacketManager::deletePacket()
{
    uniPacket *tmp;
    tmp = packets[curPacket];
    packets.erase(packets.begin() + curPacket);
    delete tmp;
    if (packets.size() == 0)
        displayCurrent(-1);
    else
        displayCurrent(curPacket % packets.size());
}

void PacketManager::exportPacket()
{
    int i, dot = -1, err = 0;
    string extStr = "pktmgr";
    string fileStr;
    QString filter = "Packet files (*.pktmgr)";
    QString filename = QFileDialog::getSaveFileName(this, "Open a File", "C:\\untitled.pktmgr", filter, &filter);
    if (filename.isEmpty())
        return;
    fileStr = filename.toStdString();
    for (i = 0; i < filename.size(); i++)
        if (filename[i] == '.')
            dot = i + 1;
    if (dot != filename.size() - 6)
        err++;
    if (err != 0)
    {
        for (i = dot; i < filename.size(); i++)
            if (fileStr[i] != extStr[i - dot])
                err++;
    }
    if (err != 0)
        filename.push_back(".pktmgr");
    switch (packets[curPacket]->protocol)
    {
    case IP_CODE:
    {
        packets[curPacket]->ip->convertToFile();
        ofstream file;
        file.open(filename.toStdString());
        file << packets[curPacket]->ip->packetFile;
        file.close();
        break;
    }
    case TCP_CODE:
    {
        packets[curPacket]->tcp->convertToFile();
        ofstream file;
        file.open(filename.toStdString());
        file << packets[curPacket]->tcp->packetFile;
        file.close();
        break;
    }
    case UDP_CODE:
    {
        packets[curPacket]->udp->convertToFile();
        ofstream file;
        file.open(filename.toStdString());
        file << packets[curPacket]->udp->packetFile;
        file.close();
        break;
    }
    case ICMP_CODE:
    {
        packets[curPacket]->icmp->convertToFile();
        ofstream file;
        file.open(filename.toStdString());
        file << packets[curPacket]->icmp->packetFile;
        file.close();
        break;
    }
    default:
        return;
    }
}

void PacketManager::rawPacket()
{
    string rawStr;
    switch (packets[curPacket]->protocol)
    {
    case IP_CODE:
    {
        rawStr = packets[curPacket]->ip->convertToRaw();
        break;
    }
    case TCP_CODE:
    {
        rawStr = packets[curPacket]->tcp->convertToRaw();
        break;
    }
    case UDP_CODE:
    {
        rawStr = packets[curPacket]->udp->convertToRaw();
        break;
    }
    case ICMP_CODE:
    {

        break;
    }
    default:
        return;
    }
    const size_t len = rawStr.size() + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), rawStr.c_str(), len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

void PacketManager::sendPacket()
{
    switch (packets[curPacket]->protocol)
    {
    case IP_CODE:
    {
        packets[curPacket]->ip->convertToSend();
        PacketSender::send(IP_CODE, packets[curPacket]->ip->packetSend, packets[curPacket]->ip->size);
        break;
    }
    case TCP_CODE:
    {
        packets[curPacket]->tcp->convertToSend();
        PacketSender::send(IP_CODE, packets[curPacket]->ip->packetSend, packets[curPacket]->tcp->size);
        break;
    }
    case UDP_CODE:
    {
        packets[curPacket]->udp->convertToSend();
        PacketSender::send(IP_CODE, packets[curPacket]->ip->packetSend, packets[curPacket]->udp->size);
        break;
    }
    case ICMP_CODE:
    {
        packets[curPacket]->icmp->convertToSend();
        PacketSender::send(IP_CODE, packets[curPacket]->ip->packetSend, packets[curPacket]->icmp->size);
        break;
    }
    default:
        return;
    }
}

void PacketManager::nextPreview()
{
    displayCurrent((curPacket + 1) % packets.size());
}

void PacketManager::prevPreview()
{
    displayCurrent((curPacket - 1 + packets.size()) % packets.size());
}

void PacketManager::sendPackets()
{
    int i;
    for (i = 0; i < packets.size(); i++)
    {
        switch (packets[i]->protocol)
        {
        case IP_CODE:
        {
            packets[i]->ip->convertToSend();
            PacketSender::send(IP_CODE, packets[i]->ip->packetSend, packets[curPacket]->ip->size);
            break;
        }
        case TCP_CODE:
        {
            packets[i]->tcp->convertToSend();
            PacketSender::send(IP_CODE, packets[i]->tcp->packetSend, packets[curPacket]->tcp->size);
            break;
        }
        case UDP_CODE:
        {
            packets[i]->udp->convertToSend();
            PacketSender::send(IP_CODE, packets[i]->udp->packetSend, packets[curPacket]->udp->size);
            break;
        }
        case ICMP_CODE:
        {
            packets[i]->icmp->convertToSend();
            PacketSender::send(IP_CODE, packets[i]->icmp->packetSend, packets[curPacket]->icmp->size);
            break;
        }
        default:
            continue;
        }
    }
}

PacketManager::~PacketManager()
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++)
            delete previewTableItem[i][j];
    delete ui;
}
