#include "EditMd.h"
#include "PreviewPage.h"
#include <QWebChannel>
#include <QEvent>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QStyle>
#include <QMessageBox>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileDialog>

EditMd::EditMd(QWidget *parent) : QWidget(parent)
{
    initCtrls(parent);

    //鼠标碰不到
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

    PreviewPage *page = new PreviewPage(this);
    showWidget->setPage(page);

    connect(editWidget, &QPlainTextEdit::textChanged,
            [=]() { m_content.setText(editWidget->toPlainText()); });

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);
    //必须是qrc:
//    showWidget->setUrl(QUrl("qrc:/res/md/index.html"));
    showWidget->setUrl(QUrl("qrc:/res/md-it/index.html"));
}
void EditMd::openFile(const QString& _filePath){
    m_filePath = _filePath;

    QFile defaultTextFile(_filePath);
    qDebug()<< "EditMd::openFile : " <<defaultTextFile.open(QIODevice::ReadOnly);
    editWidget->setPlainText(defaultTextFile.readAll());
}
bool EditMd::eventFilter(QObject * obj, QEvent * e) {
     qDebug()<< "EditMd::eventFilter QEvent " <<  e->type();

    return QWidget::eventFilter(obj, e);
}
void EditMd::mouseDoubleClickEvent(QMouseEvent *event){
    qDebug()<< "EditMd::mouseDoubleClickEvent QMouseEvent " <<  event->button();

    //双击切换
    if(event->button() == Qt::LeftButton){
        if(m_stackWidget->currentWidget() == showWidget){
            m_stackWidget->setCurrentWidget(editWidget);
        }else{
            m_stackWidget->setCurrentWidget(showWidget);
        }
     }
    //有菜单就不行
    if(event->button() == Qt::RightButton){
        //m_stackWidget->setCurrentWidget(showWidget);
     }
}
void EditMd::initCtrls(QWidget *parent) {
    m_stackWidget = new QStackedWidget(this);

    showWidget = new QWebEngineView(this);
    editWidget = new QPlainTextEdit(this);
    // 设置鼠标穿透 为了 mouseDoubleClickEvent
    showWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    editWidget->setAttribute(Qt::WA_TransparentForMouseEvents);

    showWidget->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    m_stackWidget->setGeometry(0, 0, parent->width(),parent->height());
    showWidget->setGeometry(0, 0, parent->width(),parent->height());
    editWidget->setGeometry(0, 0, parent->width(),parent->height());
    //父类处理
    showWidget->installEventFilter(this);
    editWidget->installEventFilter(this);

    m_stackWidget->addWidget(showWidget);
    m_stackWidget->addWidget(editWidget);

    m_stackWidget->setCurrentWidget(showWidget);
}
void EditMd::onFileSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this,
        tr("Save MarkDown File"), "", tr("MarkDown File (*.md, *.markdown)"));
    if (path.isEmpty())
        return;
    m_filePath = path;
    onFileSave();
}
void EditMd::onFileSave()
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
