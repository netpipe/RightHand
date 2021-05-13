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
            output.append(inputToken);
        }
    }

    // Update UI with produced output
    ui->translated->setText(output.toLatin1());
}

void MainWindow::on_sublist_itemSelectionChanged()
{

}
