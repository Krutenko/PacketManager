#include "udpdialog.h"
#include "ui_udpdialog.h"

udpDialog::udpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::udpDialog)
{
    int i;
    QRect rect;
    QRegExp srcExp;
    QRegExp dstExp;
    QRegExp lenExp;
    QRegExp crcExp;
    QRegExpValidator *srcVal;
    QRegExpValidator *dstVal;
    QRegExpValidator *lenVal;
    QRegExpValidator *crcVal;
    ui->setupUi(this);
    packet = new udpPacket();
    mainLayout = new QGridLayout(this);
    smallLayout = new QGridLayout(this);
    smallWidget = new QWidget(this);
    srcLabel = new QLabel(this);
    dstLabel = new QLabel(this);
    lenLabel = new QLabel(this);
    crcLabel = new QLabel(this);
    srcLine = new QLineEdit(this);
    dstLine = new QLineEdit(this);
    lenLine = new QLineEdit(this);
    crcLine = new QLineEdit(this);
    lenWidget = new QWidget(this);
    crcWidget = new QWidget(this);
    autWidget = new QWidget(this);
    lenLayout = new QGridLayout(this);
    crcLayout = new QGridLayout(this);
    autLayout = new QGridLayout(this);
    lenBox = new QCheckBox(this);
    crcBox = new QCheckBox(this);
    autBox = new QCheckBox(this);
    lenAutoLabel = new QLabel(this);
    crcAutoLabel = new QLabel(this);
    autAutoLabel = new QLabel(this);
    msgLabel = new QLabel(this);
    msgText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    setWindowTitle("UDP");
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
    lenLabel->setText("Length:");
    crcLabel->setText("Checksum:");
    lenAutoLabel->setText("Automatically");
    crcAutoLabel->setText("Automatically");
    autAutoLabel->setText("All automatically");
    msgLabel->setText("Payload:");
    srcLine->setPlaceholderText("Dec");
    dstLine->setPlaceholderText("Dec");
    lenLine->setPlaceholderText("Dec");
    crcLine->setPlaceholderText("Hex");
    msgText->setPlaceholderText("Hex");
    srcExp = QRegExp("([1-9][0-9]{,4})|0");
    dstExp = QRegExp("([1-9][0-9]{,4})|0");
    lenExp = QRegExp("([1-9][0-9]{,4})|0");
    crcExp = QRegExp("[0-9a-fA-F]{4}");
    srcVal = new QRegExpValidator(srcExp, this);
    dstVal = new QRegExpValidator(dstExp, this);
    lenVal = new QRegExpValidator(lenExp, this);
    crcVal = new QRegExpValidator(crcExp, this);
    srcLine->setValidator(srcVal);
    dstLine->setValidator(dstVal);
    lenLine->setValidator(lenVal);
    crcLine->setValidator(crcVal);
    smallLayout->addWidget(srcLabel, 0, 0);
    smallLayout->addWidget(dstLabel, 1, 0);
    smallLayout->addWidget(lenLabel, 2, 0);
    smallLayout->addWidget(crcLabel, 3, 0);
    smallLayout->addWidget(srcLine, 0, 1);
    smallLayout->addWidget(dstLine, 1, 1);
    smallLayout->addWidget(lenLine, 2, 1);
    smallLayout->addWidget(crcLine, 3, 1);
    smallLayout->addWidget(lenWidget, 2, 2);
    smallLayout->addWidget(crcWidget, 3, 2);
    smallLayout->addWidget(autWidget, 12, 2);
    lenWidget->setLayout(lenLayout);
    crcWidget->setLayout(crcLayout);
    autWidget->setLayout(autLayout);
    lenLayout->addWidget(lenAutoLabel, 0, 0);
    crcLayout->addWidget(crcAutoLabel, 0, 0);
    autLayout->addWidget(autAutoLabel, 0, 0);
    lenLayout->addWidget(lenBox, 0, 1);
    crcLayout->addWidget(crcBox, 0, 1);
    autLayout->addWidget(autBox, 0, 1);
    smallLayout->addWidget(msgLabel, 0, 4);
    smallLayout->addWidget(msgText, 0, 5, 10, 5);
    smallWidget->setLayout((smallLayout));
    connect(lenBox, SIGNAL(stateChanged(int)), this, SLOT(lenStateChanged()));
    connect(crcBox, SIGNAL(stateChanged(int)), this, SLOT(crcStateChanged()));
    connect(autBox, SIGNAL(stateChanged(int)), this, SLOT(autStateChanged()));
    connect(msgText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(saveButton, SIGNAL(released()), this, SLOT(saveButtonPressed()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(cancelButtonPressed()));
}

void udpDialog::lenStateChanged()
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
        if (crcBox->isChecked())
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
        if (!crcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void udpDialog::crcStateChanged()
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
        if (lenBox->isChecked())
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
        if (!lenBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void udpDialog::autStateChanged()
{
    if (autBox->isChecked())
    {
        lenBox->setChecked(true);
        crcBox->setChecked(true);
    }
    else
    {
        lenBox->setChecked(false);
        crcBox->setChecked(false);
    }
}

void udpDialog::recolour()
{
    QLineEdit *line = qobject_cast<QLineEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    line->setPalette(*palette);
    disconnect(line, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    delete palette;
}

void udpDialog::recolourText()
{
    QTextEdit *text = qobject_cast<QTextEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    text->setPalette(*palette);
    disconnect(text, SIGNAL(textChanged()), this, SLOT(recolour()));
    delete palette;
}

void udpDialog::textValidator()
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

void udpDialog::setPacket(udpPacket *pkt)
{
    int i;
    string crcStr = "";
    string msgStr = "";
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[0] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[0] % 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[1] / 16));
    crcStr.push_back(CommonPacket::CharToHex(pkt->Checksum[1] % 16));
    for (i = 0; i < pkt->Payload.size(); i++)
    {
        msgStr.push_back(CommonPacket::CharToHex(pkt->Payload[i] / 16));
        msgStr.push_back(CommonPacket::CharToHex(pkt->Payload[i] % 16));
    }
    while (msgStr[msgStr.size() - 1] == '0')
        msgStr.pop_back();
    srcLine->setText(QString::fromStdString(to_string(pkt->SourcePort)));
    dstLine->setText(QString::fromStdString(to_string(pkt->DestinationPort)));
    lenLine->setText(QString::fromStdString(to_string(pkt->Length)));
    crcLine->setText(QString::fromStdString(crcStr));
    msgText->setText(QString::fromStdString(msgStr));
}

void udpDialog::saveButtonPressed()
{
    unsigned int i, totalLen;
    unsigned int err = 0;
    unsigned char cnt, resNum = 0, flagNum = 0;
    string token;
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::red);
    totalLen = 65535 - 40 - 16;
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
    if (lenLine->text().isEmpty() || stoi(lenLine->text().toStdString()) > 65535)
    {
        lenLine->setPalette(*palette);
        connect(lenLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (crcLine->text().isEmpty() || crcLine->text().length() != 4)
    {
        crcLine->setPalette(*palette);
        connect(crcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
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
    packet->SourcePort = stoi(srcLine->text().toStdString());
    packet->DestinationPort = stoi(dstLine->text().toStdString());
    packet->Length = stoi(lenLine->text().toStdString());
    packet->Checksum[0] = CommonPacket::HexToChar(crcLine->text().toStdString()[0], crcLine->text().toStdString()[1]);
    packet->Checksum[1] = CommonPacket::HexToChar(crcLine->text().toStdString()[2], crcLine->text().toStdString()[3]);
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

void udpDialog::cancelButtonPressed()
{
    reject();
}

udpDialog::~udpDialog()
{
    delete ui;
    delete packet;
}
