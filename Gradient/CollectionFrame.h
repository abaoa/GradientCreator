#ifndef COLLECTIONFRAME_H
#define COLLECTIONFRAME_H

#include <QFrame>
#include "GradienBoxtItemFrame.h"
#include "flowlayout.h"
namespace Ui {
class CollectionFrame;
}

class CollectionFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CollectionFrame(QWidget *parent = nullptr);
    ~CollectionFrame();

    void add(const QString &name, const QString &gradientText);
    void toLayout();
    void clearLayout();

    void save();
    void load();
signals:
    void textSig(const QString &text);
private slots:
    void resultActionSlot(int action,const QVariantList &list);
private:
    Ui::CollectionFrame *ui;
    QList<GradienBoxtItemFrame*> mItemList;
    FlowLayout *mLayout;
};

#endif // COLLECTIONFRAME_H
