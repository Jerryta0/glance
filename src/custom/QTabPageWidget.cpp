#include "QTabPageWidget.h"

#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QStyle>
#include <QFile>

QTabPageWidget::QTabPageWidget(QWidget *parent) : QTabWidget(parent)
{
    defaultSetting();
}
void QTabPageWidget::defaultSetting()
{
    //开启可关闭
    this->setTabsClosable(true);
    //关闭按钮点击,发出信号
    // void tabCloseRequested(int index);
    connect(this,&QTabWidget::tabCloseRequested,[=](int index){
        this->removeTab(index);
    });

    //双击关闭
    // void tabBarDoubleClicked(int index);
    connect(this,&QTabWidget::tabBarDoubleClicked,[=](){
        int index= currentIndex();
        this->removeTab(index);
    });
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, [=](const QPoint &pos){
        this->childAt(pos);
        QIcon view = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
        QIcon test = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);

        // 创建菜单
        QMenu menu;
        menu.addAction(view, tr("close other"), [=](){
            qDebug()<<"look";
        });
        menu.addSeparator();
        menu.addAction(test, tr("test"), [=](){
            qDebug()<<"test";
        });
        //菜单位置
        menu.exec(QCursor::pos());
    });
}

int QTabPageWidget::addTabOnly(QWidget *widget, const QString &tabName){
    // 循环查找tab页
    for (int i = 0; i < this->count(); ++i)
    {
        if (this->tabText(i) == tabName)
        {
            qDebug()<<"setCurrentIndex";
            // 跳转
            this->setCurrentIndex(i);
            return i;
        }
    }
    int currentIndex = this->addTab(widget, tabName);
    this->setCurrentIndex(currentIndex);
    return currentIndex;
}
