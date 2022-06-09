#include "PointItemFrame.h"
#include "ui_PointItemFrame.h"

PointItemFrame::PointItemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PointItemFrame)
{
    ui->setupUi(this);
}

PointItemFrame::~PointItemFrame()
{
    delete ui;
}

void PointItemFrame::setTitle(const QString &text)
{
    ui->groupBox->setTitle(text);
}

void PointItemFrame::setPoint(QPointF point)
{
    ui->doubleSpinBox_x->blockSignals(true);
    ui->doubleSpinBox_y->blockSignals(true);

    ui->doubleSpinBox_x->setValue(point.x());
    ui->doubleSpinBox_y->setValue(point.y());

    ui->doubleSpinBox_x->blockSignals(false);
    ui->doubleSpinBox_y->blockSignals(false);

}

QPointF PointItemFrame::getPoint()
{
    return QPointF(ui->doubleSpinBox_x->value(),ui->doubleSpinBox_y->value());
}

void PointItemFrame::on_doubleSpinBox_x_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    emit changedSig();
}


void PointItemFrame::on_doubleSpinBox_y_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    emit changedSig();
}

