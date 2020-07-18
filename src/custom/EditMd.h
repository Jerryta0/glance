#ifndef EDITMD_H
#define EDITMD_H

#include <QWidget>
#include <QStackedWidget>
#include "bean/document.h"
#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QString>

class EditMd : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget * m_stackWidget;
    //编辑
    QPlainTextEdit * editWidget;
    //当前的展示
    QWidget * currentShowWidget;
    //展示 showWidgetOfWeb
    QWebEngineView * showWidget;
    //不同的实现
    QTextEdit * showWidgetOfRich;
    //类型
    int type;

    Document m_content;
    QString m_filePath;

    void initCtrls(QWidget *parent);
public:
    explicit EditMd(QWidget *parent = nullptr);
    bool eventFilter(QObject * obj, QEvent * e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void onFileSave();
    void onFileSaveAs();
    void openFile(const QString& _filePath);
signals:

};

#endif // EDITMD_H
