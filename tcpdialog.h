#ifndef TCPDIALOG_H
#define TCPDIALOG_H

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
#include "tcppacket.h"

using namespace std;

namespace Ui {
class tcpDialog;
}

class tcpDialog : public QDialog
{
    Q_OBJECT

public:
    tcpPacket *packet;
    void setPacket(tcpPacket *pkt);
    explicit tcpDialog(vector<string> interfaces, QWidget *parent = nullptr);
    ~tcpDialog();

private slots:
    void offStateChanged();
    void crcStateChanged();
    void autStateChanged();
    void saveButtonPressed();
    void cancelButtonPressed();
    void recolour();
    void recolourText();
    void textValidator();

private:
    Ui::tcpDialog *ui;
    QGridLayout *mainLayout;
    QWidget *smallWidget;
    QGridLayout *smallLayout;
    QLabel *srcLabel;
    QLabel *dstLabel;
    QLabel *seqLabel;
    QLabel *ackLabel;
    QLabel *offLabel;
    QLabel *resLabel;
    QLabel *flagLabel;
    QLabel *winLabel;
    QLabel *crcLabel;
    QLabel *urgLabel;
    QLabel *optLabel;
    QLabel *msgLabel;
    QLineEdit *srcLine;
    QLineEdit *dstLine;
    QLineEdit *seqLine;
    QLineEdit *ackLine;
    QLineEdit *offLine;
    QLineEdit *resLine;
    QLineEdit *flagLine;
    QLineEdit *winLine;
    QLineEdit *crcLine;
    QLineEdit *urgLine;
    QTextEdit *optText;
    QTextEdit *msgText;
    QWidget *offWidget;
    QWidget *crcWidget;
    QWidget *autWidget;
    QGridLayout *offLayout;
    QGridLayout *crcLayout;
    QGridLayout *autLayout;
    QLabel *offAutoLabel;
    QLabel *crcAutoLabel;
    QLabel *autAutoLabel;
    QCheckBox *offBox;
    QCheckBox *crcBox;
    QCheckBox *autBox;
    QLabel *ifLabel;
    QComboBox *ifBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif
