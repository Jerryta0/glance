#ifndef MDGRAPHICSTEXTITEM_H
#define MDGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>
#include <QFocusEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
/**
* @author taojiayu
* @date 2020-07-19
* @desc mind的文字item
*/
class MindGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    QString m_plain_str;
    QString m_html_str;
    explicit MindGraphicsTextItem(QGraphicsItem *parent = nullptr);
    void adJustSize();


        void focusInEvent(QFocusEvent *event) override{
            //注意右键菜单再次进入焦点时不保存原始文本
            if(event->reason() != Qt::PopupFocusReason){
                m_plain_str = toPlainText();//保存原始文本
            }
            QGraphicsTextItem::focusInEvent(event);
        }

        void focusOutEvent(QFocusEvent *event) override{
            if(event->reason() == Qt::MouseFocusReason && QApplication::mouseButtons()==Qt::RightButton){
                //右键点击其他地方失去焦点，定义为取消操作，恢复原始文本
                setPlainText(m_plain_str);
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

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override{
            //左键双击进入可编辑状态并打开焦点
            if(event->button() == Qt::LeftButton){
                setTextInteractionFlags(Qt::TextEditorInteraction);
                setFocus();
                QGraphicsTextItem::mouseDoubleClickEvent(event);
            }
        }

        void mousePressEvent(QGraphicsSceneMouseEvent *event)override{
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

        void keyPressEvent(QKeyEvent *event) override{
            if(event->key() == Qt::Key_Return||event->key() == Qt::Key_Enter)
            {
            //点击回车失去焦点，编辑完成，后续给FocusOutEvent处理
                clearFocus();
            }else{
                QGraphicsTextItem::keyPressEvent(event);
            }
        }
signals:
    void mySignal(QString);
};

// 实现双击进入编辑状态
// https://blog.csdn.net/Finull1/article/details/106403323
#endif // MDGRAPHICSTEXTITEM_H
