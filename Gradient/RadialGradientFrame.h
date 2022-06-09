#ifndef RADIALGRADIENTFRAME_H
#define RADIALGRADIENTFRAME_H

#include <QFrame>
#include "GradientFrameBase.h"

namespace Ui {
class RadialGradientFrame;
}

class RadialGradientFrame : public QFrame,public GradientFrameBase
{
    Q_OBJECT

public:
    explicit RadialGradientFrame(QWidget *parent = nullptr);
    ~RadialGradientFrame();

    void setPoint(qreal cx,qreal cy,qreal cradius,qreal fx,qreal fy,qreal fradius);
private:
    Ui::RadialGradientFrame *ui;

    // GradientFrameBase interface
public:
    virtual void genStyle() override;
    virtual void save(QSettings *settings) override;
    virtual void load(QSettings *settings) override;
    virtual SpreadFrame *getSpreadFrame() override;
    virtual void genCode(const QString &objName, bool isPointer) override;
    virtual bool qssText2Gradient(const QString &text) override;
private slots:
    void on_doubleSpinBox_centerRadius_valueChanged(double arg1);
    void on_doubleSpinBox_focalRadius_valueChanged(double arg1);
};

#endif // RADIALGRADIENTFRAME_H
