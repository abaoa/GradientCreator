#ifndef GRADIENTCOLORCONTENTFRAME_H
#define GRADIENTCOLORCONTENTFRAME_H

#include <QFrame>
#include "GradientColor.h"
#include "GradientColorItemFrame.h"
#include "qsettings.h"
class QVBoxLayout;

namespace Ui {
class GradientColorContentFrame;
}

class GradientColorContentFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GradientColorContentFrame(QWidget *parent = nullptr);
    ~GradientColorContentFrame();

    void addItem();
    void addDefaultItem();
    void clear();

    QSettings *save();
    QSettings *load();

    ColorAtList getColorAtList();

    void initByText(const QString &text);
signals:
    void changedSig();
private slots:
    void actionSlot(int type);
private:
    void addItem(const ColorItemData &data);
    void toLayout();
    void clearLayout();
private:
    Ui::GradientColorContentFrame *ui;
    QList<GradientColorItemFrame*> mItemList;
    QVBoxLayout *mItemLayout;
};

#endif // GRADIENTCOLORCONTENTFRAME_H
