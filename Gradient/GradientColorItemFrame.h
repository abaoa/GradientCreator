#ifndef GRADIENTCOLORITEMFRAME_H
#define GRADIENTCOLORITEMFRAME_H

#include <QFrame>

namespace Ui {
class GradientColorItemFrame;
}

struct ColorItemData
{
    bool isUsed;
    qreal step;
    QString color;
    ColorItemData()
    {
        isUsed = true;
        step = 0.0;
        color = "#FFFFFF";
    }
};

class GradientColorItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GradientColorItemFrame(QWidget *parent = nullptr);
    ~GradientColorItemFrame();


    const ColorItemData &data();
    void setData(const ColorItemData &data);

signals:
    void actionSig(int type);
    void changedSig();
private slots:
    void on_pushButton_color_clicked();
    void on_lineEdit_color_textChanged(const QString &arg1);
    void on_pushButton_del_clicked();

    void on_pushButton_more_clicked(bool checked);

    void on_checkBox_isUsed_stateChanged(int arg1);

    void on_doubleSpinBox_step_valueChanged(double arg1);

private:
    Ui::GradientColorItemFrame *ui;
    ColorItemData mData;
};

#endif // GRADIENTCOLORITEMFRAME_H
