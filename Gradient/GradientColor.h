#ifndef GRADIENTCOLOR_H
#define GRADIENTCOLOR_H
#include <QString>
#include <QPair>
#include <QList>
#include <QGradient>

typedef QPair<qreal,QString> StepPair;
typedef QList<QPair<qreal,QString>> ColorAtList;
class GradientColor
{
public:
    GradientColor();
    static QStringList GetColorItemList();

    static StepPair GenStepPair(qreal step,const QString &color);

    static QString GetPreadText(QGradient::Spread pread);
    static QString GetColorAtText(ColorAtList colorAtlist);

    static QString LinearGradient(ColorAtList colorAtlist,QPointF start,QPointF finalStop,QGradient::Spread pread = QGradient::PadSpread);
    static QString LinearGradient(ColorAtList colorAtlist, qreal x1, qreal y1, qreal x2, qreal y2, QGradient::Spread pread = QGradient::PadSpread);

    static QString ConicalGradient(ColorAtList colorAtlist,qreal cx = 0,qreal cy = 0,qreal angle = 0,QGradient::Spread pread = QGradient::PadSpread);
    static QString ConicalGradient(ColorAtList colorAtlist,QPointF center = QPoint(0,0),qreal angle = 0,QGradient::Spread pread = QGradient::PadSpread);

    static QString RadialGradient(ColorAtList colorAtlist,qreal cx, qreal cy, qreal centerRadius, qreal fx, qreal fy, qreal focalRadius,QGradient::Spread pread = QGradient::PadSpread);
    static QString RadialGradient(ColorAtList colorAtlist,const QPointF &center, qreal centerRadius, const QPointF &focalPoint, qreal focalRadius,QGradient::Spread pread = QGradient::PadSpread);
};

#endif // GRADIENTCOLOR_H
