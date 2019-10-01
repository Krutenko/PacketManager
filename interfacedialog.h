#ifndef INTERFACEDIALOG_H
#define INTERFACEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>

#include <vector>
#include <string>

using namespace std;

namespace Ui {
class InterfaceDialog;
}

class InterfaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceDialog(vector<string> interfaces, bool many, QWidget *parent = nullptr);
    ~InterfaceDialog();
    unsigned char Index;
    bool Forall;

private slots:
    void okButtonPressed();

private:
    Ui::InterfaceDialog *ui;
    QGridLayout *mainLayout;
    QLabel *intLabel;
    QLabel *allLabel;
    QComboBox *intBox;
    QCheckBox *allBox;
    QPushButton *okButton;
};

#endif
