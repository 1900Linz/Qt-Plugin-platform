#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DEMOVTK_LIB)
#  define DEMOVTK_EXPORT Q_DECL_EXPORT
# else
#  define DEMOVTK_EXPORT Q_DECL_IMPORT
# endif
#else
# define DEMOVTK_EXPORT
#endif
