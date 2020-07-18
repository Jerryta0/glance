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
    void initTree();

    explicit MindGraphicsView(QWidget *parent = nullptr);
signals:

};

#endif // MDGRAPHICSVIEW_H
