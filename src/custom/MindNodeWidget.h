#ifndef MINDNODEWIDGET_H
#define MINDNODEWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>

/**
* @author taojiayu
* @date 2020-07-19
* @desc 使用布局的mind
*/
class MindNodeWidget : public QWidget
{
    Q_OBJECT
public:
    QWidget* parentNode;
    QWidget* sonWidget;
    QBoxLayout* sonLayout;
    //父节点内容
    //list 子节点内容
    explicit MindNodeWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MINDNODEWIDGET_H
