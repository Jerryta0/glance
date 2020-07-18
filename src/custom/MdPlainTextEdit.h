#ifndef MDPLAINTEXTEDIT_H
#define MDPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QStackedWidget>
/**
* @author taojiayu
* @date 2020-07-19
* @desc md的纯文本
*/
class MdPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    QStackedWidget * m_stackWidget;
    explicit MdPlainTextEdit(QWidget *parent = nullptr);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:

};

#endif // MDPLAINTEXTEDIT_H
