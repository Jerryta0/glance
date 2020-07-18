#ifndef MDGRAPHICSTEXTITEM_H
#define MDGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

class MdGraphicsTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit MdGraphicsTextItem(QGraphicsItem *parent = nullptr);
    void adJustSize();

signals:

};

#endif // MDGRAPHICSTEXTITEM_H
