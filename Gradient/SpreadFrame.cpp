#include "SpreadFrame.h"
#include "ui_SpreadFrame.h"

SpreadFrame::SpreadFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpreadFrame)
{
    ui->setupUi(this);
}

SpreadFrame::~SpreadFrame()
{
    delete ui;
}

QGradient::Spread SpreadFrame::getSpread()
{
    QGradient::Spread spread = QGradient::PadSpread;
    auto index = ui->comboBox_spread->currentIndex();
    if(index == 0)
    {
        spread = QGradient::PadSpread;
    }else if(index == 1)
    {
        spread = QGradient::RepeatSpread;
    }else if(index == 2)
    {
        spread = QGradient::ReflectSpread;
    }
    return spread;
}

QString SpreadFrame::getSpreadCode()
{
    auto index = ui->comboBox_spread->currentIndex();
    if(index == 0)
    {
        return "QGradient::PadSpread";
    }else if(index == 1)
    {
        return "QGradient::RepeatSpread";
    }else if(index == 2)
    {
        return "QGradient::ReflectSpread";
    }
    return "";
}

QString SpreadFrame::getCurSpreadText()
{
    return ui->comboBox_spread->currentText();
}

void SpreadFrame::setCurSpreadText(const QString &text)
{
    ui->comboBox_spread->setCurrentText(text);
}

void SpreadFrame::setQssText(const QString &text)
{
    if(text == "spread:pad")
    {
        ui->comboBox_spread->setCurrentIndex(0);
    }else if(text == "spread:repeat")
    {
        ui->comboBox_spread->setCurrentIndex(1);
    }
    else if(text == "spread:reflect")
    {
        ui->comboBox_spread->setCurrentIndex(2);
    }
}

void SpreadFrame::on_comboBox_spread_activated(int index)
{
    Q_UNUSED(index)
    emit changedSig();
}

