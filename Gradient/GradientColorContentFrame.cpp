#include "GradientColorContentFrame.h"
#include "qboxlayout.h"
#include "ui_GradientColorContentFrame.h"
#include <QRandomGenerator>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>

GradientColorContentFrame::GradientColorContentFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GradientColorContentFrame)
{
    ui->setupUi(this);

    mItemLayout = new QVBoxLayout(ui->contents);
    mItemLayout->setAlignment(Qt::AlignTop);

}

GradientColorContentFrame::~GradientColorContentFrame()
{
    delete ui;
}

void GradientColorContentFrame::addItem()
{
    addItem(ColorItemData());
}

void GradientColorContentFrame::addDefaultItem()
{
    for (int i = 0; i <= 10; i++)
    {
        auto data = ColorItemData();
        data.step = i/10.0;

        QList<int> list;
        for (int j = 0; j < 3; j++)
        {
           auto v = QRandomGenerator::global()->bounded(0,256);
           list.append(v);
        }

        data.color = QColor(list[0],list[1],list[2],255).name();

        addItem(data);
    }
}

void GradientColorContentFrame::clear()
{
    clearLayout();

    for (int i = 0; i < mItemList.size(); i++)
    {
       auto item = mItemList.takeAt(i);
       delete item;
       i = 0;
    }
    mItemList.clear();
}

QSettings *GradientColorContentFrame::save()
{
    auto filePath = QFileDialog::getSaveFileName(this,"","","*.gradient");
    if(filePath.isEmpty()) return nullptr;

    QSettings *settings = new QSettings(filePath,QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->beginGroup("General");
    settings->endGroup();

    //ItemData
    settings->beginWriteArray("ItemData");
    for (int i = 0; i < mItemList.size(); ++i)
    {
        settings->setArrayIndex(i);
        auto data = mItemList[i]->data();
        settings->setValue("color",data.color);
        settings->setValue("isUsed",data.isUsed);
        settings->setValue("step",data.step);
    }
    settings->endArray();

    return settings;
}

QSettings *GradientColorContentFrame::load()
{
    auto filePath = QFileDialog::getOpenFileName(this,"","","*.gradient");
    if(filePath.isEmpty()) return nullptr;

    this->clear();

    QSettings *settings = new QSettings(filePath,QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->beginGroup("General");
    settings->endGroup();

    //ItemData
    auto size = settings->beginReadArray("ItemData");
    for (int i = 0; i < size; ++i)
    {
        settings->setArrayIndex(i);
        ColorItemData data;
        data.color = settings->value("color",data.color).value<QString>();
        data.isUsed = settings->value("isUsed",data.isUsed).value<bool>();
        data.step = settings->value("step",data.step).value<qreal>();
        addItem(data);
    }
    settings->endArray();
    return settings;
}

void GradientColorContentFrame::toLayout()
{
    clearLayout();
    for (int i = 0; i < mItemList.size(); i++)
    {
       auto item = mItemList[i];
       mItemLayout->addWidget(item);
    }
}

void GradientColorContentFrame::clearLayout()
{
    while(1)
    {
        auto item = mItemLayout->takeAt(0);
        if(item == nullptr)
        {
            break;
        }else
        {
            item->widget()->setParent(nullptr);
        }
    }
}

ColorAtList GradientColorContentFrame::getColorAtList()
{
    ColorAtList list;

    for (int i = 0; i < mItemList.size(); i++)
    {
       auto item = mItemList[i];
       auto data = item->data();
       if(data.isUsed)
       {
           auto pair = GradientColor::GenStepPair(data.step,data.color);
           list.append(pair);
       }
    }

    return list;
}

void GradientColorContentFrame::initByText(const QString &text)
{
    clear();

    QString stop("stop");
    auto temp = text;
    while(1)
    {
        auto stopIndex = temp.indexOf(stop);
        auto nextIndex = temp.indexOf(stop,stopIndex + stop.size());
        if(stopIndex == -1) break;
        auto stopOne = temp.mid(stopIndex,nextIndex - stopIndex).trimmed();
        temp.remove(stopIndex,stopOne.size());

        QString stepText;
        ColorItemData itemData;
        if(stopOne.contains("rgba"))
        {
            //stop:0 rgba(255, 178, 102, 255)
            auto left = stopOne.indexOf("(");
            auto right = stopOne.indexOf(")");
            auto text = stopOne.mid(left+1,right-left-1).trimmed();
            text.remove(" ");

            QColor color;
            color.setRed(text.section(',',0,0).toInt());
            color.setGreen(text.section(',',1,1).toInt());
            color.setBlue(text.section(',',2,2).toInt());
            color.setAlpha(text.section(',',3,3).toInt());
            if(color.isValid())
                itemData.color = color.name(QColor::HexArgb);

            auto index = stopOne.indexOf("rgba");
            stepText = stopOne.mid(0,index).trimmed();
        }else
        {
            auto left = stopOne.indexOf("#");
            auto text = stopOne.mid(left).trimmed();
            text.remove(",");

            itemData.color = text;

            stepText = stopOne.mid(0,left).trimmed();
        }

        auto step = stepText.section(':',1,1);
        itemData.step = step.toDouble();

        addItem(itemData);
    }
}

void GradientColorContentFrame::actionSlot(int type)
{
    auto item = static_cast<GradientColorItemFrame*>(this->sender());
    if(type == 0)
    {
        for (int i = 0; i < mItemList.size(); i++)
        {
           auto temp = mItemList[i];
           if(temp == item)
           {
               mItemList.removeAt(i);
               toLayout();
               break;
           }
        }
    }
}

void GradientColorContentFrame::addItem(const ColorItemData &data)
{
    auto item = new GradientColorItemFrame;
    item->setData(data);
    connect(item,&GradientColorItemFrame::actionSig,
            this,&GradientColorContentFrame::actionSlot);
    connect(item,&GradientColorItemFrame::changedSig,
            this,&GradientColorContentFrame::changedSig);
    mItemList.append(item);
    toLayout();
}
