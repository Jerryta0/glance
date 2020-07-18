#include "MindNodeWidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
MindNodeWidget::MindNodeWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    //自适应
    layout->setSizeConstraint(QLayout::SetFixedSize);
    this->setLayout(layout);

        parentNode = new QWidget(this);

    //垂直布局才能居中
        QVBoxLayout * parentLayout = new QVBoxLayout(parentNode);
        parentNode->setLayout(parentLayout);
        parentLayout->addStretch();
        parentLayout->addWidget(new QPushButton("111111111111111111111",this));
        parentLayout->addStretch();


//    QGridLayout * parentLayout = new QGridLayout(parentNode);
//    parentNode->setLayout(parentLayout);
//    // QGridLayout 的弹簧与 QHBoxLayout 及 QVBoxLayout 有些不同。它是设定整一行和整一列的弹簧，而不是设定某个格子的弹簧。
//    parentLayout->addWidget(new QPushButton("111111111111111111111",this),1,1);
//    // 在第 0 列增加一个弹簧，比例为 1
//    parentLayout->setColumnStretch(0, 1);
//    // 在第 0 行增加一个弹簧，比例为 1
//    parentLayout->setRowStretch(0, 1);
//    // 在第 3 列增加一个弹簧，比例为 1
//    parentLayout->setColumnStretch(3, 1);
//    // 在第 3 行增加一个弹簧，比例为 1
//    parentLayout->setRowStretch(3, 1);

    sonWidget =new QWidget(this);
    sonLayout = new QVBoxLayout(sonWidget);
    sonWidget->setLayout(sonLayout);
    sonLayout->addWidget(new QTextEdit(sonWidget));
    sonLayout->addWidget(new QTextEdit(sonWidget));
    //会递归
//    sonLayout->addWidget(new MindNodeWidget(sonWidget));

    //布局添加widget
    layout->addWidget(parentNode);
    //    layout->addWidget(new QPushButton("111111111111111111111",this));
    layout->addWidget(sonWidget);
}
