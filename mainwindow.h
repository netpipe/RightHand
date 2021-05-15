#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_translatebtn_clicked();

    void on_sublist_itemSelectionChanged();

    void on_import_2_clicked();

    void on_editbtn_clicked();

    void on_export_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_Load();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
