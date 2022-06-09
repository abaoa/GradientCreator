#ifndef RESULTFRAME_H
#define RESULTFRAME_H

#include <QFrame>
#include <QGradient>

namespace Ui {
class ResultFrame;
}

class ResultFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ResultFrame(QWidget *parent = nullptr);
    ~ResultFrame();

    void setResult(const QString &text,int type);
    QString getResult();
    void clear();

    QString getQssText(const QString &text);
signals:
    void resultActionSig(int action,const QVariantList &list);
    void genCodeSig(const QString &objName,bool isPointer);
private slots:
    void on_pushButton_apply_clicked();

    void on_pushButton_genStyle_clicked();
    void on_pushButton_genCode_clicked();

    void on_pushButton_copy_clicked();

    void on_comboBox_color_activated(int index);

    void resultSlot(const QString &text);

    void on_pushButton_split_clicked();

    void on_pushButton_collection_clicked();

private:
    Ui::ResultFrame *ui;
};

#endif // RESULTFRAME_H
