#ifndef CONICALGRADIENTFRAME_H
#define CONICALGRADIENTFRAME_H

#include <QFrame>
#include "GradientFrameBase.h"

namespace Ui {
class ConicalGradientFrame;
}

class ConicalGradientFrame : public QFrame,public GradientFrameBase
{
    Q_OBJECT

public:
    explicit ConicalGradientFrame(QWidget *parent = nullptr);
    ~ConicalGradientFrame();

    void setPoint(qreal x,qreal y,qreal angle);
private:
    Ui::ConicalGradientFrame *ui;

    // GradientFrameBase interface
public:
    virtual void genStyle() override;
private slots:
    void on_pushButton_1_clicked();

    // GradientFrameBase interface
    void on_doubleSpinBox_angle_valueChanged(double arg1);

public:
    virtual void save(QSettings *settings) override;
    virtual void load(QSettings *settings) override;
    virtual SpreadFrame *getSpreadFrame() override;
    virtual void genCode(const QString &objName, bool isPointer) override;
    virtual bool qssText2Gradient(const QString &text) override;
};

#endif // CONICALGRADIENTFRAME_H
