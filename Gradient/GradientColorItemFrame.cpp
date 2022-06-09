#include "GradientColorItemFrame.h"
#include "ui_GradientColorItemFrame.h"
#include <QColorDialog>

GradientColorItemFrame::GradientColorItemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GradientColorItemFrame)
{
    ui->setupUi(this);
    ui->frame_2->setVisible(false);
}

GradientColorItemFrame::~GradientColorItemFrame()
{
    delete ui;
}

void GradientColorItemFrame::on_pushButton_color_clicked()
{
    auto oldColor = QColor(ui->lineEdit_color->text());
    oldColor = oldColor.isValid()?oldColor:QColor(Qt::white);
    auto color = QColorDialog::getColor(oldColor);
    if(color.isValid())
    {
        ui->lineEdit_color->setText(color.name());
    }
}


void GradientColorItemFrame::on_lineEdit_color_textChanged(const QString &arg1)
{
    if(QColor(arg1).isValid())
    {
        ui->lineEdit_color->setStyleSheet(QString("color:%1").arg(arg1));
        emit changedSig();
    }
}


void GradientColorItemFrame::on_pushButton_del_clicked()
{
    emit actionSig(0);
}

const ColorItemData &GradientColorItemFrame::data()
{
    mData.isUsed = ui->checkBox_isUsed->isChecked();
    mData.step = ui->doubleSpinBox_step->value();
    mData.color = ui->lineEdit_color->text();
    return mData;
}

void GradientColorItemFrame::setData(const ColorItemData &data)
{
    mData = data;

    ui->checkBox_isUsed->blockSignals(true);
    ui->doubleSpinBox_step->blockSignals(true);
    ui->lineEdit_color->blockSignals(true);

    ui->checkBox_isUsed->setChecked(data.isUsed);
    ui->doubleSpinBox_step->setValue(data.step);
    ui->lineEdit_color->setText(data.color);

    ui->checkBox_isUsed->blockSignals(false);
    ui->doubleSpinBox_step->blockSignals(false);
    ui->lineEdit_color->blockSignals(false);
}


void GradientColorItemFrame::on_pushButton_more_clicked(bool checked)
{
    ui->frame_2->setVisible(checked);
}


void GradientColorItemFrame::on_checkBox_isUsed_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    emit changedSig();
}


void GradientColorItemFrame::on_doubleSpinBox_step_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changedSig();
}

