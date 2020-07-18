#ifndef MDGRAPHICSVIEW_H
#define MDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

/**
* @author taojiayu
* @date 2020-07-19
* @desc mind的画布
*/
class MindGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsScene * scene;
    //上一个点的位置
    QPointF m_lastPointF;
    //缩放大小
    qreal m_scale = 1;
    void initTree();
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void mouseDoubleClickEvent(QMouseEvent *event);
    explicit MindGraphicsView(QWidget *parent = nullptr);
    //缩放方法
    void scaleView(QWheelEvent *event);

signals:

};
// Graphics View基于笛卡尔坐标系。

// QGraphicsView的缩放和拖动，以及缩放围绕鼠标所在点进行缩放
// https://blog.csdn.net/xi__q/article/details/84289935
// 没试过 方法2: QGraphicsView 以定点为中心进行缩放
// https://www.jianshu.com/p/05f680cf1f88
#endif // MDGRAPHICSVIEW_H
