#include "MindGraphicsView.h"
#include "MindGraphicsTextItem.h"

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
}
