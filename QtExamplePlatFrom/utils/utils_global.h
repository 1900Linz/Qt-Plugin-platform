#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(UTILS_LIB)
#  define UTILS_EXPORT Q_DECL_EXPORT
# else
#  define UTILS_EXPORT Q_DECL_IMPORT
# endif
#else
# define UTILS_EXPORT
#endif
