#include "GradientColor.h"

GradientColor::GradientColor()
{

}

QStringList GradientColor::GetColorItemList()
{
    QStringList list;
    list << "color";
    list << "background-color";
    list << "altemate-background-color";
    list << "border-color";
    list << "border-top-color";
    list << "border-right-color";
    list << "border-bottom-color";
    list << "border-left-color";
    list << "gridline-color";
    list << "outline-color";
    list << "selection-color";
    list << "selection-background-color";
    return list;
}

StepPair GradientColor::GenStepPair(qreal step, const QString &color)
{
    return qMakePair<qreal,QString>(step,color);
}

QString GradientColor::GetPreadText(QGradient::Spread pread)
{
    switch (pread) {
    case QGradient::PadSpread:
        return "spread:pad";
    case QGradient::ReflectSpread:
        return  "spread:reflect";
        break;
    case QGradient::RepeatSpread:
        return "spread:repeat";
        break;
    }
    return "";
}

QString GradientColor::GetColorAtText(ColorAtList colorAtlist)
{
    QStringList list;
    foreach (auto pair, colorAtlist) {
       list << QString("stop:%1 %2").arg(pair.first).arg(pair.second);
    }
    return list.join(", ");
}

QString GradientColor::LinearGradient(ColorAtList colorAtlist, QPointF start, QPointF finalStop, QGradient::Spread pread)
{
    return GradientColor::LinearGradient(colorAtlist,start.x(),start.y(),finalStop.x(),finalStop.y(),pread);
}

QString GradientColor::LinearGradient(ColorAtList colorAtlist, qreal x1, qreal y1, qreal x2, qreal y2, QGradient::Spread pread)
{
    if(colorAtlist.isEmpty()) return "";

    QString type = GradientColor::GetPreadText(pread);
    auto colorAtText = GradientColor::GetColorAtText(colorAtlist);
    auto posText = QString("x1:%1, y1:%2, x2:%3, y2:%4").arg(x1).arg(y1).arg(x2).arg(y2);
    return QString("qlineargradient(%1, %2, %3);").arg(type,posText,colorAtText);
}



QString GradientColor::ConicalGradient(ColorAtList colorAtlist, qreal cx, qreal cy, qreal angle, QGradient::Spread pread)
{
    if(colorAtlist.isEmpty()) return "";

    Q_UNUSED(pread)
    //没有？？？
//    QString type = GradientColor::GetPreadText(pread);
    auto colorAtText = GradientColor::GetColorAtText(colorAtlist);
    auto posText = QString("cx:%1, cy:%2, angle:%3").arg(cx).arg(cy).arg(angle);
    return QString("qconicalgradient(%1, %2);").arg(posText,colorAtText);
}

QString GradientColor::ConicalGradient(ColorAtList colorAtlist, QPointF center, qreal angle, QGradient::Spread pread)
{
    return GradientColor::ConicalGradient(colorAtlist,center.x(),center.y(),angle,pread);
}

QString GradientColor::RadialGradient(ColorAtList colorAtlist, qreal cx, qreal cy, qreal centerRadius, qreal fx, qreal fy, qreal focalRadius, QGradient::Spread pread)
{
    if(colorAtlist.isEmpty()) return "";

    Q_UNUSED(focalRadius)
    //focalRadius ?没有
    auto type = GradientColor::GetPreadText(pread);
    auto colorAtText = GradientColor::GetColorAtText(colorAtlist);
    auto posText = QString("cx:%1, cy:%2, radius:%3, fx:%4, fy:%5").arg(cx).arg(cy).arg(centerRadius).arg(fx).arg(fy);
    return QString("qradialgradient(%1, %2, %3);").arg(type,posText,colorAtText);
}

QString GradientColor::RadialGradient(ColorAtList colorAtlist, const QPointF &center, qreal centerRadius, const QPointF &focalPoint, qreal focalRadius, QGradient::Spread pread)
{
    return GradientColor::RadialGradient(colorAtlist,center.x(),center.y(),centerRadius,focalPoint.x(),focalPoint.y(),focalRadius,pread);
}
