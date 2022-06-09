#include "ConicalGradientFrame.h"
#include "qdebug.h"
#include "ui_ConicalGradientFrame.h"
#pragma execution_character_set("utf-8")

ConicalGradientFrame::ConicalGradientFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConicalGradientFrame)
{
    ui->setupUi(this);

    ui->frame_center->setTitle(tr("中心点"));
    connect(ui->frame_center,&PointItemFrame::changedSig,
            this,[this]{this->genStyle();});
    connect(ui->frame_spread,&SpreadFrame::changedSig,
            this,[this]{this->genStyle();});
}

ConicalGradientFrame::~ConicalGradientFrame()
{
    delete ui;
}

void ConicalGradientFrame::setPoint(qreal x, qreal y, qreal angle)
{
    ui->frame_center->setPoint(QPointF(x,y));

    ui->doubleSpinBox_angle->blockSignals(true);
    ui->doubleSpinBox_angle->setValue(angle);
    ui->doubleSpinBox_angle->blockSignals(false);

    genStyle();
}


void ConicalGradientFrame::genStyle()
{
    if(mContentFrame)
    {
        auto list = mContentFrame->getColorAtList();
        auto spread = ui->frame_spread->getSpread();
        auto result = GradientColor::ConicalGradient(list,ui->frame_center->getPoint(),ui->doubleSpinBox_angle->value(),spread);
        mResultFrame->setResult(result,0);
    }
}

void ConicalGradientFrame::on_pushButton_1_clicked()
{
    setPoint(0.5,0.5,0);
}

void ConicalGradientFrame::save(QSettings *settings)
{
    settings->beginGroup("ConicalGradientFrame");
    settings->setValue("spread",ui->frame_spread->getCurSpreadText());
    settings->setValue("center",ui->frame_center->getPoint());
    settings->setValue("angle",ui->doubleSpinBox_angle->value());
    settings->endGroup();
}

void ConicalGradientFrame::load(QSettings *settings)
{
    settings->beginGroup("ConicalGradientFrame");
    auto spread = settings->value("spread",ui->frame_spread->getCurSpreadText()).value<QString>();
    auto center = settings->value("center",ui->frame_center->getPoint()).value<QPointF>();
    auto angle = settings->value("angle",ui->doubleSpinBox_angle->value()).value<qreal>();
    settings->endGroup();

    ui->frame_spread->setCurSpreadText(spread);
    ui->frame_center->setPoint(center);
    ui->doubleSpinBox_angle->setValue(angle);
}


SpreadFrame *ConicalGradientFrame::getSpreadFrame()
{
    return ui->frame_spread;
}


void ConicalGradientFrame::genCode(const QString &objName, bool isPointer)
{
    auto name = objName.isEmpty()? QString("gradient") : objName;
    auto pointerText = isPointer? QString("->") : QString(".");

    QStringList codeList;
    if(isPointer)
    {
        codeList << QString("auto %1 = new QConicalGradient();").arg(name);
    }else
    {
        codeList << QString("QConicalGradient %1;").arg(name);
    }

    codeList << QString("%1%2setSpread(%3);").arg(name,pointerText,ui->frame_spread->getSpreadCode());

    auto center = ui->frame_center->getPoint();
    codeList << QString("%1%2setCenter(%3,%4);").arg(name,pointerText).arg(center.x()).arg(center.y());

    auto angle = ui->doubleSpinBox_angle->value();
    codeList << QString("%1%2setAngle(%3);").arg(name,pointerText).arg(angle);

    auto list = getColorAtCodeList(name,pointerText);
    codeList.append(list);

    mResultFrame->setResult(codeList.join("\n"),1);
}


bool ConicalGradientFrame::qssText2Gradient(const QString &text)
{
    QString flag("qconicalgradient");
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

    qreal points[3] = {0};
    auto valueText = content.mid(douHaoIndex,stopIndex-douHaoIndex).trimmed();
    auto valueList = valueText.split(douHao,Qt::SkipEmptyParts);
    for (int i = 0; i < valueList.size(); i++)
    {
        auto text = valueList[i];
        text = text.trimmed();
        auto name = text.section(':',0,0);
        auto value = text.section(':',1,1);
        auto v = value.toDouble();
        if(name == "cx") points[0] = v;
        if(name == "cy") points[1] = v;
        if(name == "angle") points[2] = v;
    }

    setPoint(points[0],points[1],points[2]);

    return true;
}

void ConicalGradientFrame::on_doubleSpinBox_angle_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    this->genStyle();
}

