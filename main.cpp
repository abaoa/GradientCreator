#include <QApplication>
#include "GradientColorFrame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GradientColorFrame f;
    f.showMaximized();
    return a.exec();
}
