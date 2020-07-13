#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>
#include <QModelIndex>
#include <QSplitter>



#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>
#include <QVariant>

#include <QJsonDocument>
#include <QJsonObject>

#include <QMessageBox>
#include <QDebug>

#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inlib.h"
#include "common/systemConsts.h"
#include "custom/texteditor.h"
#include "custom/editmd.h"
void callOutFunction();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(widthOfMianWin,heightOfMianWin);
    defaultQss();
    QString rootPath = defaultRootPath;
    //为什么留this->ui->centralWidget, 因为本来就是需要一个容器
    QHBoxLayout* layout = new QHBoxLayout(this->ui->centralWidget);
    this->centralWidget()->setLayout(layout);
    //新建主分割窗口，水平分割
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, this->ui->centralWidget);
    //左右, 拉伸边缘的时候,splitterMain会变大
    layout->addWidget(splitterMain);
    splitterMain->setGeometry(10,70,this->width(),this->height());

    //设置好parent,就不需要调价layout,再addwidget
    folderTreeView = new FolderTreeView(splitterMain);
    folderTreeView->setGeometry(0,0,this->width()/7,this->height());
    folderTreeView->setMaximumWidth(this->width()/7*2);

    loadFolderTreeView(folderTreeView,rootPath);

    createActions();
//    createStatusBar();
//    readSettings();

    //右分割窗口，并以主分割窗口作为父窗口
    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
    //在拖拽分割条时，是否实时更新
    splitterRight->setOpaqueResize(true);
    //控件是否可伸缩。第一个参数用于指定控件的序号。第二个函数大于0时，表示控件可伸缩，小于0时，表示控件不可伸缩。
    //拉伸的时候,拉伸1
    splitterRight->setStretchFactor(1,1);

    tabWidget = new QTabPageWidget(splitterRight);
    splitterRight->addWidget(tabWidget);

    tabWidget->setGeometry(QRect(10,0,this->width()/7*6,this->height()));

//    tabWidget->addTab(new QPushButton("btn1",this),"tab 1");
//    tabWidget->addTab(new QPushButton("btn2",this),"tab 2");

    //点击事件 void  clicked(const QModelIndex &index)
    connect(folderTreeView,&QTreeView::clicked,[=](const QModelIndex &index){
        qDebug()<<index.row()<<index.data()<<index.data().toString();

        //___遍历获得___
        QStringList filepath;
        QModelIndex cur = index;
        while(!cur.data().toString().isEmpty())
        {
            //获取itemfile名称
            filepath<<cur.data().toString();
            //将itemfile指向父item
            cur=cur.parent();
        }
        QString strpath;
        //QStringlist类filepath反向存着初始item的路径
        for(int i=(filepath.size()-1);i>=0;i--)
        { //将filepath反向输出，相应的加入’/‘
            strpath+=filepath.at(i);
            if(i!=0){
                strpath+="/";
            }
        }
//        qDebug()<<"strpath=="<<strpath;
    // https://blog.csdn.net/guofu8241260/article/details/22398773
        //___遍历获得___

        QString filePath =  modelOfFolder->filePath(index);
        QFile fileOfClick(filePath);
        QFileInfo fileInfoOfClick(filePath);
        if(fileInfoOfClick.isFile()){
           loadFile(filePath);
        }
    });



}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createActions()
{
    //menuBar() 系统默认给的Bar,删除会报错
    QMenuBar * bar = this->menuBar();
    QToolBar *mainToolBar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
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


void MainWindow::loadFile(const QString &filePath)
{
    //解析后缀
    //如果是txt
    QFileInfo fileInfo(filePath);
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, appName,
                             QString("Cannot read file %1:\n%2.")
                             //toNativeSeparators
                             //把windows下的路径转换为Qt可以识别的路径
                             //如"C:/Users/Administrator/Desktop"------->"C:\Users\Administrator\Desktop"
                             .arg(QDir::toNativeSeparators(filePath), file.errorString()));
        return;
    }
    //不区分大小写 ==0 表示相等
    if(fileInfo.suffix().compare("txt", Qt::CaseInsensitive) == 0){
        qDebug()<<"txt file";
        // QPlainTextEdit 不需要 setGeometry
        TextEditor* txt = new TextEditor(filePath,this);
        auto readData = file.readAll();
        qDebug()<<readData;
        txt->setPlainText(readData);
        tabWidget->addTabOnly(txt,fileInfo.fileName());
        connect(txt,&TextEditor::printMsg,[=](const QString& msg){
            statusBar()->showMessage(tr(msg.toUtf8().data()), timeoutOfPrint);
        });
    }

    //如果是.md
    if(fileInfo.suffix().compare(mdSuffix, Qt::CaseInsensitive) == 0){
        qDebug()<<"md file";
        file.close();
        EditMd* editMd = new EditMd(tabWidget);
        editMd->openFile(filePath);
        tabWidget->addTabOnly(editMd,fileInfo.fileName());
    }


    if(fileInfo.suffix().compare(gmindSuffix, Qt::CaseInsensitive) == 0){
        qDebug()<<"gmind file";
        //todo 读取文件
        QByteArray json = file. readAll();
        if(json.isEmpty()){
            //new jsonObj
        }
        QJsonParseError error;
        QJsonObject jsonObj;
        const QJsonDocument& jsDoc = QJsonDocument::fromJson(json,&error);
        if (QJsonParseError::NoError == error.error){
            if(jsDoc.isObject()){
                jsonObj = jsDoc.object();
            }
            // 在Java中，使用第三方库GSON就可以方便地实现对象和json之间的转换；而C++没有反射机制，所以没有类似的库。
            // Qt JSON解析生成笔记 https://www.cnblogs.com/buyishi/p/10306551.html

        }else{
            throw error.errorString();
        }
    }
    statusBar()->showMessage(tr("File loaded"), timeoutOfPrint);
}


void MainWindow::loadFolderTreeView(FolderTreeView* folderTreeView,const QString& rootPath)
{
    modelOfFolder = new QFileSystemModel(this);
    //图标
//    modelOfFolder->iconProvider()

    modelOfFolder->setRootPath(rootPath);
    //文件系统的默认icon
    modelOfFolder->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    //model类型:QAbstractItemModel
    folderTreeView->setModel(modelOfFolder);
    if (!rootPath.isEmpty()) {
        // QDir::cleanPath 删除多余空格
        const QModelIndex rootIndex = modelOfFolder->index(QDir::cleanPath(rootPath));
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
void MainWindow::defaultQss()
{
    QFile qssfile(":/res/style/dark-orange.qss");
    if(qssfile.open(QFile::ReadOnly)){
        QString qss = qssfile.readAll();
        this->setStyleSheet(qss);
    }else{
        qDebug()<<"style file open fail";
    }
    qssfile.close();
}

void callOutFunction()
{
    InLib inLib;
    inLib.testLib();
}
