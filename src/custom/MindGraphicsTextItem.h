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
    QString plainStr;
    QString htmlStr;
    //父节点 可以通过父节点找到所有兄弟
    MindGraphicsTextItem* parentNode;
    //子集合
    QList<MindGraphicsTextItem*> children;
    //属性
    int maxWidth;

    void adJustSize();

    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    explicit MindGraphicsTextItem(QGraphicsItem *parent = nullptr);
signals:
    void mySignal(QString);
};

// 实现双击进入编辑状态
// https://blog.csdn.net/Finull1/article/details/106403323
#endif // MDGRAPHICSTEXTITEM_H
