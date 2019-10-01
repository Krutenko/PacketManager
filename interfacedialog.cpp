#include "interfacedialog.h"
#include "ui_interfacedialog.h"

InterfaceDialog::InterfaceDialog(vector<string> interfaces, bool many, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceDialog)
{
    int i;
    QRect rect;
    ui->setupUi(this);
    mainLayout = new QGridLayout(this);
    intLabel = new QLabel(this);
    allLabel = new QLabel(this);
    intBox = new QComboBox(this);
    allBox = new QCheckBox(this);
    okButton = new QPushButton(this);
    setWindowTitle("Interface");
    rect = QApplication::desktop()->screenGeometry();
    int x = rect.width() * 4 / 10;
    int y = rect.height() * 4 / 10;
    int w = rect.width() * 2 / 10;
    int h = rect.height() * 2 / 10;
    this->setGeometry(x, y, w, h);
    okButton->setText(QString("OK"));
    okButton->setAutoDefault(true);
    okButton->setDefault(true);
    for (i = 0; i < 6; i++)
        mainLayout->setColumnStretch(i, 1);
    for (i = 0; i < 6; i++)
        mainLayout->setRowStretch(i, 1);
    intLabel->setText("Choose the interface:");
    allLabel->setText("Use this interface for all downloaded files:");
    for (i = 0; i < interfaces.size(); i++)
        intBox->addItem(QString::fromStdString(interfaces[i]));
    allBox->setChecked(true);
    if (!many)
    {
        QPalette *palette;
        palette = new QPalette();
        palette->setColor(QPalette::WindowText, Qt::darkGray);
        allLabel->setPalette(*palette);
        allBox->setEnabled(false);
        delete palette;
    }
    mainLayout->addWidget(intLabel, 1, 0);
    mainLayout->addWidget(intBox, 1, 1, 1, 5);
    mainLayout->addWidget(allLabel, 3, 1);
    mainLayout->addWidget(allBox, 3, 2);
    mainLayout->addWidget(okButton, 5, 5);
    setLayout(mainLayout);
    connect(okButton, SIGNAL(released()), this, SLOT(okButtonPressed()));
}

void InterfaceDialog::okButtonPressed()
{
    Index = intBox->currentIndex();
    Forall = allBox->isChecked();
    accept();
}

InterfaceDialog::~InterfaceDialog()
{
    delete ui;
}
