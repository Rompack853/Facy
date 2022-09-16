#include "controller.h"

Controller::Controller()
{
 setup();
}

/**
 * @brief Controller::setup
 * Basic Setup of Connection and Data that is
 * crutial for the Controller to work
 */
void Controller::setup(){
    qDebug()<<"Database found & Connected: "<<database.connect();
}
