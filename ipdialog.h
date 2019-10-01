#ifndef IPDIALOG_H
#define IPDIALOG_H

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
#include <QComboBox>

#include <sstream>
#include <string>
#include <iostream>
#include "ippacket.h"

using namespace std;

namespace Ui {
class ipDialog;
}

class ipDialog : public QDialog
{
    Q_OBJECT

public:
    ipPacket *packet;
    void setPacket(ipPacket *pkt);
    explicit ipDialog(vector<string> interfaces, QWidget *parent = nullptr);
    ~ipDialog();

private slots:
    void ihlStateChanged();
    void lenStateChanged();
    void crcStateChanged();
    void srcStateChanged();
    void autStateChanged();
    void saveButtonPressed();
    void cancelButtonPressed();
    void recolour();
    void recolourText();
    void textValidator();

private:
    Ui::ipDialog *ui;
    QGridLayout *mainLayout;
    QWidget *smallWidget;
    QGridLayout *smallLayout;
    QLabel *verLabel;
    QLabel *ihlLabel;
    QLabel *tosLabel;
    QLabel *lenLabel;
    QLabel *idLabel;
    QLabel *flagLabel;
    QLabel *offLabel;
    QLabel *ttlLabel;
    QLabel *protLabel;
    QLabel *crcLabel;
    QLabel *srcLabel;
    QLabel *dstLabel;
    QLabel *optLabel;
    QLabel *msgLabel;
    QLineEdit *verLine;
    QLineEdit *ihlLine;
    QLineEdit *tosLine;
    QLineEdit *lenLine;
    QLineEdit *idLine;
    QLineEdit *flagLine;
    QLineEdit *offLine;
    QLineEdit *ttlLine;
    QLineEdit *protLine;
    QLineEdit *crcLine;
    QLineEdit *srcLine;
    QLineEdit *dstLine;
    QTextEdit *optText;
    QTextEdit *msgText;
    QWidget *ihlWidget;
    QWidget *lenWidget;
    QWidget *crcWidget;
    QWidget *srcWidget;
    QWidget *autWidget;
    QGridLayout *ihlLayout;
    QGridLayout *lenLayout;
    QGridLayout *crcLayout;
    QGridLayout *srcLayout;
    QGridLayout *autLayout;
    QLabel *ihlAutoLabel;
    QLabel *lenAutoLabel;
    QLabel *crcAutoLabel;
    QLabel *srcAutoLabel;
    QLabel *autAutoLabel;
    QCheckBox *ihlBox;
    QCheckBox *lenBox;
    QCheckBox *crcBox;
    QCheckBox *srcBox;
    QCheckBox *autBox;
    QLabel *ifLabel;
    QComboBox *ifBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif
