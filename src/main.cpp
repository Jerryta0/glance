#include <QApplication>
#include <QCommandLineParser>
#include <QTranslator>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>
#include "MainWindow.h"
#include "common/systemConsts.h"

void translate(const QApplication& app)
{
    // 使用Linguist制作
    QTranslator translator;
    //需要把.qm文件放在exe同目录下
//    QString filePath = QCoreApplication::applicationDirPath();
//    filePath+="/myI18N_zh_CN.qm";
    QString filePath = ":/myI18N_zh_CN.qm";
    bool translatorLoad = translator.load(filePath);
    if(translatorLoad){
        qDebug()<<"load filePath : " << filePath;
        app.installTranslator(&translator);
    }else{
        qDebug()<<"load fail translatorLoad:" << translatorLoad;
    }
}

void setBasicInfo()
{
    QCoreApplication::setOrganizationName(organizationName);
    QCoreApplication::setApplicationName(appName);
    //qt版本
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
}

void readCommand(const QApplication& app,MainWindow& mainWin)
{
    //读取命令行
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    //可以 -help
    parser.addHelpOption();
    //可以 -version
    parser.addVersionOption();
    //添加一个参数
    parser.addPositionalArgument("file", "The file to open.");
    //把用户的命令行的放入解析实例 Process the actual command line arguments given by the user
    parser.process(app);
    if(parser.positionalArguments().isEmpty()){
        return;
    }
    if (!parser.positionalArguments().isEmpty()){
        //项目-run-命令行- 1.txt
        qDebug()<<parser.positionalArguments().first();
        mainWin.loadFile(parser.positionalArguments().first());
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //控件高清适配
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //解决 QPlainTextEdit 乱码问题
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);

    translate(app);
    setBasicInfo();
    MainWindow mainWin;
    mainWin.setWindowTitle(appName);
    readCommand(app,mainWin);
    mainWin.show();
    return app.exec();
}
