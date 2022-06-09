#include "RadialGradientFrame.h"
#include "qdebug.h"
#include "ui_RadialGradientFrame.h"
#pragma execution_character_set("utf-8")

RadialGradientFrame::RadialGradientFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RadialGradientFrame)
{
    ui->setupUi(this);

    ui->frame_center->setTitle(tr("中心点"));
    ui->frame_focalPoint->setTitle(tr("焦点"));

    connect(ui->frame_center,&PointItemFrame::changedSig,
            this,[this]{this->genStyle();});
    connect(ui->frame_focalPoint,&PointItemFrame::changedSig,
            this,[this]{this->genStyle();});
    connect(ui->frame_spread,&SpreadFrame::changedSig,
            this,[this]{this->genStyle();});
}

RadialGradientFrame::~RadialGradientFrame()
{
    delete ui;
}

void RadialGradientFrame::setPoint(qreal cx, qreal cy, qreal cradius, qreal fx, qreal fy, qreal fradius)
{
    ui->frame_center->setPoint(QPointF(cx,cy));

    ui->doubleSpinBox_centerRadius->blockSignals(true);
    ui->doubleSpinBox_centerRadius->setValue(cradius);
    ui->doubleSpinBox_centerRadius->blockSignals(false);

    ui->frame_focalPoint->setPoint(QPointF(fx,fy));

    ui->doubleSpinBox_focalRadius->blockSignals(true);
    ui->doubleSpinBox_focalRadius->setValue(fradius);
    ui->doubleSpinBox_focalRadius->blockSignals(false);

    genStyle();
}


void RadialGradientFrame::genStyle()
{
    if(mContentFrame)
    {
        auto list = mContentFrame->getColorAtList();
        auto spread = ui->frame_spread->getSpread();
        auto result = GradientColor::RadialGradient(list,ui->frame_center->getPoint(),
                                                    ui->doubleSpinBox_centerRadius->value(),
                                                    ui->frame_focalPoint->getPoint(),
                                                    ui->doubleSpinBox_focalRadius->value(),spread);
        mResultFrame->setResult(result,0);
    }
}


void RadialGradientFrame::save(QSettings *settings)
{
    settings->beginGroup("RadialGradientFrame");
    settings->setValue("spread",ui->frame_spread->getCurSpreadText());
    settings->setValue("center",ui->frame_center->getPoint());
    settings->setValue("centerRadius",ui->doubleSpinBox_centerRadius->value());
    settings->setValue("focalPoint",ui->frame_focalPoint->getPoint());
    settings->setValue("focalRadius",ui->doubleSpinBox_focalRadius->value());
    settings->endGroup();
}

void RadialGradientFrame::load(QSettings *settings)
{
    settings->beginGroup("RadialGradientFrame");
    auto spread = settings->value("spread",ui->frame_spread->getCurSpreadText()).value<QString>();
    auto center = settings->value("center",ui->frame_center->getPoint()).value<QPointF>();
    auto centerRadius = settings->value("centerRadius",ui->doubleSpinBox_centerRadius->value()).value<qreal>();
    auto focalPoint = settings->value("focalPoint",ui->frame_focalPoint->getPoint()).value<QPointF>();
    auto focalRadius = settings->value("focalRadius",ui->doubleSpinBox_focalRadius->value()).value<qreal>();
    settings->endGroup();

    ui->frame_spread->setCurSpreadText(spread);
    ui->frame_center->setPoint(center);
    ui->doubleSpinBox_centerRadius->setValue(centerRadius);
    ui->frame_focalPoint->setPoint(focalPoint);
    ui->doubleSpinBox_focalRadius->setValue(focalRadius);
}


SpreadFrame *RadialGradientFrame::getSpreadFrame()
{
    return ui->frame_spread;
}


void RadialGradientFrame::genCode(const QString &objName, bool isPointer)
{
    auto name = objName.isEmpty()? QString("gradient") : objName;
    auto pointerText = isPointer? QString("->") : QString(".");

    QStringList codeList;
    if(isPointer)
    {
        codeList << QString("auto %1 = new QRadialGradient();").arg(name);
    }else
    {
        codeList << QString("QRadialGradient %1;").arg(name);
    }

    codeList << QString("%1%2setSpread(%3);").arg(name,pointerText,ui->frame_spread->getSpreadCode());

    auto center = ui->frame_center->getPoint();
    codeList << QString("%1%2setCenter(%3,%4);").arg(name,pointerText).arg(center.x()).arg(center.y());

    auto centerRadius = ui->doubleSpinBox_centerRadius->value();
    codeList << QString("%1%2setCenterRadius(%3);").arg(name,pointerText).arg(centerRadius);

    auto focalPoint = ui->frame_focalPoint->getPoint();
    codeList << QString("%1%2setFocalPointr(%3,%4);").arg(name,pointerText).arg(focalPoint.x()).arg(focalPoint.y());

    auto focalRadius = ui->doubleSpinBox_focalRadius->value();
    codeList << QString("%1%2setFocalRadius(%3);").arg(name,pointerText).arg(focalRadius);

    auto list = getColorAtCodeList(name,pointerText);
    codeList.append(list);

    mResultFrame->setResult(codeList.join("\n"),1);
}


bool RadialGradientFrame::qssText2Gradient(const QString &text)
{
    QString flag("qradialgradient");
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

    qreal points[6] = {0};
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
        if(name == "radius") points[2] = v;
        if(name == "fx") points[3] = v;
        if(name == "fy") points[4] = v;
        if(name == "fradius") points[5] = v;
    }

    setPoint(points[0],points[1],points[2],points[3],points[4],points[5]);

    return true;
}

void RadialGradientFrame::on_doubleSpinBox_centerRadius_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    this->genStyle();
}


void RadialGradientFrame::on_doubleSpinBox_focalRadius_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    this->genStyle();
}

