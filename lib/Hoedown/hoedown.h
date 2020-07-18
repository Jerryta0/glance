#ifndef HOEDOWN_H
#define HOEDOWN_H

#include "Hoedown_global.h"

class HOEDOWN_EXPORT Hoedown
{
public:
    Hoedown();
    QString markdown2html(const QString &mdText);
    QByteArray markdown2HtmlGetArray(const QByteArray &markdownText);
};

#endif // HOEDOWN_H
