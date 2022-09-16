#include "frmmain.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FrmMain w;
    //w.show();

    Controller controller;

    return a.exec();
}
