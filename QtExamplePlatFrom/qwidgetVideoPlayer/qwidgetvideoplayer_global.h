#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QWIDGETVIDEOPLAYER_LIB)
#  define QWIDGETVIDEOPLAYER_EXPORT Q_DECL_EXPORT
# else
#  define QWIDGETVIDEOPLAYER_EXPORT Q_DECL_IMPORT
# endif
#else
# define QWIDGETVIDEOPLAYER_EXPORT
#endif
