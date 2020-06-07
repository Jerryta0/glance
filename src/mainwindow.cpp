#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inlib.h"
#include "common/systemConsts.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textEdit(new QPlainTextEdit)
{
    ui->setupUi(this);

    setCentralWidget(textEdit);

//    createActions();
//    createStatusBar();
//    readSettings();


    InLib inLib;
    inLib.testLib();
}




MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, appName,
                             QString("Cannot read file %1:\n%2.")
                             //把windows下的路径转换为Qt可以识别的路径
                             //如"C:/Users/Administrator/Desktop"------->"C:\Users\Administrator\Desktop"
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    //读取文件
    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::setCurrentFile(const QString &fileName)
//! [46] //! [47]
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
