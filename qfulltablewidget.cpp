#include "qfulltablewidget.h"

QFullTableWidget::QFullTableWidget(QWidget *parent) : QTableWidget(parent)
{

}

void QFullTableWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
    QTableWidget::mouseReleaseEvent(e);
}
