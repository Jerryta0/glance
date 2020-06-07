#ifndef INLIB_GLOBAL_H
#define INLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INLIB_LIBRARY)
#  define INLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define INLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INLIB_GLOBAL_H
