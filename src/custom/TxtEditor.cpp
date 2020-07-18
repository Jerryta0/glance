#include "TxtEditor.h"

#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QStyle>
#include <QFile>
#include <QShortcut>
TxtEditor::TxtEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    defaultSetting();
}
TxtEditor::TxtEditor(const QString& _filePath,QWidget *parent):TxtEditor(parent){
    filePath = _filePath;
}


void TxtEditor::defaultSetting()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, [=](const QPoint &pos){
        this->childAt(pos);
        QIcon view = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
        QIcon test = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);

        // 创建菜单
        QMenu menu;
        menu.addAction(view, tr("save"), [=](){
            this->saveFile();
        });

        menu.addSeparator();
        menu.addAction(test, tr("test"), [=](){
            qDebug()<<"test";
        });
        //菜单位置
        menu.exec(QCursor::pos());
    });

    //按键
    QShortcut *saveCut = new QShortcut(this);
    //设置键值，也就是设置快捷键.
    saveCut->setKey(tr("ctrl+s"));
    //设置是否会自动反复按键.
    saveCut->setAutoRepeat(false);
    //连接信号与槽，showSlot()是自定义的槽函数!
    connect(saveCut, &QShortcut::activated, this, &TxtEditor::saveFile);
}
void TxtEditor::saveFile(){
    if(m_isTextChanged){
        return;
    }
    if(filePath.isEmpty()){
        return;
    }
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << this->toPlainText();
        file.close();
        m_isTextChanged = false;
    }
    file.close();
    qDebug()<<"save file";
    emit printMsg(QString("save file : %1").arg(filePath));
}

void TxtEditor::wheelEvent(QWheelEvent *event)
{
    qDebug() << "wheel";
    if ( QApplication::keyboardModifiers () == Qt::ControlModifier)
     {
        if (event->delta() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
     }
}
