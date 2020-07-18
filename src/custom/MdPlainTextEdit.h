#ifndef MDPLAINTEXTEDIT_H
#define MDPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QStackedWidget>
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
