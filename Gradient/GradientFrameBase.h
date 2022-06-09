#ifndef GRADIENTFRAMEBASE_H
#define GRADIENTFRAMEBASE_H
#include "GradientColorContentFrame.h"
#include "ResultFrame.h"
#include "SpreadFrame.h"
#include <QSettings>

class GradientFrameBase
{
public:
    GradientFrameBase();
    GradientColorContentFrame *contentFrame() const;
    void setContentFrame(GradientColorContentFrame *newContentFrame);

    virtual void genStyle() = 0;
    virtual void save(QSettings *settings) = 0;
    virtual void load(QSettings *settings) = 0;
    virtual SpreadFrame *getSpreadFrame() = 0;
    virtual void genCode(const QString &objName, bool isPointer) = 0;
    virtual bool qssText2Gradient(const QString &text) = 0;

    ResultFrame *getResultFrame() const;
    void setResultFrame(ResultFrame *newResultFrame);

    QStringList getColorAtCodeList(const QString &objName,const QString &pointerText);
protected:
    GradientColorContentFrame *mContentFrame;
    ResultFrame *mResultFrame;
};

#endif // GRADIENTFRAMEBASE_H
