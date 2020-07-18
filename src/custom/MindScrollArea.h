#ifndef MINDSCROLLAREA_H
#define MINDSCROLLAREA_H

#include <QScrollArea>
#include "MindNodeWidget.h"
class MindScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    MindNodeWidget * root;

    explicit MindScrollArea(QWidget *parent = nullptr);

    void defaultSetting();

signals:

public slots:
};
#endif // MINDSCROLLAREA_H
