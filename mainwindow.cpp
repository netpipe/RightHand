#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qfile.h>
#include <QTextStream>
#include <QFileDialog>
#include <QDirIterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_Load();
    on_import_2_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Convert input string to list of tokens
// Each token is either a word (sequence of letters)
// or a non-word (numeric, symbol, etc)
QStringList tokenizeInput(QString input) {
    QStringList tokenList;
    QString currentToken;
    for(int i = 0; i < input.length(); i++) {
        if (input[i].isLetter()){
            // keep accumulating letters that form a word
            currentToken += input[i];
        } else {
            // if there is an accumulated word, flush to the list
            if (currentToken.length() != 0) {
                tokenList.append(currentToken);
                currentToken.clear();
            }
            // add the non-word token into token list (e.g. space/symbol/digit)
            tokenList.append(QString(input[i]));
        }
    }
    // the input can end with a letter, flush if there is an accumulated word
    if (currentToken.length() != 0) {
        tokenList.append(currentToken);
    }
    // return produced token list
    return tokenList;
}

void MainWindow::on_translatebtn_clicked()
{
    // Grab the input string to translate/substitute
    QString input = ui->input->toPlainText().toLatin1();

    // Build rule map
    QMap<QString, QString> ruleMap;
    int ruleCount = ui->sublist->count();
    qDebug() << ruleCount;
    for (int i = 0; i < ruleCount; i++) {
        // A wild item has appeared
        QString ruleStr = ui->sublist->item(i)->text();
        QStringList ruleTokens = ruleStr.split(",");
        ruleMap.insert(ruleTokens.at(0), ruleTokens.at(1));
        ruleMap.insert(ruleTokens.at(1), ruleTokens.at(0));
    }

    // Convert input to list of tokens (words and non-words)
    QStringList inputTokens = tokenizeInput(input);

    // Produce output using list of input tokens and rule map
    QString output;
    for (int i=0; i < inputTokens.length(); i++){
        QString inputToken = inputTokens.at(i);
        if (ruleMap.contains(inputToken)) {
            output.append(ruleMap[inputToken]);
        } else {
            if (inputToken.length() > 2){
                output.append("un"+inputToken);}else{ output.append(inputToken);}
        }
    }


    if (ui->reversed->isChecked()){
   //     std::reverse(output.begin(), output.end());
    };

    // Update UI with produced output
    ui->translated->setText(output.toLatin1());




}

void MainWindow::on_sublist_itemSelectionChanged()
{


QString test = ui->sublist->currentItem()->text();
QStringList test2 = test.split(",");
ui->in1->setText(test2.at(0));
ui->in2->setText(test2.at(1));

//todo still needs to save and add new row


}

void MainWindow::on_import_2_clicked()
{
//do this on startup to import any settings

    QFile file(ui->loadlistcmb->currentText());
   //     QFile file("sublist.txt");
if (file.exists()){
 ui->sublist->clear();
    QStringList stringList;
  //  QFile textFile;

    file.open(QIODevice::ReadWrite | QFile::Text);

    QTextStream textStream(&file);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            stringList.append(line);

         QStringList test2 = line.split(",");
         qDebug() << test2.at(0) << test2.at(1);
     //    ui->in1->setText(test2.at(0));// << "," << test2.at(1)
     //    ui->in1->setText(test2.at(1));//
QString itemtxt = test2.at(0).toLatin1();
        itemtxt += ",";
        itemtxt += test2.at(1).toLatin1();
         ui->sublist->addItem(itemtxt.toLatin1());
    }

       file.close();
}


}

void MainWindow::on_editbtn_clicked()
{
    //if empty in1 and 2 then make new or unselected sublist
   if ((ui->in1->text().toLatin1()=="") && (ui->in2->text().toLatin1()=="")){

        ui->sublist->insertItem((ui->sublist->count()+1),"new1,new1");
   }else{
       QString test = ui->sublist->currentItem()->text();
       QStringList test2 = test.split(",");

       if ((test2.at(0).toLatin1()=="new1") && (test2.at(1).toLatin1()=="new1")){
           QString itemtxt = ui->in1->text().toLatin1();
                   itemtxt += ",";
                   itemtxt += ui->in2->text().toLatin1();

                   ui->sublist->currentItem()->setText(itemtxt.toLatin1());
       }else{
           QString itemtxt = ui->in1->text().toLatin1();
                   itemtxt += ",";
                   itemtxt += ui->in2->text().toLatin1();

                   ui->sublist->currentItem()->setText(itemtxt.toLatin1());
       }
   }
on_export_2_clicked();
}

void MainWindow::on_export_2_clicked()
{

QString Filename = QFileDialog::getSaveFileName(this, "Save File",".txt",".txt");
    QFile file(Filename);
    file.open(QIODevice::ReadWrite | QFile::Text);



    QStringList exported;

    int listcount = ui->sublist->count();
    qDebug() << listcount;
    for (int i=0;i < listcount;i++){
         QTextStream out(&file);

        QString test =  ui->sublist->item(i)->text(); //ui->sublist->currentItem()->text();
        QStringList test2 = test.split(",");
//        //  exported << test2.at(0) << test2.at(1);
        out << test2.at(0).toLatin1() << "," << test2.at(1).toLatin1() << endl;
      //  qDebug() << "testing2";
    //     qDebug() << test2.at(0).toLatin1();

    }

       file.close();

//dump exported to file
       on_Load();

}


void MainWindow::on_Load()
{

    QDirIterator it("./", QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
      //  QFileInfo fileInfo(f.fileName());
        ui->loadlistcmb->addItem(it.next().toLatin1());
    }

    if (ui->loadlistcmb->currentText() == "default"){
        qDebug() << "testing";
    }

}




void MainWindow::on_comboBox_activated(const QString &arg1)
{

}
