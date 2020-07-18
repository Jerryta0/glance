#include "FolderTreeView.h"
#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
void FolderTreeView::defaultSetting()
{
    // 为treeView添加右键菜单
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeView::customContextMenuRequested, [=](const QPoint &pos){
        // 《给QTreeView表项添加右键菜单》：系列教程之四
        // https://blog.csdn.net/zyhse/article/details/105894442
        QModelIndex curIndex = this->indexAt(pos);
        // 右键选中了有效index
        if (curIndex.isValid())
        {
            QIcon view = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
            QIcon test = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);

            // 创建菜单
            QMenu menu;
            menu.addAction(view, tr("look"), [=](){
                QModelIndex curIndex = this->currentIndex();
                 // sibling同胞 获取同一行第0列
                QModelIndex index = curIndex.sibling(curIndex.row(), 0);
                if(index.isValid())
                {
                    QMessageBox::information(this, tr("信息"), index.data().toString());
                }
            });
            menu.addSeparator();
            menu.addAction(test, tr("test"), [=](){
                qDebug()<<"test";
            });
            //菜单位置
            menu.exec(QCursor::pos());
        }

    });
}

FolderTreeView::FolderTreeView(QWidget *parent) : QTreeView(parent)
{

    defaultSetting();
}
