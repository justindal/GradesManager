#include <QApplication>
#include "GradeManagerGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GradeManagerGUI w;
    w.show();
    return QApplication::exec();
}
