#include "frmmain.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FrmMain w;
    //w.show();

    Controller controller;
    //DELETE==========
    controller.addUser(Role::USER, "Fsociety", "Password123");
    controller.addUser(Role::ADMIN, "ChuckNorris", "psswrd");
    //DELETE=========
    return a.exec();
}
