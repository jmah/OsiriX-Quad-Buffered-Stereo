/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImageGradient.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageGradient - Computes the gradient vector.
// .SECTION Description
// vtkImageGradient computes the gradient vector of an image.  The vector
// results are stored as scalar components. The Dimensionality determines
// whether to perform a 2d or 3d gradient. The default is two dimensional 
// XY gradient.  OutputScalarType is always double. Gradient is computed using
// central differences.



#ifndef __vtkImageGradient_h
#define __vtkImageGradient_h


#include "vtkThreadedImageAlgorithm.h"

class VTK_IMAGING_EXPORT vtkImageGradient : 
  public vtkThreadedImageAlgorithm
{
public:
  static vtkImageGradient *New();
  vtkTypeRevisionMacro(vtkImageGradient,vtkThreadedImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Determines how the input is interpreted (set of 2d slices ...)
  vtkSetClampMacro(Dimensionality,int,2,3);
  vtkGetMacro(Dimensionality,int);
  
  // Description:
  // If "HandleBoundariesOn" then boundary pixels are duplicated
  // So central differences can get values.
  vtkSetMacro(HandleBoundaries, int);
  vtkGetMacro(HandleBoundaries, int);
  vtkBooleanMacro(HandleBoundaries, int);

protected:
  vtkImageGradient();
  ~vtkImageGradient() {};

  int HandleBoundaries;
  int Dimensionality;

  virtual int RequestInformation (vtkInformation*,
                                  vtkInformationVector**,
                                  vtkInformationVector*);
  virtual int RequestUpdateExtent(vtkInformation*,
                                  vtkInformationVector**,
                                  vtkInformationVector*);

  void ThreadedExecute (vtkImageData *inData, vtkImageData *outData,
                       int extent[6], int id);
private:
  vtkImageGradient(const vtkImageGradient&);  // Not implemented.
  void operator=(const vtkImageGradient&);  // Not implemented.
};

#endif



