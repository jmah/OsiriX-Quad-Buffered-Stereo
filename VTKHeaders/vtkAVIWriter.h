/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkAVIWriter.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkAVIWriter - Writes Windows AVI files.
// .SECTION Description
// vtkAVIWriter writes AVI files. The data type
// of the file is unsigned char regardless of the input type.
// .SECTION See Also
// vtkGenericMovieWriter vtkMPEG2Writer

#ifndef __vtkAVIWriter_h
#define __vtkAVIWriter_h

#include "vtkGenericMovieWriter.h"

class vtkAVIWriterInternal;

class VTK_IO_EXPORT vtkAVIWriter : public vtkGenericMovieWriter
{
public:
  static vtkAVIWriter *New();
  vtkTypeRevisionMacro(vtkAVIWriter,vtkGenericMovieWriter);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // These methods start writing an AVI file, write a frame to the file
  // and then end the writing process.
  void Start();
  void Write();
  void End();
  
protected:
  vtkAVIWriter();
  ~vtkAVIWriter();
  
  vtkAVIWriterInternal *Internals;

  int Rate;
  int Time;

private:
  vtkAVIWriter(const vtkAVIWriter&); // Not implemented
  void operator=(const vtkAVIWriter&); // Not implemented
};

#endif



