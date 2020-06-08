#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

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
    resize(600,800);
//    ui->retranslateUi(this);

    setCentralWidget(textEdit);

    createActions();
//    createStatusBar();
//    readSettings();


//    InLib inLib;
//    inLib.testLib();
}
void MainWindow::createActions()
{
    //menuBar() 系统默认给的Bar
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *mainToolBar = this->ui->mainToolBar;

    const QIcon openFolderIcon = QIcon::fromTheme("document-open", QIcon(":/res/images/icon_open_folder.png"));
    QAction *openFolderAction = new QAction(openFolderIcon, tr("Open Folder..."), this);
    // QKeySequence类中定义了一套跨平台的快捷键列表。
    //QKeySequence::New在window平台的大多数软件等同于Ctrl+N
    openFolderAction->setShortcuts(QKeySequence::Open);
    openFolderAction->setStatusTip(tr("Open an existing folder"));
    connect(openFolderAction, &QAction::triggered, this, &MainWindow::openFolder);
    fileMenu->addAction(openFolderAction);
    mainToolBar->addAction(openFolderAction);

    fileMenu->addSeparator();
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("Exit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("Exit the application");
    fileMenu->addAction(exitAct);

}

void MainWindow::openFolder()
{
    //打开文件夹
    QUrl folderUrl = QFileDialog::getExistingDirectoryUrl(this);
    //file:///F:/gitWs/glance/make_bin/src/release
    //如果没有打开文件 返回""
    qDebug()<< folderUrl.toString();

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
