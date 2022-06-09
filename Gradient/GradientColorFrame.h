#ifndef GRADIENTCOLORFRAME_H
#define GRADIENTCOLORFRAME_H

#include <QFrame>
#include "GradientFrameBase.h"

namespace Ui {
class GradientColorFrame;
}

class GradientColorFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GradientColorFrame(QWidget *parent = nullptr);
    ~GradientColorFrame();

private slots:
    void on_pushButton_add_clicked();

    void resultActionSlot(int action,const QVariantList &list);
    void genCodeSlot(const QString &objName,bool isPointer);

    void on_pushButton_addDefault_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_load_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::GradientColorFrame *ui;
    QList<GradientFrameBase*> mFrameBaseList;
};

#endif // GRADIENTCOLORFRAME_H
