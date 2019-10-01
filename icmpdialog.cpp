#include "icmpdialog.h"
#include "ui_icmpdialog.h"

icmpDialog::icmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::icmpDialog)
{
    int i;
    QRect rect;
    QRegExp typeExp;
    QRegExp codeExp;
    QRegExp crcExp;
    QRegExp idExp;
    QRegExp seqExp;
    QRegExpValidator *typeVal;
    QRegExpValidator *codeVal;
    QRegExpValidator *crcVal;
    QRegExpValidator *idVal;
    QRegExpValidator *seqVal;
    ui->setupUi(this);
    packet = new icmpPacket();
    mainLayout = new QGridLayout(this);
    smallLayout = new QGridLayout(this);
    smallWidget = new QWidget(this);
    typeLabel = new QLabel(this);
    codeLabel = new QLabel(this);
    crcLabel = new QLabel(this);
    idLabel = new QLabel(this);
    seqLabel = new QLabel(this);
    typeLine = new QLineEdit(this);
    codeLine = new QLineEdit(this);
    crcLine = new QLineEdit(this);
    idLine = new QLineEdit(this);
    seqLine = new QLineEdit(this);
    codeWidget = new QWidget(this);
    crcWidget = new QWidget(this);
    autWidget = new QWidget(this);
    codeLayout = new QGridLayout(this);
    crcLayout = new QGridLayout(this);
    autLayout = new QGridLayout(this);
    codeBox = new QCheckBox(this);
    crcBox = new QCheckBox(this);
    autBox = new QCheckBox(this);
    codeAutoLabel = new QLabel(this);
    crcAutoLabel = new QLabel(this);
    autAutoLabel = new QLabel(this);
    msgLabel = new QLabel(this);
    msgText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    setWindowTitle("ICMP");
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
    typeLabel->setText("Type:");
    codeLabel->setText("Code:");
    crcLabel->setText("Checksum:");
    idLabel->setText("Identifier:");
    seqLabel->setText("Sequence Number:");
    codeAutoLabel->setText("Automatically");
    crcAutoLabel->setText("Automatically");
    autAutoLabel->setText("All automatically");
    msgLabel->setText("Payload:");
    typeLine->setPlaceholderText("Dec");
    codeLine->setPlaceholderText("Dec");
    crcLine->setPlaceholderText("Hex");
    idLine->setPlaceholderText("Dec");
    seqLine->setPlaceholderText("Dec");
    msgText->setPlaceholderText("Hex");
    typeExp = QRegExp("([1-9][0-9]{,2})|0");
    codeExp = QRegExp("([1-9][0-9]{,2})|0");
    crcExp = QRegExp("[0-9a-fA-F]{4}");
    idExp = QRegExp("([1-9][0-9]{,4})|0");
    seqExp = QRegExp("([1-9][0-9]{,4})|0");
    typeVal = new QRegExpValidator(typeExp, this);
    codeVal = new QRegExpValidator(codeExp, this);
    crcVal = new QRegExpValidator(crcExp, this);
    idVal = new QRegExpValidator(idExp, this);
    seqVal = new QRegExpValidator(seqExp, this);
    typeLine->setValidator(typeVal);
    codeLine->setValidator(codeVal);
    crcLine->setValidator(crcVal);
    idLine->setValidator(idVal);
    seqLine->setValidator(seqVal);
    smallLayout->addWidget(typeLabel, 0, 0);
    smallLayout->addWidget(codeLabel, 1, 0);
    smallLayout->addWidget(crcLabel, 2, 0);
    smallLayout->addWidget(idLabel, 3, 0);
    smallLayout->addWidget(seqLabel, 4, 0);
    smallLayout->addWidget(typeLine, 0, 1);
    smallLayout->addWidget(codeLine, 1, 1);
    smallLayout->addWidget(crcLine, 2, 1);
    smallLayout->addWidget(idLine, 3, 1);
    smallLayout->addWidget(seqLine, 4, 1);
    smallLayout->addWidget(codeWidget, 1, 2);
    smallLayout->addWidget(crcWidget, 2, 2);
    smallLayout->addWidget(autWidget, 12, 2);
    codeWidget->setLayout(codeLayout);
    crcWidget->setLayout(crcLayout);
    autWidget->setLayout(autLayout);
    codeLayout->addWidget(codeAutoLabel, 0, 0);
    crcLayout->addWidget(crcAutoLabel, 0, 0);
    autLayout->addWidget(autAutoLabel, 0, 0);
    codeLayout->addWidget(codeBox, 0, 1);
    crcLayout->addWidget(crcBox, 0, 1);
    autLayout->addWidget(autBox, 0, 1);
    smallLayout->addWidget(msgLabel, 0, 4);
    smallLayout->addWidget(msgText, 0, 5, 10, 5);
    smallWidget->setLayout((smallLayout));
    connect(codeBox, SIGNAL(stateChanged(int)), this, SLOT(codeStateChanged()));
    connect(crcBox, SIGNAL(stateChanged(int)), this, SLOT(crcStateChanged()));
    connect(autBox, SIGNAL(stateChanged(int)), this, SLOT(autStateChanged()));
    connect(msgText, SIGNAL(textChanged()), this, SLOT(textValidator()));
    connect(saveButton, SIGNAL(released()), this, SLOT(saveButtonPressed()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(cancelButtonPressed()));
}

void icmpDialog::codeStateChanged()
{
    QPalette *palette;
    disconnect(codeLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    if (codeBox->isChecked())
    {
        codeLine->setReadOnly(true);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::lightGray);
        palette->setColor(QPalette::Text, Qt::darkGray);
        codeLine->setPalette(*palette);
        codeLine->setText(QString("Auto"));
        if (crcBox->isChecked())
            autBox->setChecked(true);
    }
    else
    {
        codeLine->setReadOnly(false);
        palette = new QPalette();
        palette->setColor(QPalette::Base, Qt::white);
        palette->setColor(QPalette::Text, Qt::black);
        codeLine->setPalette(*palette);
        codeLine->setText(QString(""));
        if (!crcBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void icmpDialog::crcStateChanged()
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
        if (codeBox->isChecked())
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
        if (!codeBox->isChecked())
            autBox->setChecked(false);
    }
    delete palette;
}

void icmpDialog::autStateChanged()
{
    if (autBox->isChecked())
    {
        codeBox->setChecked(true);
        crcBox->setChecked(true);
    }
    else
    {
        codeBox->setChecked(false);
        crcBox->setChecked(false);
    }
}

void icmpDialog::recolour()
{
    QLineEdit *line = qobject_cast<QLineEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    line->setPalette(*palette);
    disconnect(line, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
    delete palette;
}

void icmpDialog::recolourText()
{
    QTextEdit *text = qobject_cast<QTextEdit*>(sender());
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    text->setPalette(*palette);
    disconnect(text, SIGNAL(textChanged()), this, SLOT(recolour()));
    delete palette;
}

void icmpDialog::textValidator()
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

void icmpDialog::setPacket(icmpPacket *pkt)
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
    typeLine->setText(QString::fromStdString(to_string((int) pkt->Type)));
    codeLine->setText(QString::fromStdString(to_string((int) pkt->Code)));
    crcLine->setText(QString::fromStdString(crcStr));
    idLine->setText(QString::fromStdString(to_string(pkt->Identifier)));
    seqLine->setText(QString::fromStdString(to_string(pkt->SequenceNumber)));
    msgText->setText(QString::fromStdString(msgStr));
}

void icmpDialog::saveButtonPressed()
{
    unsigned int i, totalLen;
    unsigned int err = 0;
    unsigned char cnt, resNum = 0, flagNum = 0;
    string token;
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::red);
    totalLen = 65535 - 40 - 16;
    if (typeLine->text().isEmpty() || stoi(typeLine->text().toStdString()) > 255)
    {
        typeLine->setPalette(*palette);
        connect(typeLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (codeLine->text().isEmpty() || stoi(codeLine->text().toStdString()) > 255)
    {
        codeLine->setPalette(*palette);
        connect(codeLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (crcLine->text().isEmpty() || crcLine->text().length() != 4)
    {
        crcLine->setPalette(*palette);
        connect(crcLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (idLine->text().isEmpty() || stoi(idLine->text().toStdString()) > 65535)
    {
        idLine->setPalette(*palette);
        connect(idLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
        err++;
    }
    if (seqLine->text().isEmpty() || stoi(seqLine->text().toStdString()) > 65535)
    {
        seqLine->setPalette(*palette);
        connect(seqLine, SIGNAL(textChanged(const QString&)), this, SLOT(recolour()));
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
    packet->Type = stoi(typeLine->text().toStdString());
    packet->Code = stoi(codeLine->text().toStdString());
    packet->Checksum[0] = CommonPacket::HexToChar(crcLine->text().toStdString()[0], crcLine->text().toStdString()[1]);
    packet->Checksum[1] = CommonPacket::HexToChar(crcLine->text().toStdString()[2], crcLine->text().toStdString()[3]);
    packet->Identifier = stoi(idLine->text().toStdString());
    packet->SequenceNumber = stoi(seqLine->text().toStdString());
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

void icmpDialog::cancelButtonPressed()
{
    reject();
}

icmpDialog::~icmpDialog()
{
    delete ui;
    delete packet;
}
