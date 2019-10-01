#include "tcpdialog.h"
#include "ui_tcpdialog.h"

tcpDialog::tcpDialog(vector<string> interfaces, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcpDialog)
{
    int i;
    QRect rect;
    QRegExp srcExp;
    QRegExp dstExp;
    QRegExp seqExp;
    QRegExp ackExp;
    QRegExp offExp;
    QRegExp resExp;
    QRegExp flagExp;
    QRegExp winExp;
    QRegExp crcExp;
    QRegExp urgExp;
    QRegExpValidator *srcVal;
    QRegExpValidator *dstVal;
    QRegExpValidator *seqVal;
    QRegExpValidator *ackVal;
    QRegExpValidator *offVal;
    QRegExpValidator *resVal;
    QRegExpValidator *flagVal;
    QRegExpValidator *winVal;
    QRegExpValidator *crcVal;
    QRegExpValidator *urgVal;
    ui->setupUi(this);
    packet = new tcpPacket();
    mainLayout = new QGridLayout(this);
    smallLayout = new QGridLayout(this);
    smallWidget = new QWidget(this);
    srcLabel = new QLabel(this);
    dstLabel = new QLabel(this);
    seqLabel = new QLabel(this);
    ackLabel = new QLabel(this);
    offLabel = new QLabel(this);
    resLabel = new QLabel(this);
    flagLabel = new QLabel(this);
    winLabel = new QLabel(this);
    crcLabel = new QLabel(this);
    urgLabel = new QLabel(this);
    srcLine = new QLineEdit(this);
    dstLine = new QLineEdit(this);
    seqLine = new QLineEdit(this);
    ackLine = new QLineEdit(this);
    offLine = new QLineEdit(this);
    resLine = new QLineEdit(this);
    flagLine = new QLineEdit(this);
    winLine = new QLineEdit(this);
    crcLine = new QLineEdit(this);
    urgLine = new QLineEdit(this);
    offWidget = new QWidget(this);
    crcWidget = new QWidget(this);
    autWidget = new QWidget(this);
    offLayout = new QGridLayout(this);
    crcLayout = new QGridLayout(this);
    autLayout = new QGridLayout(this);
    offBox = new QCheckBox(this);
    crcBox = new QCheckBox(this);
    autBox = new QCheckBox(this);
    offAutoLabel = new QLabel(this);
    crcAutoLabel = new QLabel(this);
    autAutoLabel = new QLabel(this);
    optLabel = new QLabel(this);
    msgLabel = new QLabel(this);
    optText = new QTextEdit(this);
    msgText = new QTextEdit(this);
    ifLabel = new QLabel(this);
    ifBox = new QComboBox(this);
    saveButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    setWindowTitle("TCP");
    rect = QApplication::desktop()->screenGeometry();
    int x = rect.width() * 2 / 10;
    int y = rect.height() * 2 / 10;
    int w = rect.width() * 6 / 10;
    int h = rect.height() * 6 / 10;
    this->setGeometry(x, y, w, h);
    saveButton->setText(QString("Save"));
    cancelButton->setText(QString("Cancel"));
    saveButton->setAutoDefault(true);
    saveButton->setDefault(true);
    mainLayout->addWidget(saveButton, 1, 4);
    mainLayout->addWidget(cancelButton, 1, 3);
    mainLayout->addWidget(smallWidget, 0, 0, 1, 5);
    setLayout(mainLayout);
    for (i = 0; i < 10; i++)
        smallLayout->setColumnStretch(i, 1);
    for (i = 0; i < 13; i++)
        smallLayout->setRowStretch(i, 1);
    srcLabel->setText("Source Port:");
    dstLabel->setText("Destination Port:");
    seqLabel->setText("Sequence Number:");
    ackLabel->setText("Acknowledgment Number:");
    offLabel->setText("Data Offset:");
    resLabel->setText("Reserved:");
    flagLabel->setText("Flags:");
    winLabel->setText("Window:");
    crcLabel->setText("Checksum:");
    urgLabel->setText("Urgent Pointer:");
    offAutoLabel->setText("Automatically");
    crcAutoLabel->setText("Automatically");
    autAutoLabel->setText("All automatically");
    optLabel->setText("Options:");
    msgLabel->setText("Payload:");
    srcLine->setPlaceholderText("Dec");
    dstLine->setPlaceholderText("Dec");
    seqLine->setPlaceholderText("Dec");
    ackLine->setPlaceholderText("Dec");
    offLine->setPlaceholderText("Dec");
    resLine->setPlaceholderText("Bin");
    flagLine->setPlaceholderText("Bin");
    winLine->setPlaceholderText("Dec");
    crcLine->setPlaceholderText("Hex");
    urgLine->setPlaceholderText("Dec");
    optText->setPlaceholderText("Hex");
    msgText->setPlaceholderText("Hex");
    srcExp = QRegExp("([1-9][0-9]{,4})|0");
    dstExp = QRegExp("([1-9][0-9]{,4})|0");
    seqExp = QRegExp("([1-9][0-9]{,9})|0");
    ackExp = QRegExp("([1-9][0-9]{,9})|0");
    offExp = QRegExp("[1-9]?[0-9]");
    resExp = QRegExp("[01]{6}");
    flagExp = QRegExp("[01]{6}");
    winExp = QRegExp("([1-9][0-9]{,4})|0");
    crcExp = QRegExp("[0-9a-fA-F]{4}");
    urgExp = QRegExp("([1-9][0-9]{,4})|0");
    srcVal = new QRegExpValidator(srcExp, this);
    dstVal = new QRegExpValidator(dstExp, this);
    seqVal = new QRegExpValidator(seqExp, this);
    ackVal = new QRegExpValidator(ackExp, this);
    offVal = new QRegExpValidator(offExp, this);
    resVal = new QRegExpValidator(resExp, this);
    flagVal = new QRegExpValidator(flagExp, this);
    winVal = new QRegExpValidator(winExp, this);
    crcVal = new QRegExpValidator(crcExp, this);
    urgVal = new QRegExpValidator(urgExp, this);
    srcLine->setValidator(srcVal);
    dstLine->setValidator(dstVal);
    seqLine->setValidator(seqVal);
    ackLine->setValidator(ackVal);
    offLine->setValidator(offVal);
    resLine->setValidator(resVal);
    flagLine->setValidator(flagVal);
    winLine->setValidator(winVal);
    crcLine->setValidator(crcVal);
    urgLine->setValidator(urgVal);
    ifLabel->setText("Interface:");
    for (i = 0; i < interfaces.size(); i++)
        ifBox->addItem(QString::fromStdString(interfaces[i]));
    smallLayout->addWidget(srcLabel, 0, 0);
    smallLayout->addWidget(dstLabel, 1, 0);
    smallLayout->addWidget(seqLabel, 2, 0);
    smallLayout->addWidget(ackLabel, 3, 0);
    smallLayout->addWidget(offLabel, 4, 0);
    smallLayout->addWidget(resLabel, 5, 0);
    smallLayout->addWidget(flagLabel, 6, 0);
    smallLayout->addWidget(winLabel, 7, 0);
    smallLayout->addWidget(crcLabel, 8, 0);
    smallLayout->addWidget(urgLabel, 9, 0);
    smallLayout->addWidget(srcLine, 0, 1);
    smallLayout->addWidget(dstLine, 1, 1);
    smallLayout->addWidget(seqLine, 2, 1);
    smallLayout->addWidget(ackLine, 3, 1);
    smallLayout->addWidget(offLine, 4, 1);
    smallLayout->addWidget(resLine, 5, 1);
    smallLayout->addWidget(flagLine, 6, 1);
    smallLayout->addWidget(winLine, 7, 1);
    smallLayout->addWidget(crcLine, 8, 1);
    smallLayout->addWidget(urgLine, 9, 1);
    smallLayout->addWidget(offWidget, 4, 2);
    smallLayout->addWidget(crcWidget, 8, 2);
    smallLayout->addWidget(autWidget, 12, 2);
    offWidget->setLayout(offLayout);
    crcWidget->setLayout(crcLayout);
    autWidget->setLayout(autLayout);
    offLayout->addWidget(offAutoLabel, 0, 0);
    crcLayout->addWidget(crcAutoLabel, 0, 0);
    autLayout->addWidget(autAutoLabel, 0, 0);
    offLayout->addWidget(offBox, 0, 1);
    crcLayout->addWidget(crcBox, 0, 1);
    autLayout->addWidget(autBox, 0, 1);
    smallLayout->addWidget(optLabel, 0, 4);
    smallLayout->addWidget(msgLabel, 2, 4);
    smallLayout->addWidget(optText, 0, 5, 2, 5);
    smallLayout->addWidget(msgText, 2, 5, 9, 5);
    smallLayout->addWidget(ifLabel, 11, 4);
    smallLayout->addWidget(ifBox, 11, 5, 1, 5);
    smallWidget->setLayout((smallLayout));
    connect(offBox, SIGNAL(stateChanged(int)), this, SLOT(offStateChanged()));
    connect(crcBox, SIGNAL(stateChanged(int)), this, SLOT(crcStateChanged()));
    connect(autBox, SIGNAL(stateChanged(int)), this, SLOT(autStateChanged()));
    connect(optText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(msgText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(saveButton, SIGNAL(released()), this, SLOT(saveButtonPressed()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(cancelButtonPressed()));
}

void tcpDialog::offStateChanged()
{
    QPalette *palette;
    disconnect(offLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (offBox->isChecked())
    {
        offLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        offLine->setPalette(*palette);
        offLine->setText(QString("Auto"));
        if (crcBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        offLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::white);
        palette->setColor(QPalette::Text, Qt::black);
        offLine->setPalette(*palette);
        offLine->setText(QString(""));
        if (!crcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void tcpDialog::crcStateChanged()
{
    QPalette *palette;
    disconnect(crcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (crcBox->isChecked())
    {
        crcLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        crcLine->setPalette(*palette);
        crcLine->setText(QString("Auto"));
        if (offBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        crcLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::white);
        palette->setColor(QPalette::Text,Qt::black);
        crcLine->setPalette(*palette);
        crcLine->setText(QString(""));
        if (!offBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void tcpDialog::autStateChanged()
{
    if (autBox->isChecked())
    {
        offBox->setChecked(true);
        crcBox->setChecked(true);
    }
    else
    {
        offBox->setChecked(false);
        crcBox->setChecked(false);
    }
}

void tcpDialog::recolour()
{
    QLineEdit *line = qobject_cast<QLineEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    line->setPalette(*palette);
    disconnect(line, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    delete palette;
}

void tcpDialog::recolourText()
{
    QTextEdit *text = qobject_cast<QTextEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    text->setPalette(*palette);
    disconnect(text, SIGNAL(textChanged()), this, SLOT(recolour()));
    delete palette;
}

void tcpDialog::textValidator()
{
    QTextEdit *text = qobject_cast<QTextEdit*>(sender());
    QRegExp textRegExp = QRegExp("[0-9a-fA-F]*");
    if (!textRegExp.exactMatch(text->toPlainText()))
    {
        QTextCursor cursor = text->textCursor();
        text->setTextCursor(cursor);
        cursor.deletePreviousChar();
    }
}

void tcpDialog::setPacket(tcpPacket *pkt)
{
    int i, k;
    unsigned char val;
    string resStr = "";
    string flagStr = "";
    string crcStr = "";
    string optStr = "";
    string msgStr = "";
    val = pkt->Flags % 64;
    k = 32;
    for (i = 0; i < 6; i++)
    {
        flagStr += to_string(val / k);
        val %= k;
        k /= 2;
    }
    val = pkt->Reserved % 64;
    k = 32;
    for (i = 0; i < 6; i++)
    {
        resStr += to_string(val / k);
        val %= k;
        k /= 2;
    }
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[0] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[0] % 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[1] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[1] % 16));
    for (i = 0; i < pkt->Options.size(); i++)
    {
        optStr.push_back(CommonPacket::CharToHex(pkt->Options[i] / 16));
        optStr.push_back(CommonPacket::CharToHex(pkt->Options[i] % 16));
    }
    for (i = 0; i < pkt->Payload.size(); i++)
    {
        msgStr.push_back(CommonPacket::CharToHex(pkt->Payload[i] / 16));
        msgStr.push_back(CommonPacket::CharToHex(pkt->Payload[i] % 16));
    }
    while (optStr[optStr.size() - 1] == '0')
        optStr.pop_back();
    while (msgStr[msgStr.size() - 1] == '0')
        msgStr.pop_back();
    srcLine->setText(QString::fromStdString(to_string(pkt->SourcePort)));
    dstLine->setText(QString::fromStdString(to_string(pkt->DestinationPort)));
    seqLine->setText(QString::fromStdString(to_string(pkt->SequenceNumber)));
    ackLine->setText(QString::fromStdString(to_string(pkt->AcknowledgmentNumber)));
    offLine->setText(QString::fromStdString(to_string((int)pkt->DataOffset)));
    resLine->setText(QString::fromStdString(resStr));
    flagLine->setText(QString::fromStdString(flagStr));
    winLine->setText(QString::fromStdString(to_string(pkt->Window)));
    crcLine->setText(QString::fromStdString(crcStr));
    urgLine->setText(QString::fromStdString(to_string(pkt->UrgentPointer)));
    optText->setText(QString::fromStdString(optStr));
    msgText->setText(QString::fromStdString(msgStr));
}

void tcpDialog::saveButtonPressed()
{
    unsigned int i, totalLen;
    unsigned int err = 0;
    unsigned char cnt, resNum = 0, flagNum = 0;
    string token;
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::red);
    totalLen = 65535 - 40 - 40;
    if (optText->toPlainText().length() % 8 == 0)
        totalLen -= optText->toPlainText().length();
    else
        totalLen -= ((optText->toPlainText().length() / 8) + 1) * 8;
    if (srcLine->text().isEmpty() || stoi(srcLine->text().toStdString()) > 65535)
    {
        srcLine->setPalette(*palette);
        connect(srcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (dstLine->text().isEmpty() || stoi(dstLine->text().toStdString()) > 65535)
    {
        dstLine->setPalette(*palette);
        connect(dstLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (seqLine->text().isEmpty() || stol(seqLine->text().toStdString()) > 4294967295)
    {
        seqLine->setPalette(*palette);
        connect(seqLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (ackLine->text().isEmpty() || stol(ackLine->text().toStdString()) > 4294967295)
    {
        ackLine->setPalette(*palette);
        connect(ackLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (offLine->text().isEmpty() || stoi(offLine->text().toStdString()) > 15)
    {
        offLine->setPalette(*palette);
        connect(offLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (resLine->text().isEmpty() || resLine->text().length() != 6)
    {
        resLine->setPalette(*palette);
        connect(resLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (flagLine->text().isEmpty() || flagLine->text().length() != 6)
    {
        flagLine->setPalette(*palette);
        connect(flagLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (winLine->text().isEmpty() || stoi(winLine->text().toStdString()) > 65535)
    {
        winLine->setPalette(*palette);
        connect(winLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (crcLine->text().isEmpty() || crcLine->text().length() != 4)
    {
        crcLine->setPalette(*palette);
        connect(crcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (urgLine->text().isEmpty() || stoi(urgLine->text().toStdString()) > 65535)
    {
        urgLine->setPalette(*palette);
        connect(urgLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (optText->toPlainText().toStdString().length() > 80)
    {
        optText->setPalette(*palette);
        connect(optText, SIGNAL(textChanged()), this, SLOT(recolourText()));
        err++;
    }
    if (msgText->toPlainText().isEmpty() || msgText->toPlainText().toStdString().length() > totalLen)
    {
        msgText->setPalette(*palette);
        connect(msgText, SIGNAL(textChanged()), this, SLOT(recolourText()));
        err++;
    }
    if (err > 0)
        return;
    cnt = 1;
    for (i = 0; i < 6; i++)
    {
        resNum += cnt * resLine->text().toStdString()[5 - i];
        flagNum += cnt * flagLine->text().toStdString()[5 - i];
        cnt *= 2;
    }
    packet->SourcePort = stoi(srcLine->text().toStdString());
    packet->DestinationPort = stoi(dstLine->text().toStdString());
    packet->SequenceNumber = stol(seqLine->text().toStdString());
    packet->AcknowledgmentNumber = stol(ackLine->text().toStdString());
    packet->Reserved = resNum;
    packet->Flags = flagNum;
    packet->Window = stoi(winLine->text().toStdString());
    packet->Checksum[0] = CommonPacket::HexToChar(crcLine->text().toStdString()[0], crcLine->text().toStdString()[1]);
    packet->Checksum[1] = CommonPacket::HexToChar(crcLine->text().toStdString()[2], crcLine->text().toStdString()[3]);
    packet->Window = stoi(winLine->text().toStdString());
    string optStr = optText->toPlainText().toStdString();
    for (i = 0; i < optStr.length(); i += 2)
    {
        if (i + 1 == optStr.length())
            packet->Options.push_back(CommonPacket::HexToChar(optStr[i], '0'));
        else
            packet->Options.push_back(CommonPacket::HexToChar(optStr[i], optStr[i + 1]));
    }
    if (packet->Options.size() / 4 != 0)
        for (i = 0; i < 4 - (packet->Options.size() % 4); i++)
            packet->Options.push_back(0);
    string msgStr = msgText->toPlainText().toStdString();
    for (i = 0; i < msgStr.length(); i += 2)
    {
        if (i + 1 == msgStr.length())
            packet->Payload.push_back(CommonPacket::HexToChar(msgStr[i], '0'));
        else
            packet->Payload.push_back(CommonPacket::HexToChar(msgStr[i], msgStr[i + 1]));
    }
    accept();
}

void tcpDialog::cancelButtonPressed()
{
    reject();
}

tcpDialog::~tcpDialog()
{
    delete ui;
    delete packet;
}
