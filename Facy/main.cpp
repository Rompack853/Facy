#include "frmmain.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //FrmMain w;
    //w.show();

    Controller controller;
    //===============TESTING=====================
    //---Test - Writing users to Database---
    //controller.addUser(Role::USER, "Fsociety", "Password123");
    //controller.addUser(Role::ADMIN, "ChuckNorris", "psswrd");

    //---Test - Loading Users from Database---
    //for(int i=0; i<3; i++){
        //controller.loadUser("ChuckNorris");
    //}//for 3 cycles

    //---Test - Writing groups to Databse---
    /*controller.addGroup("SportlerInnen",
                        "",
                        "Als Sportler oder Sportlerin wird "
                        "eine Person bezeichnet, die regelmäßig "
                        "und intensiv eine oder mehrere "
                        "Sportarten betreibt.");
    controller.addGroup("LehrerInnen",
                        "",
                        "Ein Lehrer oder eine Lehrerin ist eine Person, "
                        "die andere Personen auf einem Gebiet "
                        "weiterbildet, auf dem sie selber einen "
                        "Vorsprung an Können, Wissen oder Erfahrung hat. "
                        "Da es sich um keine geschützte Bezeichnung handelt, "
                        "kann sich grundsätzlich jede Person so nennen, "
                        "die sich in einer Phase der Vermittlung von Wissen, "
                        "Können, Lebensweisheit, Ausbildung oder Bildung befindet.");*/

    //---Test - Loading groups from Database---
    //TODO

    //---Test - Writing list of highscores to Database---
    //TODO

    //---Test - Loading list of highscores from Database---
    //TODO

    //---Test - Creating Directories in Filesystem---
    //Filesystem::getInstance()->createNewGroupDir("Testordner123");

    return a.exec();
}
