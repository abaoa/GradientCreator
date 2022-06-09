#include "GradienBoxtItemFrame.h"
#include "ui_GradienBoxtItemFrame.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QMenu>
#include <QInputDialog>
#include <QApplication>
#include <QClipboard>
#pragma execution_character_set("utf-8")

GradienBoxtItemFrame::GradienBoxtItemFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GradienBoxtItemFrame)
{
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
}

GradienBoxtItemFrame::~GradienBoxtItemFrame()
{
    delete ui;
}

QString GradienBoxtItemFrame::name() const
{
    return ui->label->text();
}

void GradienBoxtItemFrame::setName(const QString &newName)
{
    ui->label->setText(newName);
}

QString GradienBoxtItemFrame::gradientText() const
{
    return this->property("GradientText").toString();
}

void GradienBoxtItemFrame::setGradientText(const QString &newGradientText)
{
    this->setProperty("GradientText",newGradientText);
    ui->pushButton->setStyleSheet(QString("background-color:%1;").arg(newGradientText));
}

void GradienBoxtItemFrame::on_pushButton_clicked()
{
    QVariantList list;
    list << gradientText();
    emit resultActionSig(0,list);
}


void GradienBoxtItemFrame::on_GradienBoxtItemFrame_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu menu(this);
    menu.addAction(ui->action_del);
    menu.addAction(ui->action_copy);
    menu.addAction(ui->action_rename);
    menu.exec(QCursor::pos());
}


void GradienBoxtItemFrame::on_action_del_triggered()
{
    QVariantList list;
    list << gradientText();
    emit resultActionSig(1,list);
}


void GradienBoxtItemFrame::on_action_copy_triggered()
{
    auto text = gradientText();
    qApp->clipboard()->setText(text);
}


void GradienBoxtItemFrame::on_action_rename_triggered()
{
    auto name = QInputDialog::getText(this,tr("重命名"),tr("起个名字吧！"));
    if(!name.isEmpty())
    {
       ui->label->setText(name);
    }
}

