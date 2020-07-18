#ifndef EDITMD_H
#define EDITMD_H
#include "MdPlainTextEdit.h"
#include <QWidget>
#include <QStackedWidget>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QString>

/**
* @author taojiayu
* @date 2020-07-19
* @desc md文件的切换控件
*/
class MdStackedEditor : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget * m_stackWidget;
    //编辑
    QPlainTextEdit * editWidget;
    //当前的展示
    QTextEdit * showWidget;
    //类型
    int type;

    QString m_content;
    QString m_filePath;
    void init();
    void initMenu();
    void initCtrls(QWidget *parent);
public:
    explicit MdStackedEditor(QWidget *parent = nullptr);
    void onFileSave();
    void onFileSaveAs();
    void openFile(const QString& _filePath);

//    bool eventFilter(QObject * obj, QEvent * e);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:

};

#endif // EDITMD_H
