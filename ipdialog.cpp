#include "ipdialog.h"
#include "ui_ipdialog.h"

ipDialog::ipDialog(vector<string> interfaces, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ipDialog)
{
    int i;
    QRect rect;
    QRegExp verExp;
    QRegExp ihlExp;
    QRegExp tosExp;
    QRegExp lenExp;
    QRegExp idExp;
    QRegExp flagExp;
    QRegExp offExp;
    QRegExp ttlExp;
    QRegExp protExp;
    QRegExp crcExp;
    QRegExp srcExp;
    QRegExp dstExp;
    QRegExpValidator *verVal;
    QRegExpValidator *ihlVal;
    QRegExpValidator *tosVal;
    QRegExpValidator *lenVal;
    QRegExpValidator *idVal;
    QRegExpValidator *flagVal;
    QRegExpValidator *offVal;
    QRegExpValidator *ttlVal;
    QRegExpValidator *protVal;
    QRegExpValidator *crcVal;
    QRegExpValidator *srcVal;
    QRegExpValidator *dstVal;
    ui->setupUi(this);
    packet = new ipPacket();
    mainLayout = new QGridLayout(this);
    smallLayout = new QGridLayout(this);
    smallWidget = new QWidget(this);
    verLabel = new QLabel(this);
    ihlLabel = new QLabel(this);
    tosLabel = new QLabel(this);
    lenLabel = new QLabel(this);
    idLabel = new QLabel(this);
    flagLabel = new QLabel(this);
    offLabel = new QLabel(this);
    ttlLabel = new QLabel(this);
    protLabel = new QLabel(this);
    crcLabel = new QLabel(this);
    srcLabel = new QLabel(this);
    dstLabel = new QLabel(this);
    verLine = new QLineEdit(this);
    ihlLine = new QLineEdit(this);
    tosLine = new QLineEdit(this);
    lenLine = new QLineEdit(this);
    idLine = new QLineEdit(this);
    flagLine = new QLineEdit(this);
    offLine = new QLineEdit(this);
    ttlLine = new QLineEdit(this);
    protLine = new QLineEdit(this);
    crcLine = new QLineEdit(this);
    srcLine = new QLineEdit(this);
    dstLine = new QLineEdit(this);
    ihlWidget = new QWidget(this);
    lenWidget = new QWidget(this);
    crcWidget = new QWidget(this);
    srcWidget = new QWidget(this);
    autWidget = new QWidget(this);
    ihlLayout = new QGridLayout(this);
    lenLayout = new QGridLayout(this);
    crcLayout = new QGridLayout(this);
    srcLayout = new QGridLayout(this);
    autLayout = new QGridLayout(this);
    ihlBox = new QCheckBox(this);
    lenBox = new QCheckBox(this);
    crcBox = new QCheckBox(this);
    srcBox = new QCheckBox(this);
    autBox = new QCheckBox(this);
    ihlAutoLabel = new QLabel(this);
    lenAutoLabel = new QLabel(this);
    crcAutoLabel = new QLabel(this);
    srcAutoLabel = new QLabel(this);
    autAutoLabel = new QLabel(this);
    optLabel = new QLabel(this);
    msgLabel = new QLabel(this);
    optText = new QTextEdit(this);
    msgText = new QTextEdit(this);
    ifLabel = new QLabel(this);
    ifBox = new QComboBox(this);
    saveButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    setWindowTitle("IP");
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
    verLabel->setText("Version:");
    ihlLabel->setText("IHL:");
    tosLabel->setText("Type of Service:");
    lenLabel->setText("Total Length:");
    idLabel->setText("Identification:");
    flagLabel->setText("Flags:");
    offLabel->setText("Fragment Offset:");
    ttlLabel->setText("Time to Live:");
    protLabel->setText("Protocol:");
    crcLabel->setText("Header Checksum:");
    srcLabel->setText("Source Address:");
    dstLabel->setText("Destination Address:");
    ihlAutoLabel->setText("Automatically");
    lenAutoLabel->setText("Automatically");
    crcAutoLabel->setText("Automatically");
    srcAutoLabel->setText("Automatically");
    autAutoLabel->setText("All automatically");
    optLabel->setText("Options:");
    msgLabel->setText("Payload:");
    verLine->setPlaceholderText("Dec");
    ihlLine->setPlaceholderText("Dec");
    tosLine->setPlaceholderText("Hex");
    lenLine->setPlaceholderText("Dec");
    idLine->setPlaceholderText("Dec");
    flagLine->setPlaceholderText("Bin");
    offLine->setPlaceholderText("Dec");
    ttlLine->setPlaceholderText("Dec");
    protLine->setPlaceholderText("Dec");
    crcLine->setPlaceholderText("Hex");
    srcLine->setPlaceholderText("Dec");
    dstLine->setPlaceholderText("Dec");
    optText->setPlaceholderText("Hex");
    msgText->setPlaceholderText("Hex");
    verExp = QRegExp("[1-9]?[0-9]");
    ihlExp = QRegExp("[1-9]?[0-9]");
    tosExp = QRegExp("[0-9a-fA-F]{2}");
    lenExp = QRegExp("([1-9][0-9]{,4})|0");
    idExp = QRegExp("([1-9][0-9]{,4})|0");
    flagExp = QRegExp("[01]{3}");
    offExp = QRegExp("([1-9][0-9]{,3})|0");
    ttlExp = QRegExp("([1-9][0-9]{,2})|0");
    protExp = QRegExp("([1-9][0-9]{,2})|0");
    crcExp = QRegExp("[0-9a-fA-F]{4}");
    srcExp = QRegExp("((([1-9][0-9]{,2})|0)\.){3}(([1-9][0-9]{,2})|0)");
    dstExp = QRegExp("((([1-9][0-9]{,2})|0)\.){3}(([1-9][0-9]{,2})|0)");
    verVal = new QRegExpValidator(verExp, this);
    ihlVal = new QRegExpValidator(ihlExp, this);
    tosVal = new QRegExpValidator(tosExp, this);
    lenVal = new QRegExpValidator(lenExp, this);
    idVal = new QRegExpValidator(idExp, this);
    flagVal = new QRegExpValidator(flagExp, this);
    offVal = new QRegExpValidator(offExp, this);
    ttlVal = new QRegExpValidator(ttlExp, this);
    protVal = new QRegExpValidator(protExp, this);
    crcVal = new QRegExpValidator(crcExp, this);
    srcVal = new QRegExpValidator(srcExp, this);
    dstVal = new QRegExpValidator(dstExp, this);
    verLine->setValidator(verVal);
    ihlLine->setValidator(ihlVal);
    tosLine->setValidator(tosVal);
    lenLine->setValidator(lenVal);
    idLine->setValidator(idVal);
    flagLine->setValidator(flagVal);
    offLine->setValidator(offVal);
    ttlLine->setValidator(ttlVal);
    protLine->setValidator(protVal);
    crcLine->setValidator(crcVal);
    srcLine->setValidator(srcVal);
    dstLine->setValidator(dstVal);
    ifLabel->setText("Interface:");
    for (i = 0; i < interfaces.size(); i++)
        ifBox->addItem(QString::fromStdString(interfaces[i]));
    smallLayout->addWidget(verLabel, 0, 0);
    smallLayout->addWidget(ihlLabel, 1, 0);
    smallLayout->addWidget(tosLabel, 2, 0);
    smallLayout->addWidget(lenLabel, 3, 0);
    smallLayout->addWidget(idLabel, 4, 0);
    smallLayout->addWidget(flagLabel, 5, 0);
    smallLayout->addWidget(offLabel, 6, 0);
    smallLayout->addWidget(ttlLabel, 7, 0);
    smallLayout->addWidget(protLabel, 8, 0);
    smallLayout->addWidget(crcLabel, 9, 0);
    smallLayout->addWidget(srcLabel, 10, 0);
    smallLayout->addWidget(dstLabel, 11, 0);
    smallLayout->addWidget(verLine, 0, 1);
    smallLayout->addWidget(ihlLine, 1, 1);
    smallLayout->addWidget(tosLine, 2, 1);
    smallLayout->addWidget(lenLine, 3, 1);
    smallLayout->addWidget(idLine, 4, 1);
    smallLayout->addWidget(flagLine, 5, 1);
    smallLayout->addWidget(offLine, 6, 1);
    smallLayout->addWidget(ttlLine, 7, 1);
    smallLayout->addWidget(protLine, 8, 1);
    smallLayout->addWidget(crcLine, 9, 1);
    smallLayout->addWidget(srcLine, 10, 1);
    smallLayout->addWidget(dstLine, 11, 1);
    smallLayout->addWidget(ihlWidget, 1, 2);
    smallLayout->addWidget(lenWidget, 3, 2);
    smallLayout->addWidget(crcWidget, 9, 2);
    smallLayout->addWidget(srcWidget, 10, 2);
    smallLayout->addWidget(autWidget, 12, 2);
    ihlWidget->setLayout(ihlLayout);
    lenWidget->setLayout(lenLayout);
    crcWidget->setLayout(crcLayout);
    srcWidget->setLayout(srcLayout);
    autWidget->setLayout(autLayout);
    ihlLayout->addWidget(ihlAutoLabel, 0, 0);
    lenLayout->addWidget(lenAutoLabel, 0, 0);
    crcLayout->addWidget(crcAutoLabel, 0, 0);
    srcLayout->addWidget(srcAutoLabel, 0, 0);
    autLayout->addWidget(autAutoLabel, 0, 0);
    ihlLayout->addWidget(ihlBox, 0, 1);
    lenLayout->addWidget(lenBox, 0, 1);
    crcLayout->addWidget(crcBox, 0, 1);
    srcLayout->addWidget(srcBox, 0, 1);
    autLayout->addWidget(autBox, 0, 1);
    smallLayout->addWidget(optLabel, 0, 4);
    smallLayout->addWidget(msgLabel, 2, 4);
    smallLayout->addWidget(optText, 0, 5, 2, 5);
    smallLayout->addWidget(msgText, 2, 5, 9, 5);
    smallLayout->addWidget(ifLabel, 11, 4);
    smallLayout->addWidget(ifBox, 11, 5, 1, 5);
    smallWidget->setLayout((smallLayout));
    connect(ihlBox, SIGNAL(stateChanged(int)), this, SLOT(ihlStateChanged()));
    connect(lenBox, SIGNAL(stateChanged(int)), this, SLOT(lenStateChanged()));
    connect(crcBox, SIGNAL(stateChanged(int)), this, SLOT(crcStateChanged()));
    connect(srcBox, SIGNAL(stateChanged(int)), this, SLOT(srcStateChanged()));
    connect(autBox, SIGNAL(stateChanged(int)), this, SLOT(autStateChanged()));
    connect(optText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(msgText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(saveButton, SIGNAL(released()), this, SLOT(saveButtonPressed()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(cancelButtonPressed()));
}

void ipDialog::ihlStateChanged()
{
    QPalette *palette;
    disconnect(ihlLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (ihlBox->isChecked())
    {
        ihlLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        ihlLine->setPalette(*palette);
        ihlLine->setText(QString("Auto"));
        if (lenBox->isChecked() && crcBox->isChecked() && srcBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        ihlLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::white);
        palette->setColor(QPalette::Text, Qt::black);
        ihlLine->setPalette(*palette);
        ihlLine->setText(QString(""));
        if (!lenBox->isChecked() && !crcBox->isChecked() && !srcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void ipDialog::lenStateChanged()
{
    QPalette *palette;
    disconnect(lenLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (lenBox->isChecked())
    {
        lenLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        lenLine->setPalette(*palette);
        lenLine->setText(QString("Auto"));
        if (ihlBox->isChecked() && crcBox->isChecked() && srcBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        lenLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::white);
        palette->setColor(QPalette::Text, Qt::black);
        lenLine->setPalette(*palette);
        lenLine->setText(QString(""));
        if (!ihlBox->isChecked() && !crcBox->isChecked() && !srcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void ipDialog::crcStateChanged()
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
        if (ihlBox->isChecked() && lenBox->isChecked() && srcBox->isChecked())
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
        if (!ihlBox->isChecked() && !lenBox->isChecked() && !srcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void ipDialog::srcStateChanged()
{
    QPalette *palette;
    disconnect(srcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (srcBox->isChecked())
    {
        srcLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        srcLine->setPalette(*palette);
        srcLine->setText(QString("Auto"));
        if (ihlBox->isChecked() && lenBox->isChecked() && crcBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        srcLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::white);
        palette->setColor(QPalette::Text,Qt::black);
        srcLine->setPalette(*palette);
        srcLine->setText(QString(""));
        if (!ihlBox->isChecked() && !lenBox->isChecked() && !crcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void ipDialog::autStateChanged()
{
    if (autBox->isChecked())
    {
        ihlBox->setChecked(true);
        lenBox->setChecked(true);
        crcBox->setChecked(true);
        srcBox->setChecked(true);
    }
    else
    {
        ihlBox->setChecked(false);
        lenBox->setChecked(false);
        crcBox->setChecked(false);
        srcBox->setChecked(false);
    }
}

void ipDialog::recolour()
{
    QLineEdit *line = qobject_cast<QLineEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    line->setPalette(*palette);
    disconnect(line, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    delete palette;
}

void ipDialog::recolourText()
{
    QTextEdit *text = qobject_cast<QTextEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    text->setPalette(*palette);
    disconnect(text, SIGNAL(textChanged()), this, SLOT(recolour()));
    delete palette;
}

void ipDialog::textValidator()
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

void ipDialog::setPacket(ipPacket *pkt)
{
    int i;
    unsigned char flag;
    string tosStr = "";
    string flagStr = "";
    string crcStr = "";
    string srcStr = "";
    string dstStr = "";
    string optStr = "";
    string msgStr = "";
    tosStr.push_back(CommonPacket::CharToHex(pkt->TypeOfService / 16));
    tosStr.push_back(CommonPacket::CharToHex(pkt->TypeOfService % 16));
    flag = pkt->Flags % 8;
    flagStr += to_string(flag / 4);
    flag %= 4;
    flagStr += to_string(flag / 2);
    flag %= 2;
    flagStr += to_string(flag);
    crcStr.push_back(CommonPacket::CharToHex(pkt->HeaderChecksum[0] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->HeaderChecksum[0] % 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->HeaderChecksum[1] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->HeaderChecksum[1] % 16));
    srcStr += to_string(pkt->SourceAddress[0]);
    srcStr.push_back('.');
    srcStr += to_string(pkt->SourceAddress[1]);
    srcStr.push_back('.');
    srcStr += to_string(pkt->SourceAddress[2]);
    srcStr.push_back('.');
    srcStr += to_string(pkt->SourceAddress[3]);
    dstStr += to_string(pkt->DestinationAddress[0]);
    dstStr.push_back('.');
    dstStr += to_string(pkt->DestinationAddress[1]);
    dstStr.push_back('.');
    dstStr += to_string(pkt->DestinationAddress[2]);
    dstStr.push_back('.');
    dstStr += to_string(pkt->DestinationAddress[3]);
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
    verLine->setText(QString::fromStdString(to_string((int)pkt->Version)));
    if (!pkt->boxes[0])
        ihlLine->setText(QString::fromStdString(to_string((int)pkt->IHL)));
    else
        ihlBox->setChecked(true);
    tosLine->setText(QString::fromStdString(tosStr));
    if (!pkt->boxes[1])
        lenLine->setText(QString::fromStdString(to_string((int)pkt->TotalLength)));
    else
        lenBox->setChecked(true);
    idLine->setText(QString::fromStdString(to_string((int)pkt->Identification)));
    flagLine->setText(QString::fromStdString(flagStr));
    offLine->setText(QString::fromStdString(to_string((int)pkt->FragmentOffset)));
    ttlLine->setText(QString::fromStdString(to_string((int)pkt->TimeToLive)));
    protLine->setText(QString::fromStdString(to_string((int)pkt->Protocol)));
    if (!pkt->boxes[2])
        crcLine->setText(QString::fromStdString(crcStr));
    else
        crcBox->setChecked(true);
    if (!pkt->boxes[3])
        srcLine->setText(QString::fromStdString(srcStr));
    else
        srcBox->setChecked(true);
    dstLine->setText(QString::fromStdString(dstStr));
    optText->setText(QString::fromStdString(optStr));
    msgText->setText(QString::fromStdString(msgStr));
    ifBox->setCurrentIndex((int) pkt->Interface);
}

void ipDialog::saveButtonPressed()
{
    unsigned int i, srcCnt, dstCnt, totalLen;
    unsigned int err = 0;
    unsigned int srcAddr[4] = { 0 };
    unsigned int dstAddr[4] = { 0 };
    string token;
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::red);
    string srcText;
    if (!srcBox->isChecked())
        srcText = srcLine->text().toStdString();
    else
    {
        istringstream tmp(ifBox->currentText().toStdString());
        while (getline(tmp, token, ' '))
            srcText = token;
    }
    istringstream srcIstr(srcText);
    i = 0;
    srcCnt = 0;
    while (getline(srcIstr, token, '.'))
    {
        srcAddr[i] = stoi(token);
        if (srcAddr[i] > 255)
            srcCnt++;
        i++;
    }
    if (i < 4)
        srcCnt++;
    string dstText = dstLine->text().toStdString();
    istringstream dstIstr(dstText);
    i = 0;
    dstCnt = 0;
    while (getline(dstIstr, token, '.'))
    {
        dstAddr[i] = stoi(token);
        if (dstAddr[i] > 255)
            dstCnt++;
        i++;
    }
    if (i < 4)
        dstCnt++;
    totalLen = 65535 - 40;
    if (optText->toPlainText().length() % 8 == 0)
        totalLen -= optText->toPlainText().length();
    else
        totalLen -= ((optText->toPlainText().length() / 8) + 1) * 8;
    if (verLine->text().isEmpty() || stoi(verLine->text().toStdString()) > 15)
    {
        verLine->setPalette(*palette);
        connect(verLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (!ihlBox->isChecked())
        if (ihlLine->text().isEmpty() || stoi(ihlLine->text().toStdString()) > 15)
        {
            ihlLine->setPalette(*palette);
            connect(ihlLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
            err++;
        }
    if (tosLine->text().isEmpty() || tosLine->text().length() != 2)
    {
        tosLine->setPalette(*palette);
        connect(tosLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (!lenBox->isChecked())
        if (lenLine->text().isEmpty() || stoi(verLine->text().toStdString()) > 65535)
        {
            lenLine->setPalette(*palette);
            connect(lenLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
            err++;
        }
    if (idLine->text().isEmpty() || stoi(idLine->text().toStdString()) > 65535)
    {
        idLine->setPalette(*palette);
        connect(idLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (flagLine->text().isEmpty() || flagLine->text().length() != 3)
    {
        flagLine->setPalette(*palette);
        connect(flagLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (offLine->text().isEmpty() || stoi(offLine->text().toStdString()) > 8191)
    {
        offLine->setPalette(*palette);
        connect(offLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (ttlLine->text().isEmpty() || stoi(ttlLine->text().toStdString()) > 255)
    {
        ttlLine->setPalette(*palette);
        connect(ttlLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (protLine->text().isEmpty() || stoi(protLine->text().toStdString()) > 255)
    {
        protLine->setPalette(*palette);
        connect(protLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (!crcBox->isChecked())
        if (crcLine->text().isEmpty() || crcLine->text().length() != 4)
        {
            crcLine->setPalette(*palette);
            connect(crcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
            err++;
        }
    if (!srcBox->isChecked())
        if (srcLine->text().isEmpty() || srcCnt > 0)
        {
            srcLine->setPalette(*palette);
            connect(srcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
            err++;
        }
    if (dstLine->text().isEmpty() || dstCnt > 0)
    {
        dstLine->setPalette(*palette);
        connect(dstLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
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
    packet->Version = stoi(verLine->text().toStdString());
    if (!ihlBox->isChecked())
        packet->IHL = stoi(ihlLine->text().toStdString());
    packet->TypeOfService = CommonPacket::HexToChar(tosLine->text().toStdString()[0], tosLine->text().toStdString()[1]);
    if (!lenBox->isChecked())
        packet->TotalLength = stoi(lenLine->text().toStdString());
    packet->Identification = stoi(idLine->text().toStdString());
    packet->Flags = 4 * flagLine->text().toStdString()[0] + 2 * flagLine->text().toStdString()[1] + flagLine->text().toStdString()[2];
    packet->FragmentOffset = stoi(offLine->text().toStdString());
    packet->TimeToLive = stoi(ttlLine->text().toStdString());
    packet->Protocol = stoi(protLine->text().toStdString());
    if (!crcBox->isChecked())
    {
        packet->HeaderChecksum[0] = CommonPacket::HexToChar(crcLine->text().toStdString()[0], crcLine->text().toStdString()[1]);
        packet->HeaderChecksum[1] = CommonPacket::HexToChar(crcLine->text().toStdString()[2], crcLine->text().toStdString()[3]);
    }
    else
    {
        packet->HeaderChecksum[0] = 0;
        packet->HeaderChecksum[1] = 0;
    }
    for (i = 0; i < 4; i++)
    {
        packet->SourceAddress[i] = (unsigned char) srcAddr[i];
        packet->DestinationAddress[i] = (unsigned char) dstAddr[i];
    }
    string optStr = optText->toPlainText().toStdString();
    for (i = 0; i < optStr.length(); i += 2)
    {
        if (i + 1 == optStr.length())
            packet->Options.push_back(CommonPacket::HexToChar(optStr[i], '0'));
        else
            packet->Options.push_back(CommonPacket::HexToChar(optStr[i], optStr[i + 1]));
    }
    int left = packet->Options.size() % 4;
    if (left != 0)
        for (i = 0; i < 4 - left; i++)
            packet->Options.push_back(0);
    string msgStr = msgText->toPlainText().toStdString();
    for (i = 0; i < msgStr.length(); i += 2)
    {
        if (i + 1 == msgStr.length())
            packet->Payload.push_back(CommonPacket::HexToChar(msgStr[i], '0'));
        else
            packet->Payload.push_back(CommonPacket::HexToChar(msgStr[i], msgStr[i + 1]));
    }
    if (ihlBox->isChecked())
        packet->IHL = 5 + packet->Options.size() / 4;
    if (lenBox->isChecked())
        packet->TotalLength = packet->IHL * 4 + packet->Payload.size();
    if (crcBox->isChecked())
    {
        unsigned int sum;
        packet->convertToSend();
        for (i = 0; i < 40; i += 2)
        {
            sum += (int) packet->packetSend[i];
            sum += (int) packet->packetSend[i + 1];
        }
        while (sum / 65536 != 0)
        {
            int val = sum / 65536;
            sum %= 65536;
            sum += val;
        }
        sum = 65535 - sum;
        packet->HeaderChecksum[0] = sum / 256;
        packet->HeaderChecksum[1] = sum % 256;
    }
    packet->Interface = ifBox->currentIndex();
    packet->boxes[0] = ihlBox->isChecked();
    packet->boxes[1] = lenBox->isChecked();
    packet->boxes[2] = crcBox->isChecked();
    packet->boxes[3] = srcBox->isChecked();
    accept();
}

void ipDialog::cancelButtonPressed()
{
    reject();
}

ipDialog::~ipDialog()
{
    delete ui;
    delete packet;
}
