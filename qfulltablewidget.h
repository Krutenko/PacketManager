#ifndef QFULLTABLEWIDGET_H
#define QFULLTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QMouseEvent>

class QFullTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QFullTableWidget(QWidget *parent);
private slots:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void rightClicked();
};

#endif
