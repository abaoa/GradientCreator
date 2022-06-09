#ifndef LINEARGRADIENTFRAME_H
#define LINEARGRADIENTFRAME_H

#include <QFrame>
#include "GradientFrameBase.h"

namespace Ui {
class LinearGradientFrame;
}

class LinearGradientFrame : public QFrame,public GradientFrameBase
{
    Q_OBJECT

public:
    explicit LinearGradientFrame(QWidget *parent = nullptr);
    ~LinearGradientFrame();


    void setPoint(qreal x1,qreal y1,qreal x2,qreal y2);
private slots:

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::LinearGradientFrame *ui;

    // GradientFrameBase interface
public:
    virtual void genStyle() override;
    virtual void save(QSettings *settings) override;
    virtual void load(QSettings *settings) override;
    virtual SpreadFrame *getSpreadFrame() override;
    virtual void genCode(const QString &objName, bool isPointer) override;
    virtual bool qssText2Gradient(const QString &text) override;
};

#endif // LINEARGRADIENTFRAME_H
