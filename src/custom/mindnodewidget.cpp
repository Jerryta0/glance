#include "mindnodewidget.h"
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


    QWidget* parentWidget =new QWidget(this);
    parentNode =new QPlainTextEdit(parentWidget);
    // 纯文本
    parentNode->setPlainText("parentNode");
    QFont font = parentNode->font();
    // 像素大小
    font.setPixelSize(20);
    // 斜体
    font.setItalic(false);
    // 下划线
    font.setUnderline(false);
    parentNode->setFont(font);
    //已经产生了布局管理器了，大小就不可以改变了
    //可以用 QGridLayout ，网格布局管理器，这个你可以分配某个部件所占的格数，一般能达到你QTextEdit大小的问题

    //QTextEdit 适应内容调整大小

    //垂直布局才能居中
    //    QVBoxLayout * parentLayout = new QVBoxLayout(parentWidget);
    //    parentWidget->setLayout(parentLayout);
    //    parentLayout->addStretch();
    //    parentLayout->addWidget(parentNode);
    //    parentLayout->addStretch();

    QGridLayout * grid = new QGridLayout(parentWidget);
    parentWidget->setLayout(grid);
    // QGridLayout 的弹簧与 QHBoxLayout 及 QVBoxLayout 有些不同。它是设定整一行和整一列的弹簧，而不是设定某个格子的弹簧。
    grid->addWidget(parentNode,1,1);
    // 在第 0 列增加一个弹簧，比例为 1
    grid->setColumnStretch(0, 1);
    // 在第 0 行增加一个弹簧，比例为 1
    grid->setRowStretch(0, 1);
    // 在第 3 列增加一个弹簧，比例为 1
    grid->setColumnStretch(3, 1);
    // 在第 3 行增加一个弹簧，比例为 1
    grid->setRowStretch(3, 1);


    sonWidget =new QWidget(this);
    QTextEdit* sonNode =new QTextEdit(sonWidget);
    sonNode->setPlainText("sonNode\n111\n111\n111\n");
    QVBoxLayout* sonLayout = new QVBoxLayout(sonWidget);
    sonWidget->setLayout(sonLayout);
    sonLayout->addWidget(sonNode);
    sonLayout->addWidget(new QTextEdit(sonWidget));
    sonLayout->addWidget(new QTextEdit(sonWidget));
    sonLayout->addWidget(new QTextEdit(sonWidget));
    sonLayout->addWidget(new QTextEdit(sonWidget));
    sonLayout->addWidget(new QTextEdit(sonWidget));
    //布局添加widget
    //    layout->addWidget(parentNode);
    layout->addWidget(parentWidget);
    //    layout->addWidget(new QPushButton("111111111111111111111",this));
    layout->addWidget(sonWidget);
}
