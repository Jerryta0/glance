#include "MindGraphicsView.h"
#include "MindGraphicsTextItem.h"
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QDebug>


MindGraphicsView::MindGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    initTree();
}

void MindGraphicsView::initTree()
{
    QGraphicsTextItem *pItem = new MindGraphicsTextItem();
    pItem->setHtml("<hr/> \n <h1>111</h1> <hr/>");
    scene->addItem(pItem);
    QGraphicsTextItem *pItem2 = new MindGraphicsTextItem();
    pItem2->setHtml("12344444444444444");
    scene->addItem(pItem2);
    pItem2->setPos(-300,0);
}
void MindGraphicsView::scaleView(QWheelEvent *event)
{
    //不然会无限放大
    this->scale(1/m_scale, 1/m_scale);
    if(event->delta() > 0){
        if(m_scale < 10){
            //增量
            m_scale += 0.2;
        }else{
            //最大系数
            m_scale = 10;
        }
    }else{
        if(m_scale > 0.2){
            m_scale -= 0.2;
        }else{
            m_scale = 0.2;
        }
    }
    this->scale(m_scale, m_scale);
}

void MindGraphicsView::wheelEvent(QWheelEvent *event){

    // 获取当前的鼠标所在的view坐标;
    QPoint prev_viewPos = event->pos();
    // 获取当前鼠标相对于scene的位置;
    QPointF prev_scenePos = this->mapToScene(prev_viewPos);

    //进行缩放
    scaleView(event);

    //调整scene，使得scene和view一致，主要是为了排除掉scroll
    this->scene->setSceneRect(this->mapToScene(this->rect()).boundingRect());
    //获取缩放后的scene坐标
    QPointF scenePos = this->mapToScene(prev_viewPos);
    //获取缩放前后的坐标差值，即为需要进行move的位移
    QPointF disPointF = scenePos - prev_scenePos;
    //调整位置
    this->scene->setSceneRect(this->scene->sceneRect().x()-disPointF.x(),
                              this->scene->sceneRect().y()-disPointF.y(),
                              this->scene->sceneRect().width(),
                              this->scene->sceneRect().height());

    this->scene->update();
}
void MindGraphicsView::mousePressEvent(QMouseEvent *event){
    m_lastPointF = event->pos();
    qDebug()<<"m_lastPointFc : " << m_lastPointF;
}
void MindGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    //是否 按下ctrl
    if(event->modifiers() != Qt::ControlModifier){
        return;
    }
    QPointF disPointF = event->pos() - m_lastPointF;
    m_lastPointF = event->pos();
    //整个拖动都是在对view的scene进行操作的
    //每次调用scene的setSceneRect()动态的设置场景的范围，就是类似在一直在调整scene通过view显示的部分，
    //动态的显示整个scene的部分（scene是无限大）
    this->scene->setSceneRect(this->scene->sceneRect().x()+disPointF.x(),
                              this->scene->sceneRect().y()+disPointF.y(),
                              this->scene->sceneRect().width(),
                              this->scene->sceneRect().height());
    this->scene->update();
}
