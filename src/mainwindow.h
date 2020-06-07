#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    //文本框
    QPlainTextEdit *textEdit;
    QString curFile;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
