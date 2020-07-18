#include "MdStackedEditor.h"
#include "hoedown.h"

#include <QEvent>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QStyle>
#include <QMessageBox>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>

#include <QDebug>
#include "common/GolbalVar.h"
extern Hoedown hoedown;
MdStackedEditor::MdStackedEditor(QWidget *parent) : QWidget(parent)
{
    init();
    initCtrls(parent);
    //自定义菜单
    initMenu();
    connect(editWidget, &QPlainTextEdit::textChanged,[=]() {
        m_content = editWidget->toPlainText();
        QString htmlStr = hoedown.markdown2html(m_content);
        qDebug()<<htmlStr;
        htmlStr = "<html><head><meta charset='utf-8'>"
                " <link  rel=\"stylesheet\" href=\"D:/OneDrive/md/my-markdown.css\"> "
                  " <style type=\"text/css\"> \n"
                                  "code {\n"
                                  "    font-family: Consolas, Monaco, Andale Mono, monospace;\n"
                                  "    line-height: 1.5;\n"
                                  "    padding: .2em .4em;\n"
                                  "    margin: 0;\n"
                                  "    font-size: 85%;\n"
                                  "    background-color: rgba(27,31,35,.05);\n"
                                  "    border-radius: 3px;\n"
                                  "}\n"
                                  "</style> "
                "</head><body>"+ htmlStr + "</body></html>";
        qDebug()<<htmlStr.toUtf8().data();
        showWidget->setHtml(htmlStr);
    });
}
void MdStackedEditor::openFile(const QString& _filePath){
    m_filePath = _filePath;

    QFile defaultTextFile(_filePath);
    qDebug()<< "EditMd::openFile : " <<defaultTextFile.open(QIODevice::ReadOnly);
    editWidget->setPlainText(defaultTextFile.readAll());
}
//bool EditMd::eventFilter(QObject * obj, QEvent * e) {
////     qDebug()<< "EditMd::eventFilter QEvent " <<  e->type();
//    return QWidget::eventFilter(obj, e);
//}
void MdStackedEditor::mouseDoubleClickEvent(QMouseEvent *event){
//    qDebug()<< "EditMd::mouseDoubleClickEvent QMouseEvent " <<  event->button();

    //双击切换
    if(event->button() == Qt::LeftButton){
        if(m_stackWidget->currentWidget() == showWidget){
            m_stackWidget->setCurrentWidget(editWidget);
            //可以获得焦点 就是输入框
//            editWidget->setFocus();
        }else{
            m_stackWidget->setCurrentWidget(showWidget);

            //页面还是可以显示
//            showWidget->document()->setModified(true);
        }
     }
    //有菜单就不行
    if(event->button() == Qt::RightButton){
        //m_stackWidget->setCurrentWidget(showWidget);
     }
}
void MdStackedEditor::init()
{
    m_stackWidget = new QStackedWidget(this);
    showWidget = new QTextEdit(m_stackWidget);
    editWidget = new MdPlainTextEdit(m_stackWidget);
    editWidget->document()->setModified(true);
}

void MdStackedEditor::initMenu()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, [=](const QPoint &pos){
            QIcon view = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
            QIcon test = QApplication::style()->standardIcon(QStyle::SP_DesktopIcon);
            // 创建菜单
            QMenu menu;
            QAction * saveAction = menu.addAction(view, tr("save"), [=](){
                onFileSave();
            });
            //自动保存
            connect(editWidget->document(), &QTextDocument::modificationChanged,
                    saveAction, &QAction::setEnabled);
            menu.addSeparator();
            menu.addAction(test, tr("test"), [=](){
                qDebug()<<"test";
            });
            //菜单位置
            menu.exec(QCursor::pos());
    });
}

void MdStackedEditor::initCtrls(QWidget *parent) {

    // 设置鼠标穿透 为了 mouseDoubleClickEvent
    showWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    //子在上,父在下,无法用鼠标移动光标
//    editWidget->setAttribute(Qt::WA_TransparentForMouseEvents);

    //获取焦点
    showWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    m_stackWidget->setGeometry(0, 0, parent->width(),parent->height());

    showWidget->setGeometry(0, 0, parent->width(),parent->height());
    editWidget->setGeometry(0, 0, parent->width(),parent->height());
    //父类处理
    showWidget->installEventFilter(this);
//    editWidget->installEventFilter(this);

    m_stackWidget->addWidget(showWidget);
    m_stackWidget->addWidget(editWidget);
    m_stackWidget->setCurrentWidget(showWidget);

}
void MdStackedEditor::onFileSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this,
        tr("Save MarkDown File"), "", tr("MarkDown File (*.md, *.markdown)"));
    if (path.isEmpty())
        return;
    m_filePath = path;
    onFileSave();
}
void MdStackedEditor::onFileSave()
{
    if (m_filePath.isEmpty()) {
        onFileSaveAs();
        return;
    }

    QFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))  {
        QMessageBox::warning(this, windowTitle(),
                             tr("Could not write to file %1: %2").arg(
                                 QDir::toNativeSeparators(m_filePath), f.errorString()));
        return;
    }
    QTextStream str(&f);
    str << editWidget->toPlainText();
    editWidget->document()->setModified(false);
}
