#include "MindScrollArea.h"

MindScrollArea::MindScrollArea(QWidget *parent) : QScrollArea(parent)
{

    root = new MindNodeWidget(this);
    root->sonLayout->addWidget(new MindNodeWidget(this));
    root->sonLayout->addWidget(new MindNodeWidget(this));
    MindNodeWidget* tmp = new MindNodeWidget(this);
    tmp->sonLayout->addWidget(new MindNodeWidget(this));
    root->sonLayout->addWidget(tmp);
    //缩放必须要有
    this->setWidget(root);
}
