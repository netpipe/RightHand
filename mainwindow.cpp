#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translatebtn_clicked()
{
    QString tbuff = ui->input->toPlainText().toLatin1();

    QString tbuff2;
    QString tbuff3;


    tbuff2 += "test";
    tbuff3 += "nontest2";

    tbuff.replace(tbuff2.toLatin1(),tbuff3.toLatin1());
    ui->translated->setText(tbuff.toLatin1());



    //do both tbuff2 and tbuff3 on new or non changed words / name them with a number then swap them back after.
//also add the . and comma's from the searched words to replace
}

void MainWindow::on_sublist_itemSelectionChanged()
{

}
