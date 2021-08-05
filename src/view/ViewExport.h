/*
* HelloCAD a simple cad platform
*/

#pragma once

#include <QObject>

#if defined(WIN32)
#if defined(VIEW_LIB)
#define VIEW_EXPORT Q_DECL_EXPORT
#else
#define VIEW_EXPORT Q_DECL_IMPORT
#endif
#else
#define VIEW_EXPORT
#endif

