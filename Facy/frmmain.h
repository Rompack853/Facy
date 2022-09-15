#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FrmMain; }
QT_END_NAMESPACE

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private:
    Ui::FrmMain *ui;
};
#endif // FRMMAIN_H
