#ifndef MINDNODEWIDGET_H
#define MINDNODEWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
class MindNodeWidget : public QWidget
{
    Q_OBJECT
public:
    QPlainTextEdit* parentNode;
    QWidget* sonWidget;
    //父节点内容
    //list 子节点内容
    explicit MindNodeWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MINDNODEWIDGET_H
