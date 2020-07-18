#ifndef EDITMD_H
#define EDITMD_H

#include <QWidget>
#include <QStackedWidget>
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
    QTextEdit * showWidget;
    //类型
    int type;

    QString m_content;
    QString m_filePath;

    void initCtrls(QWidget *parent);
public:
    explicit EditMd(QWidget *parent = nullptr);
    bool eventFilter(QObject * obj, QEvent * e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void onFileSave();
    void onFileSaveAs();
    void openFile(const QString& _filePath);
    void init();

    void initMenu();

signals:

};

#endif // EDITMD_H
