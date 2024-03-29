#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void WriteSettings();
    void ReadSettings();

private slots:
    void on_editName_returnPressed();
    void on_btnRM_clicked();
};

#endif // MAINWINDOW_H
