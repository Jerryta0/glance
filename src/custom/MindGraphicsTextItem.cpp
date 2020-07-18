#include "MindGraphicsTextItem.h"
#include <QAbstractTextDocumentLayout>
MindGraphicsTextItem::MindGraphicsTextItem(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{

}
void MindGraphicsTextItem::adJustSize(){
    //获得文档的高度
    QTextDocument *doc= this->document();
    QAbstractTextDocumentLayout *layout = doc->documentLayout();
    int pixelsWidth = layout->documentSize().width();
    int pixelsHeight = layout->documentSize().height();
}
