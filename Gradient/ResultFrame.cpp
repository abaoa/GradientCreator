#include "ResultFrame.h"
#include "qmenu.h"
#include "ui_ResultFrame.h"
#include "GradientColor.h"
#include <QApplication>
#include <QClipboard>
#include <QInputDialog>

#pragma execution_character_set("utf-8")
ResultFrame::ResultFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ResultFrame)
{
    ui->setupUi(this);

    auto list = GradientColor::GetColorItemList();
    ui->comboBox_color->addItems(list);
    ui->comboBox_color->setCurrentIndex(1);
    on_comboBox_color_activated(1);

    connect(ui->frame_collection,&CollectionFrame::textSig,
            this,[this](const QString &text){
         setResult(text,0);
         on_pushButton_split_clicked();
    });
}

ResultFrame::~ResultFrame()
{
    delete ui;
}

void ResultFrame::setResult(const QString &text, int type)
{
    ui->textEdit->setPlainText(text);
    if(type == 0)
    {
        resultSlot(text);
    }else
    {
        qApp->clipboard()->setText(text);
    }
}

QString ResultFrame::getResult()
{
    return ui->textEdit->toPlainText();
}

void ResultFrame::clear()
{
    ui->textEdit->clear();
}

QString ResultFrame::getQssText(const QString &text)
{
    return ui->comboBox_color->currentText() + ":" + text;
}

void ResultFrame::resultSlot(const QString &text)
{
    auto result = this->getQssText(text);
    QString border;
    border.append("border-width: 6px;");
    border.append("border-style: solid;");

    border = result.contains("border")?border:QString("");
    auto qss = QString("QPushButton{%2%1}").arg(result,border);
    ui->pushButton_result->setStyleSheet(qss);
}


void ResultFrame::on_pushButton_apply_clicked()
{
    resultSlot(ui->textEdit->toPlainText());
}

void ResultFrame::on_pushButton_genStyle_clicked()
{
    QVariantList list;
    emit resultActionSig(0,list);
}
void ResultFrame::on_pushButton_genCode_clicked()
{
    auto objName = ui->lineEdit_objName->text();
    emit genCodeSig(objName,ui->checkBox_isPointer->isChecked());
}

void ResultFrame::on_pushButton_copy_clicked()
{
    qApp->clipboard()->setText(getQssText(ui->textEdit->toPlainText()));
}

void ResultFrame::on_comboBox_color_activated(int index)
{
    on_pushButton_copy_clicked();
    on_pushButton_apply_clicked();

    if(index == 0)
    {
        ui->pushButton_result->setText(tr("文字效果"));
    }else
    {
        ui->pushButton_result->setText("");
    }
}


void ResultFrame::on_pushButton_split_clicked()
{
    auto text = ui->textEdit->toPlainText();
    if(text.isEmpty()) return;

    QVariantList list;
    list << text;
    emit resultActionSig(2,list);
}


void ResultFrame::on_pushButton_collection_clicked()
{
    auto text = ui->textEdit->toPlainText();
    if(text.isEmpty()) return;

    auto name = QInputDialog::getText(this,tr("起个名字吧！"),tr("起个名字吧！"));
    if(!name.isEmpty())
    {
        ui->frame_collection->add(name,text);
    }
}

