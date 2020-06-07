#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inlib.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InLib inLib;
    inLib.testLib();
}

MainWindow::~MainWindow()
{
    delete ui;
}
