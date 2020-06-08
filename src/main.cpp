#include <QApplication>
#include <QCommandLineParser>
#include <QTranslator>
#include <QDebug>

#include "mainwindow.h"
#include "common/systemConsts.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Linguist
    QTranslator translator;
//    QString filePath = QCoreApplication::applicationDirPath();
//    filePath+="/myI18N_zh_CN.qm";
    QString filePath = ":/myI18N_zh_CN.qm";
    bool translatorLoad = translator.load(filePath);
    if(translatorLoad){
        qDebug()<<"filePath:" << filePath;
        app.installTranslator(&translator);
    }else{
        qDebug()<<"translatorLoad:" << translatorLoad;
    }

    QCoreApplication::setOrganizationName(organizationName);
    QCoreApplication::setApplicationName(appName);
    //qt版本
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    //读取命令行
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow mainWin;
    mainWin.setWindowTitle(appName);
    if (!parser.positionalArguments().isEmpty())
        mainWin.loadFile(parser.positionalArguments().first());
    mainWin.show();
    return app.exec();
}
