#ifndef MDGRAPHICSVIEW_H
#define MDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
class MdGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MdGraphicsView(QWidget *parent = nullptr);

signals:

};

#endif // MDGRAPHICSVIEW_H
