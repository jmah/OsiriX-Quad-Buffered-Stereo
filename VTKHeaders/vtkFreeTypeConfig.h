#ifndef _freetypeConfig_h
#define _freetypeConfig_h

#if defined(__BORLANDC__)
#pragma warn -8004 /* Disable "foo is assigned a value that is never used." */
#endif

/* 
   Static or shared lib flags
*/
/* #undef VTKFREETYPE_DLL */
#define VTKFREETYPE_STATIC

/* 
   HPUX workaround
*/
/* #undef VTKFREETYPE_HPUX_SOURCE */
#if defined(VTKFREETYPE_HPUX_SOURCE) && !defined(_HPUX_SOURCE)
#define _HPUX_SOURCE
#endif

/* 
   Carbon framework
*/
/* #undef VTKFREETYPE_USE_CARBON */
#if defined(VTKFREETYPE_USE_CARBON) && !defined(FT_USE_CARBON_HEADER)
#define FT_USE_CARBON_HEADER
#endif

#endif
