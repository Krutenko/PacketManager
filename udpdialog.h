#ifndef UDPDIALOG_H
#define UDPDIALOG_H

#include <QDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRegExpValidator>

#include <sstream>
#include <string>
#include "udppacket.h"

using namespace std;

namespace Ui {
class udpDialog;
}

class udpDialog : public QDialog
{
    Q_OBJECT

public:
    udpPacket *packet;
    void setPacket(udpPacket *pkt);
    explicit udpDialog(QWidget *parent = nullptr);
    ~udpDialog();

private slots:
    void lenStateChanged();
    void crcStateChanged();
    void autStateChanged();
    void saveButtonPressed();
    void cancelButtonPressed();
    void recolour();
    void recolourText();
    void textValidator();

private:
    Ui::udpDialog *ui;
    QGridLayout *mainLayout;
    QWidget *smallWidget;
    QGridLayout *smallLayout;
    QLabel *srcLabel;
    QLabel *dstLabel;
    QLabel *lenLabel;
    QLabel *crcLabel;
    QLabel *msgLabel;
    QLineEdit *srcLine;
    QLineEdit *dstLine;
    QLineEdit *lenLine;
    QLineEdit *crcLine;
    QTextEdit *msgText;
    QWidget *lenWidget;
    QWidget *crcWidget;
    QWidget *autWidget;
    QGridLayout *lenLayout;
    QGridLayout *crcLayout;
    QGridLayout *autLayout;
    QLabel *lenAutoLabel;
    QLabel *crcAutoLabel;
    QLabel *autAutoLabel;
    QCheckBox *lenBox;
    QCheckBox *crcBox;
    QCheckBox *autBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif
