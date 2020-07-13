#ifndef EDITMD_H
#define EDITMD_H

#include <QWidget>
#include <QStackedWidget>
#include "bean/document.h"
#include <QWebEngineView>
#include <QPlainTextEdit>
#include <QString>

class EditMd : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget * m_stackWidget;
    //展示
    QWebEngineView * showWidget;
    //编辑
    QPlainTextEdit * editWidget;
    Document m_content;
    QString m_filePath;
    void initCtrls(QWidget *parent);
public:
    explicit EditMd(QWidget *parent = nullptr);
    bool eventFilter(QObject * obj, QEvent * e);
    void onFileSave();
    void onFileSaveAs();
    void openFile(const QString& _filePath);
signals:

};

#endif // EDITMD_H
