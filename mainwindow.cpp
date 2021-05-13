#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

    int count = ui->sublist->count();
    qDebug() << count;
    for(int index = 0;
        index < count;
        index++)
    {
      //  QListWidgetItem * item = ui->sublist->item(index);
        // A wild item has appeared
        QString str = ui->sublist->item(index)->text();
qDebug() << str;
        //QString str2 = str.split(",").first();
        QStringList strlist = str.split(",");

        tbuff2 = strlist.at(0).toLatin1();
        tbuff3 = strlist.at(1).toLatin1();

        //tbuff.replace(tbuff2.toLatin1(),tbuff3.toLatin1());
        tbuff.replace(tbuff2.toLatin1(),"tstemp");
        tbuff.replace(tbuff3.toLatin1(),tbuff2.toLatin1());
        tbuff.replace("tstemp",tbuff3.toLatin1());
qDebug() << tbuff2.toLatin1() << tbuff3.toLatin1();



        //do both tbuff2 and tbuff3 on new or non changed words / name them with a number then swap them back after.
    //also add the . and comma's from the searched words to replace
    }

        ui->translated->setText(tbuff.toLatin1());


}

void MainWindow::on_sublist_itemSelectionChanged()
{

}
