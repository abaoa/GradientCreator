#include "CollectionFrame.h"
#include "ui_CollectionFrame.h"
#include <QSettings>

CollectionFrame::CollectionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CollectionFrame)
{
    ui->setupUi(this);

    mLayout = new FlowLayout(ui->contents);

    load();
}

CollectionFrame::~CollectionFrame()
{
    delete ui;
}

void CollectionFrame::add(const QString &name, const QString &gradientText)
{
    auto box = new GradienBoxtItemFrame;
    box->setName(name);
    box->setGradientText(gradientText);

    connect(box,&GradienBoxtItemFrame::resultActionSig,
            this,&CollectionFrame::resultActionSlot);
    mItemList.append(box);

    toLayout();
}

void CollectionFrame::save()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + QString("/CollectionGradient.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("General");
    settings.endGroup();

    settings.beginWriteArray("item");
    for (int i = 0; i < mItemList.size(); i++)
    {
        auto item = mItemList[i];
        settings.setArrayIndex(i);
        settings.setValue("name",item->name());
        settings.setValue("text",item->gradientText());
    }
    settings.endArray();
}

void CollectionFrame::load()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + QString("/CollectionGradient.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("General");
    settings.endGroup();

    auto size = settings.beginReadArray("item");
    for (int i = 0; i < size; i++)
    {
        settings.setArrayIndex(i);
        auto name = settings.value("name").toString();
        auto text = settings.value("text").toString();
        this->add(name,text);
    }
    settings.endArray();
}


void CollectionFrame::toLayout()
{
    clearLayout();
    for (int i = 0; i < mItemList.size(); i++)
    {
       auto item = mItemList[i];
       mLayout->addWidget(item);
    }

    save();
}

void CollectionFrame::clearLayout()
{
    while(1)
    {
        auto item = mLayout->takeAt(0);
        if(item == nullptr)
        {
            break;
        }else
        {
            item->widget()->setParent(nullptr);
        }
    }
}

void CollectionFrame::resultActionSlot(int action, const QVariantList &list)
{
    if(action == 0) //点击
    {
        auto text = list[0].toString();
        emit textSig(text);
    }else if(action == 1) //删除
    {
        auto p = static_cast<GradienBoxtItemFrame*>(this->sender());
        for (int i = 0; i < mItemList.size(); i++)
        {
           if(mItemList.at(i) == p)
           {
               auto item = mItemList.takeAt(i);

               toLayout();

               item->setParent(nullptr);
               item->deleteLater();
               break;
           }
        }

    }else if(action == 2) //
    {

    }
}
