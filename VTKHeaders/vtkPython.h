/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPython.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkPython_h
#define __vtkPython_h

#undef _POSIX_THREADS

#include "vtkToolkits.h"

/* Use the real python debugging library if it is provided.  */
#if defined(VTK_WINDOWS_PYTHON_DEBUGGABLE)
# include <Python.h>
#else
# ifdef _DEBUG
#  undef _DEBUG
#  include <Python.h>
#  define _DEBUG
# else
#  include <Python.h>
# endif
#endif

#endif
