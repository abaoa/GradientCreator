#include "GradientFrameBase.h"

GradientFrameBase::GradientFrameBase()
{
    mContentFrame = nullptr;
    mResultFrame = nullptr;
}

GradientColorContentFrame *GradientFrameBase::contentFrame() const
{
    return mContentFrame;
}

void GradientFrameBase::setContentFrame(GradientColorContentFrame *newContentFrame)
{
    mContentFrame = newContentFrame;
}

ResultFrame *GradientFrameBase::getResultFrame() const
{
    return mResultFrame;
}

void GradientFrameBase::setResultFrame(ResultFrame *newResultFrame)
{
    mResultFrame = newResultFrame;
}

QStringList GradientFrameBase::getColorAtCodeList(const QString &objName, const QString &pointerText)
{
    QStringList result;
    if(mContentFrame)
    {
        auto list = mContentFrame->getColorAtList();
        for (int i = 0; i < list.size(); i++)
        {
            auto pair = list.at(i);
            auto step = QString::number(pair.first);
            auto color = QString("\"%1\"").arg(pair.second);
            result << QString("%1%2setColorAt(%3,%4);").arg(objName,pointerText,step,color);
        }
    }
    return result;
}
