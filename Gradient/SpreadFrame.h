#ifndef SPREADFRAME_H
#define SPREADFRAME_H

#include <QFrame>
#include <QGradient>

namespace Ui {
class SpreadFrame;
}

class SpreadFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SpreadFrame(QWidget *parent = nullptr);
    ~SpreadFrame();

    QGradient::Spread getSpread();
    QString getSpreadCode();

    QString getCurSpreadText();
    void setCurSpreadText(const QString &text);

    void setQssText(const QString &text);
signals:
    void changedSig();
private slots:
    void on_comboBox_spread_activated(int index);

private:
    Ui::SpreadFrame *ui;
};

#endif // SPREADFRAME_H
