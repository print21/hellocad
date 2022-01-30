/*
 *HelloCAD a simple cad platform
*/

#pragma once

#if defined(WIN32)
#if defined(DATA_LIB)
#define DATA_EXPORT Q_DECL_EXPORT
#else
#define DATA_EXPORT Q_DECL_IMPORT
#endif
#else
#define DATA_EXPORT
#endif

