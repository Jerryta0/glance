#include "MindGraphicsTextItem.h"
#include <QAbstractTextDocumentLayout>
#include <QDebug>
MindGraphicsTextItem::MindGraphicsTextItem(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    //没用 没设置固定宽度的
    //this->document()->documentLayout()->documentSize().setWidth(100);

    // QGraphicsTextItem 没用textChanged
    connect(this->document(), &QTextDocument::modificationChanged,[=](){
        qDebug()<<this->document()->size().height();
        //需要保存
        this->document()->setModified(false);
    });

}
void MindGraphicsTextItem::adJustSize(){
    //获得文档的高度
    QTextDocument *doc= this->document();
    QAbstractTextDocumentLayout *layout = doc->documentLayout();
    int pixelsWidth = layout->documentSize().width();
    int pixelsHeight = layout->documentSize().height();


}

void MindGraphicsTextItem::focusInEvent(QFocusEvent *event) {
    //注意右键菜单再次进入焦点时不保存原始文本
    if(event->reason() != Qt::PopupFocusReason){
        //保存原始文本
        plainStr = toPlainText();
    }
    QGraphicsTextItem::focusInEvent(event);
}

void MindGraphicsTextItem::focusOutEvent(QFocusEvent *event) {
    if(event->reason() == Qt::MouseFocusReason && QApplication::mouseButtons()==Qt::RightButton){
        //右键点击其他地方失去焦点，定义为取消操作，恢复原始文本
        setPlainText(plainStr);
        //恢复不能编辑状态
        setTextInteractionFlags(Qt::NoTextInteraction);
    }
    //右键弹出菜单时不做处理
    else if(event->reason() == Qt::PopupFocusReason){

    }
    //其他情况，包括下面点击回车的情况，编辑成功，发送信号给父对象
    else{
        setTextInteractionFlags(Qt::NoTextInteraction);
        emit mySignal(toPlainText());
    }
    QGraphicsTextItem::focusOutEvent(event);
}

void MindGraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //左键双击进入可编辑状态并打开焦点
    if(event->button() == Qt::LeftButton){
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus();
        QGraphicsTextItem::mouseDoubleClickEvent(event);
    }
}

void MindGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        //左键点击是可编辑状态的话响应单击事件
        if(textInteractionFlags() != Qt::NoTextInteraction){
            QGraphicsTextItem::mousePressEvent(event);
        }
        //是不可编辑状态的话，也就是未双击进入编辑状态时不响应，一遍产生双击事件
    }else{
        //其他按键正常流程
        QGraphicsTextItem::mousePressEvent(event);
    }
}
//shift + enter 失去焦点
void MindGraphicsTextItem::keyPressEvent(QKeyEvent *event) {
    //    if (e->modifiers() == (Qt::ShiftModifier | Qt::ControlModifier) && e->key() == Qt::Key_A)
        if (event->modifiers() == (Qt::ShiftModifier) && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)){
            //回车失去焦点，编辑完成，后续给FocusOutEvent处理
            clearFocus();
        }else{
            QGraphicsTextItem::keyPressEvent(event);
        }

}
