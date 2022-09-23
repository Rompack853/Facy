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
    //Working!

    //---Test - Writing list of highscores to Database---
    //Adding a highscore With a User that doesn't exist
    //controller.addHighscore("LolloRosso", "SportlerInnen", 5);
    //qDebug() << "Test 1: finished";
    //Adding a highscore With a Group that doesn't exist
    //controller.addHighscore("Fsociety", "Nerds", 100);
    //qDebug() << "Test 2: finished";
    //Adding a highscore With a crazy score (below zero or of extreme size)
    //controller.addHighscore("Fsociety", "SportlerInnen", -4);
    //qDebug() << "Test 3: finished";
    //Overriding a highscore of the same group and a different User
    //controller.addHighscore("ChuckNorris", "SportlerInnen", 7);
    //qDebug() << "Test 4: finished";
    //---Test - Loading list of highscores from Database---
    //TODO,

    //---Test - Creating Directories in Filesystem---
    //Filesystem::getInstance()->createNewGroupDir("Testordner123");

    return a.exec();
}
