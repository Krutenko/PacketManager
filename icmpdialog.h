#ifndef ICMPDIALOG_H
#define ICMPDIALOG_H

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
#include "icmppacket.h"

using namespace std;

namespace Ui {
class icmpDialog;
}

class icmpDialog : public QDialog
{
    Q_OBJECT

public:
    icmpPacket *packet;
    void setPacket(icmpPacket *pkt);
    explicit icmpDialog(QWidget *parent = nullptr);
    ~icmpDialog();

private slots:
    void codeStateChanged();
    void crcStateChanged();
    void autStateChanged();
    void saveButtonPressed();
    void cancelButtonPressed();
    void recolour();
    void recolourText();
    void textValidator();

private:
    Ui::icmpDialog *ui;
    QGridLayout *mainLayout;
    QWidget *smallWidget;
    QGridLayout *smallLayout;
    QLabel *typeLabel;
    QLabel *codeLabel;
    QLabel *crcLabel;
    QLabel *idLabel;
    QLabel *seqLabel;
    QLabel *msgLabel;
    QLineEdit *typeLine;
    QLineEdit *codeLine;
    QLineEdit *crcLine;
    QLineEdit *idLine;
    QLineEdit *seqLine;
    QTextEdit *msgText;
    QWidget *codeWidget;
    QWidget *crcWidget;
    QWidget *autWidget;
    QGridLayout *codeLayout;
    QGridLayout *crcLayout;
    QGridLayout *autLayout;
    QLabel *codeAutoLabel;
    QLabel *crcAutoLabel;
    QLabel *autAutoLabel;
    QCheckBox *codeBox;
    QCheckBox *crcBox;
    QCheckBox *autBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif
