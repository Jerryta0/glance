#include "MdGraphicsView.h"
#include "MdGraphicsTextItem.h"

MdGraphicsView::MdGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene(this);
    this->setScene(scene);
    QGraphicsTextItem *pItem = new MdGraphicsTextItem();
    pItem->setHtml("<hr/> \n <h1>111</h1> <hr/>");


    scene->addItem(pItem);
}
