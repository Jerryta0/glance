#include "MdGraphicsTextItem.h"
#include <QAbstractTextDocumentLayout>
MdGraphicsTextItem::MdGraphicsTextItem(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{

}
void MdGraphicsTextItem::adJustSize(){
    //获得文档的高度
    QTextDocument *doc= this->document();
    QAbstractTextDocumentLayout *layout = doc->documentLayout();
    int pixelsWidth = layout->documentSize().width();
    int pixelsHeight = layout->documentSize().height();
}
