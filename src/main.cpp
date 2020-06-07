#include <QApplication>
#include <QCommandLineParser>

#include "mainwindow.h"
#include "common/systemConsts.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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
    if (!parser.positionalArguments().isEmpty())
        mainWin.loadFile(parser.positionalArguments().first());
    mainWin.show();
    return app.exec();
}
