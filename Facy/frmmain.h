#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FrmMain; }
QT_END_NAMESPACE

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::FrmMain *ui;

    Server* server;
};
#endif // FRMMAIN_H
