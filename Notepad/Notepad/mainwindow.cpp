#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionSave_as_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}