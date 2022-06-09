#ifndef GRADIENBOXTITEMFRAME_H
#define GRADIENBOXTITEMFRAME_H

#include <QFrame>

namespace Ui {
class GradienBoxtItemFrame;
}

class GradienBoxtItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GradienBoxtItemFrame(QWidget *parent = nullptr);
    ~GradienBoxtItemFrame();

    QString name() const;
    void setName(const QString &newName);

    QString gradientText() const;
    void setGradientText(const QString &newGradientText);

signals:
    void resultActionSig(int action,const QVariantList &list);
private slots:
    void on_pushButton_clicked();
    void on_GradienBoxtItemFrame_customContextMenuRequested(const QPoint &pos);

    void on_action_del_triggered();
    void on_action_copy_triggered();
    void on_action_rename_triggered();

private:
    Ui::GradienBoxtItemFrame *ui;
};

#endif // GRADIENBOXTITEMFRAME_H
