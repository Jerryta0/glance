#ifndef MDGRAPHICSTEXTITEM_H
#define MDGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

/**
* @author taojiayu
* @date 2020-07-19
* @desc mind的文字item
*/
class MindGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit MindGraphicsTextItem(QGraphicsItem *parent = nullptr);
    void adJustSize();

signals:

};

#endif // MDGRAPHICSTEXTITEM_H
