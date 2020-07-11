#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QFileSystemModel>


#include "custom/foldertreeview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString curFile;
    QFileSystemModel *modelOfFolder;
    void loadFolderTreeView(FolderTreeView* folderTreeView,const QString& rootPath);
    FolderTreeView* folderTreeView;
    QTabWidget* tabWidget;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    void openFolder();
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
