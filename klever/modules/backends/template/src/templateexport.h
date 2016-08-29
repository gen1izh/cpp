#ifndef TEMPLATE_EXPORT_H
#define TEMPLATE_EXPORT_H

#include <QtCore/qglobal.h>

#if defined(TEMPLATE_PLUGIN)
#  define TEMPLATE_EXPORT Q_DECL_EXPORT
#else
#  define TEMPLATE_EXPORT Q_DECL_IMPORT
#endif

#endif // TEMPLATE_EXPORT_H
