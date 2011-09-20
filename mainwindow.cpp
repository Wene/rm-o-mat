#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDate>
#include <QSettings>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadSettings();
    ui->editLine->setFocus();
}

void MainWindow::ReadSettings()
{
    QSettings settings("marvo","RM-o-Mat");
    settings.beginGroup("MainWindow");
    QSize windowSize = settings.value("size", QSize(350,65)).toSize();
    resize(windowSize);
    QPoint windowPosition = settings.value("position", QPoint(20,20)).toPoint();
    if (windowPosition.x() + windowSize.width()
        > QApplication::desktop()->screenGeometry().width())
    {
        windowPosition.setX(QApplication::desktop()->screenGeometry().width()
                            - (windowSize.width() + 20));
    }
    if (windowPosition.x() <= 0)
    {
        windowPosition.setX(5);
    }
    if (windowPosition.y() + windowSize.height()
        > QApplication::desktop()->screenGeometry().height())
    {
        windowPosition.setY(QApplication::desktop()->screenGeometry().height()
                            - (windowSize.height() + 20));
    }
    if (windowPosition.y() <= 0)
    {
        windowPosition.setY(5);
    }
    move(windowPosition);
    settings.endGroup();
    settings.beginGroup("Content");
    ui->editName->setText(settings.value("Name","").toString());
    settings.endGroup();
}

void MainWindow::WriteSettings()
{
    QSettings settings("marvo", "RM-o-Mat");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("position", pos());
    settings.endGroup();
    settings.beginGroup("Content");
    settings.setValue("Name", ui->editName->text());
    settings.endGroup();
}

MainWindow::~MainWindow()
{
    WriteSettings();
    delete ui;
}

void MainWindow::on_btnRM_clicked()
{
    QClipboard *myClip = QApplication::clipboard();
    QString myRM;
    QDate myDate = QDate::currentDate();
    myRM = myDate.toString("dd.MM.yy") + " RM "+ ui->editName->text() +
           " \"" + ui->editLine->text() + '"';

    myClip->setText(myRM);
    ui->statusBar->showMessage(myRM);
    ui->editLine->setFocus();
    ui->editLine->selectAll();
}

void MainWindow::on_editName_returnPressed()
{
    ui->editLine->setFocus();
}
