#include "MdPlainTextEdit.h"
#include <QShortcut>
#include <QDebug>
MdPlainTextEdit::MdPlainTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    //不能给其他用
    m_stackWidget = (QStackedWidget*)parent;
}
void MdPlainTextEdit::mouseDoubleClickEvent(QMouseEvent *event){

    //双击切换
    if(event->button() == Qt::LeftButton){
        m_stackWidget->setCurrentIndex(0);
     }

}
