#ifndef HOEDOWN_GLOBAL_H
#define HOEDOWN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HOEDOWN_LIBRARY)
#  define HOEDOWN_EXPORT Q_DECL_EXPORT
#else
#  define HOEDOWN_EXPORT Q_DECL_IMPORT
#endif

#endif // HOEDOWN_GLOBAL_H
