#include "LinearGradientFrame.h"
#include "qdebug.h"
#include "ui_LinearGradientFrame.h"

#pragma execution_character_set("utf-8")
LinearGradientFrame::LinearGradientFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LinearGradientFrame)
{
    ui->setupUi(this);

    ui->frame_start->setTitle(tr("开始点"));
    ui->frame_end->setTitle(tr("结束点"));

    connect(ui->frame_start,&PointItemFrame::changedSig,
            this,[this]{this->genStyle();});
    connect(ui->frame_end,&PointItemFrame::changedSig,
            this,[this]{this->genStyle();});
    connect(ui->frame_spread,&SpreadFrame::changedSig,
            this,[this]{this->genStyle();});
}

LinearGradientFrame::~LinearGradientFrame()
{
    delete ui;
}

void LinearGradientFrame::setPoint(qreal x1, qreal y1, qreal x2, qreal y2)
{
    auto start = QPointF(x1,y1);
    auto end = QPointF(x2,y2);
    ui->frame_start->setPoint(start);
    ui->frame_end->setPoint(end);

    genStyle();
}

void LinearGradientFrame::genStyle()
{
    if(mContentFrame)
    {
        auto list = mContentFrame->getColorAtList();
        auto spread = ui->frame_spread->getSpread();
        auto result = GradientColor::LinearGradient(list,ui->frame_start->getPoint(),ui->frame_end->getPoint(),spread);
        mResultFrame->setResult(result,0);
    }
}


void LinearGradientFrame::on_pushButton_1_clicked()
{
    setPoint(0,0,1,0);
}

void LinearGradientFrame::on_pushButton_3_clicked()
{
    setPoint(1,0,0,0);
}

void LinearGradientFrame::on_pushButton_2_clicked()
{
    setPoint(0,0,0,1);
}
void LinearGradientFrame::on_pushButton_4_clicked()
{
    setPoint(0,1,0,0);
}


void LinearGradientFrame::on_pushButton_5_clicked()
{
    setPoint(0,0,1,1);
}


void LinearGradientFrame::on_pushButton_6_clicked()
{
    setPoint(1,1,0,0);
}


void LinearGradientFrame::on_pushButton_7_clicked()
{
    setPoint(1,0,0,1);
}


void LinearGradientFrame::on_pushButton_8_clicked()
{
    setPoint(0,1,1,0);
}



void LinearGradientFrame::save(QSettings *settings)
{
    settings->beginGroup("LinearGradientFrame");
    settings->setValue("spread",ui->frame_spread->getCurSpreadText());
    settings->setValue("startPoint",ui->frame_start->getPoint());
    settings->setValue("endPoint",ui->frame_end->getPoint());
    settings->endGroup();
}

void LinearGradientFrame::load(QSettings *settings)
{
    settings->beginGroup("LinearGradientFrame");
    auto spread = settings->value("spread",ui->frame_spread->getCurSpreadText()).value<QString>();
    auto startPoint = settings->value("startPoint",ui->frame_start->getPoint()).value<QPointF>();
    auto endPoint = settings->value("endPoint",ui->frame_end->getPoint()).value<QPointF>();
    settings->endGroup();

    ui->frame_spread->setCurSpreadText(spread);
    ui->frame_start->setPoint(startPoint);
    ui->frame_end->setPoint(endPoint);
}


SpreadFrame *LinearGradientFrame::getSpreadFrame()
{
    return ui->frame_spread;
}


void LinearGradientFrame::genCode(const QString &objName, bool isPointer)
{
    auto name = objName.isEmpty()? QString("gradient") : objName;
    auto pointerText = isPointer? QString("->") : QString(".");

    QStringList codeList;
    if(isPointer)
    {
        codeList << QString("auto %1 = new QLinearGradient();").arg(name);
    }else
    {
        codeList << QString("QLinearGradient %1;").arg(name);
    }

    codeList << QString("%1%2setSpread(%3);").arg(name,pointerText,ui->frame_spread->getSpreadCode());

    auto start = ui->frame_start->getPoint();
    codeList << QString("%1%2setStart(%3,%4);").arg(name,pointerText).arg(start.x()).arg(start.y());

    auto end = ui->frame_end->getPoint();
    codeList << QString("%1%2setFinalStop(%3,%4);").arg(name,pointerText).arg(end.x()).arg(end.y());

    auto list = getColorAtCodeList(name,pointerText);
    codeList.append(list);

    mResultFrame->setResult(codeList.join("\n"),1);
}


bool LinearGradientFrame::qssText2Gradient(const QString &text)
{
    QString flag("qlineargradient");
    if(!text.contains(flag))
    {
        return false;
    }

    auto index = text.indexOf(flag);
    auto start = index + flag.size() + 1;
    auto end = text.size() - start - 2;
    auto content = text.mid(start,end);

    QString douHao(",");
    QString spread("spread");

    auto spreadIndex = content.indexOf(spread);
    auto douHaoIndex = content.indexOf(douHao,spreadIndex);
    auto spreadText = content.mid(spreadIndex,douHaoIndex).trimmed();
    ui->frame_spread->setQssText(spreadText);

    QString stop("stop");
    auto stopIndex = content.indexOf(stop);
    auto stopText = content.mid(stopIndex,-1).trimmed();
    mContentFrame->initByText(stopText);

    qreal points[4] = {0};
    auto valueText = content.mid(douHaoIndex,stopIndex-douHaoIndex).trimmed();
    auto valueList = valueText.split(douHao,Qt::SkipEmptyParts);
    for (int i = 0; i < valueList.size(); i++)
    {
        auto text = valueList[i];
        text = text.trimmed();
        auto name = text.section(':',0,0);
        auto value = text.section(':',1,1);
        auto v = value.toDouble();
        if(name == "x1") points[0] = v;
        if(name == "y1") points[1] = v;
        if(name == "x2") points[2] = v;
        if(name == "y2") points[3] = v;
    }

    setPoint(points[0],points[1],points[2],points[3]);

    return true;
}
