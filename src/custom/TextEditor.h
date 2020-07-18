#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class TextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:

    QString filePath;
    bool m_isTextChanged = false;
    explicit TextEditor(QWidget *parent = nullptr);
    explicit TextEditor(const QString& filePath,QWidget *parent = nullptr);
    //默认设置
    void defaultSetting();
    void saveFile();
//    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);



signals:
    void printMsg(const QString& msg);
};

#endif // TEXTEDITOR_H
