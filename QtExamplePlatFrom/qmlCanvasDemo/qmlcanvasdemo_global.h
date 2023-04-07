#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QMLCANVASDEMO_LIB)
#  define QMLCANVASDEMO_EXPORT Q_DECL_EXPORT
# else
#  define QMLCANVASDEMO_EXPORT Q_DECL_IMPORT
# endif
#else
# define QMLCANVASDEMO_EXPORT
#endif
