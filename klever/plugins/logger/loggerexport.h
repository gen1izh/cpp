#ifndef LOGGER_EXPORT_H
#define LOGGER_EXPORT_H

#include <QtCore/qglobal.h>

#if defined(LOGGER_PLUGIN)
#  define LOGGER_EXPORT Q_DECL_EXPORT
#else
#  define LOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGGER_EXPORT_H
