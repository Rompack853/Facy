#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);
}

FrmMain::~FrmMain()
{
    delete ui;
}


void FrmMain::on_btnConnect_clicked()
{
    if(ui->btnConnect->text() == "Start Server"){
        server = new Server(this, ui->lePort->text().toInt());
        ui->btnConnect->setText("Stop Server");
    } else {
        delete server;
        ui->btnConnect->setText("Start Server");
    }//else
}

