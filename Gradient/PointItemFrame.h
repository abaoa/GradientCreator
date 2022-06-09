#ifndef POINTITEMFRAME_H
#define POINTITEMFRAME_H

#include <QFrame>

namespace Ui {
class PointItemFrame;
}

class PointItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PointItemFrame(QWidget *parent = nullptr);
    ~PointItemFrame();

    void setTitle(const QString &text);
    void setPoint(QPointF point);
    QPointF getPoint();
signals:
    void changedSig();
private slots:
    void on_doubleSpinBox_x_valueChanged(double arg1);

    void on_doubleSpinBox_y_valueChanged(double arg1);

private:
    Ui::PointItemFrame *ui;
};

#endif // POINTITEMFRAME_H
