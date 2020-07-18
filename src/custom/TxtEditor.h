#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>


/**
* @author taojiayu
* @date 2020-07-19
* @desc txt文件编辑器
*/
class TxtEditor : public QPlainTextEdit
{
    Q_OBJECT
public:

    QString filePath;
    bool m_isTextChanged = false;
    explicit TxtEditor(QWidget *parent = nullptr);
    explicit TxtEditor(const QString& filePath,QWidget *parent = nullptr);
    //默认设置
    void defaultSetting();
    void saveFile();
//    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);



signals:
    void printMsg(const QString& msg);
};

#endif // TEXTEDITOR_H
