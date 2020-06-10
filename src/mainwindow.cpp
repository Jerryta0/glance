#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>


#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inlib.h"
#include "common/systemConsts.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(widthOfMianWin,heightOfMianWin);

    QString rootPath = defaultRootPath;
    //编程 要一步一步来
    //F:\gitWs\glance\src\mainwindow.cpp:48: error: expected type-specifier before 'FolderTreeView=               ^~~~~~~~~~~~~~
    // must use 'class' tag to refer to type  in this scope
    // https://www.cnblogs.com/Manual-Linux/p/11165861.html  error: must use ‘class’ tag to refer to type ‘XXX’ in this scope
    // https://blog.csdn.net/fjjaylz/article/details/88744885 关于C++中class关键字的一种特别使用情况
    folderTreeView = new class FolderTreeView(this);
    folderTreeView->setGeometry(10,80,300,600);
    loadFolderTreeView(folderTreeView,rootPath);

    createActions();
//    createStatusBar();
//    readSettings();


//    InLib inLib;
//    inLib.testLib();
}
void MainWindow::createActions()
{
    //menuBar() 系统默认给的Bar,删除会报错
    QMenuBar * bar = this->menuBar();
    QToolBar *mainToolBar = this->ui->mainToolBar;
    QMenu *fileMenu = bar->addMenu(tr("&File"));
    //从系统主题中获取图标，后者可以在主题中找不到图标时，再使用自己定义的图标
    const QIcon openFolderIcon = QIcon::fromTheme("document-open", QIcon(":res/images/icon_folder-open-outline.svg"));
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
    // folderUrl.url()  "file:///C:/Users/DELL/Documents"
    //folderUrl.toLocalFile()  "C:/Users/DELL/Documents"
    //如果没有打开文件 返回""
    qDebug()<<" folderUrl.url() "<< folderUrl.url();
    qDebug()<<" folderUrl.toLocalFile() "<<folderUrl.toLocalFile();
    loadFolderTreeView(folderTreeView,folderUrl.toLocalFile());
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
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
void MainWindow::loadFolderTreeView(FolderTreeView* folderTreeView,const QString& rootPath)
{
    model = new QFileSystemModel(this);

    model->setRootPath(rootPath);
    //文件系统的默认icon
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    //4列,删除失败
    qDebug()<<"model->columnCount()"<< model->columnCount();
    qDebug()<<"model->removeColumn(1)"<< model->removeColumn(1);

    //不需要show 一样展示
    folderTreeView->setModel(model);
    if (!rootPath.isEmpty()) {
        // QDir::cleanPath 删除多余空格
        //tree.setRootIndex(model.index(" ...")); 告诉tree去那个index查看数据
        //qt可能是去整条链加载
        const QModelIndex rootIndex = model->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            folderTreeView->setRootIndex(rootIndex);
    }
    //隐藏
    folderTreeView->setColumnHidden(1, true);
    folderTreeView->setColumnHidden(2, true);
    folderTreeView->setColumnHidden(3, true);
    folderTreeView->setHeaderHidden(true);
    folderTreeView->update();
}
