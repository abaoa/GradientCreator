#include "GradientColorFrame.h"
#include "ui_GradientColorFrame.h"
#pragma execution_character_set("utf-8")

GradientColorFrame::GradientColorFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GradientColorFrame)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("渐变色生成器"));

    mFrameBaseList.append(ui->frame_linear);
    mFrameBaseList.append(ui->frame_conical);
    mFrameBaseList.append(ui->frame_radial);

    for (int i = 0; i < mFrameBaseList.size(); i++)
    {
       auto base = mFrameBaseList[i];
       base->setContentFrame(ui->frame_content);
       base->setResultFrame(ui->frame_result);
    }

    connect(ui->frame_result,&ResultFrame::resultActionSig,
            this,&GradientColorFrame::resultActionSlot);
    connect(ui->frame_result,&ResultFrame::genCodeSig,
            this,&GradientColorFrame::genCodeSlot);

    connect(ui->frame_content,&GradientColorContentFrame::changedSig,
            this,[this]{
        QVariantList list;
        resultActionSlot(0,list);
    });
}

GradientColorFrame::~GradientColorFrame()
{
    delete ui;
}

void GradientColorFrame::on_pushButton_add_clicked()
{
    ui->frame_content->addItem();
}

void GradientColorFrame::resultActionSlot(int action, const QVariantList &list)
{
    auto index = ui->tabWidget->currentIndex();
    auto base = mFrameBaseList[index];
    if(action == 0)
    {
        base->genStyle();
    }else if(action == 2) //解析
    {
        auto text = list[0].toString();
        for (int i = 0; i < mFrameBaseList.size(); i++)
        {
            auto base = mFrameBaseList[i];
            auto isok = base->qssText2Gradient(text);
            if(isok)
            {
                ui->tabWidget->setCurrentIndex(i);
            }
        }
    }
}

void GradientColorFrame::genCodeSlot(const QString &objName, bool isPointer)
{
    ui->frame_result->clear();

    auto index = ui->tabWidget->currentIndex();
    auto base = mFrameBaseList[index];
    base->genCode(objName,isPointer);
}


void GradientColorFrame::on_pushButton_addDefault_clicked()
{
    ui->frame_content->addDefaultItem();
}


void GradientColorFrame::on_pushButton_clear_clicked()
{
    ui->frame_content->clear();
}


void GradientColorFrame::on_pushButton_save_clicked()
{
    auto settings = ui->frame_content->save();
    if(settings)
    {
        for (int i = 0; i < mFrameBaseList.size(); i++)
        {
           auto base = mFrameBaseList[i];
           base->save(settings);
        }
    }
}


void GradientColorFrame::on_pushButton_load_clicked()
{
    auto settings = ui->frame_content->load();
    if(settings)
    {
        for (int i = 0; i < mFrameBaseList.size(); i++)
        {
           auto base = mFrameBaseList[i];
           base->load(settings);
        }
    }
}


void GradientColorFrame::on_tabWidget_currentChanged(int index)
{
    auto base = mFrameBaseList[index];
    base->genStyle();
}

