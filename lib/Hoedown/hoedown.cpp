#include "hoedown.h"
#include "html.h"
#include <QDebug>
Hoedown::Hoedown()
{

}

QString Hoedown::markdown2html(const QString &mdText){
    return QString(markdown2HtmlGetArray(mdText.toUtf8()));
}
QByteArray Hoedown::markdown2HtmlGetArray(const QByteArray &markdownText){
    //教程
    //https://github.com/qyvlik/MarkdownEditor
    //https://github.com/hoedown/hoedown/wiki/Getting-Started

    int markdownLength = markdownText.size();
    if(markdownLength == 0) {
        return QByteArray("");
    }

    hoedown_buffer *ib, *ob;
    hoedown_renderer *renderer = nullptr;
    hoedown_document *document;

    // malloc
    ob = hoedown_buffer_new(markdownLength);
    ib = hoedown_buffer_new(markdownLength);
    renderer = hoedown_html_renderer_new(HOEDOWN_HTML_USE_XHTML, 0);


    // 尽可能的指定
    document = hoedown_document_new(renderer, HOEDOWN_EXT_TABLES, 16);

    // put data
    hoedown_buffer_put(ib, (const uint8_t *) markdownText.toStdString().c_str(), markdownText.size());

    // render markdown to html
    hoedown_document_render(document, ob, ib->data, ib->size);

    QByteArray html((const char*)ob->data, ob->size);

    // free
    hoedown_buffer_free(ib);
    hoedown_document_free(document);
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(ob);
    return html;
}
