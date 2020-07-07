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

void callOutFunction()
{
    InLib inLib;
    inLib.testLib();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(widthOfMianWin,heightOfMianWin);

    QString rootPath = defaultRootPath;
    folderTreeView = new FolderTreeView(this);
    folderTreeView->setGeometry(10,80,300,600);
    loadFolderTreeView(folderTreeView,rootPath);

    createActions();
//    createStatusBar();
//    readSettings();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createActions()
{
    //menuBar() 系统默认给的Bar,删除会报错
    QMenuBar * bar = this->menuBar();
    QToolBar *mainToolBar = this->ui->mainToolBar;

    //___打开文件QAction___
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

    //___退出QAction___
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("Exit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("Exit the application");
    fileMenu->addAction(exitAct);

}

//打开文件夹
void MainWindow::openFolder()
{
    //QFileDialog提供了一个对话框，允许用户选择文件或者目录，
    QUrl folderUrl = QFileDialog::getExistingDirectoryUrl(this);
    //如果没有打开文件 返回""
    //"C:/Users/DELL/Documents"
    qDebug()<<" folderUrl.toLocalFile() "<<folderUrl.toLocalFile();
    loadFolderTreeView(folderTreeView,folderUrl.toLocalFile());
}


void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, appName,
                             QString("Cannot read file %1:\n%2.")
                             //toNativeSeparators
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
    //路径
    //QString windowFilePath() const
    //void setWindowFilePath(const QString &filePath)
    //该属性保存了widget的文件路径。
    //这个属性只与window有关，它将文件路径和window关联起来。
    //如果设置了文件路径但是没有设置window的名字，Qt将窗口标题设置为指定的路径文件名，可以调用QFileInfo::fileName()函数来获取。
}
void MainWindow::loadFolderTreeView(FolderTreeView* folderTreeView,const QString& rootPath)
{
    model = new QFileSystemModel(this);

    model->setRootPath(rootPath);
    //文件系统的默认icon
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    //model类型:QAbstractItemModel
    folderTreeView->setModel(model);
    if (!rootPath.isEmpty()) {
        // QDir::cleanPath 删除多余空格
        const QModelIndex rootIndex = model->index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            //整条链中,告诉tree去那个index查看数据
            folderTreeView->setRootIndex(rootIndex);
    }
    //隐藏可以,   如果使用删除 model->removeColumn(1) ,会失败
    folderTreeView->setColumnHidden(1, true);
    folderTreeView->setColumnHidden(2, true);
    folderTreeView->setColumnHidden(3, true);
    //一共4列, model->columnCount() == 4 ,目前只要第一列
    folderTreeView->setHeaderHidden(true);
}
