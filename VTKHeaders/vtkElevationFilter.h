/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkElevationFilter.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkElevationFilter - generate scalars along a specified direction
// .SECTION Description
// vtkElevationFilter is a filter to generate scalar values from a dataset.
// The scalar values lie within a user specified range, and are generated
// by computing a projection of each dataset point onto a line. The line
// can be oriented arbitrarily. A typical example is to generate scalars
// based on elevation or height above a plane.

#ifndef __vtkElevationFilter_h
#define __vtkElevationFilter_h

#include "vtkDataSetAlgorithm.h"

class VTK_GRAPHICS_EXPORT vtkElevationFilter : public vtkDataSetAlgorithm 
{
public:
  vtkTypeRevisionMacro(vtkElevationFilter,vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Construct object with LowPoint=(0,0,0) and HighPoint=(0,0,1). Scalar
  // range is (0,1).
  static vtkElevationFilter *New();

  // Description:
  // Define one end of the line (small scalar values).
  vtkSetVector3Macro(LowPoint,double);
  vtkGetVectorMacro(LowPoint,double,3);

  // Description:
  // Define other end of the line (large scalar values).
  vtkSetVector3Macro(HighPoint,double);
  vtkGetVectorMacro(HighPoint,double,3);

  // Description:
  // Specify range to map scalars into.
  vtkSetVector2Macro(ScalarRange,double);
  vtkGetVectorMacro(ScalarRange,double,2);

protected:
  vtkElevationFilter();
  ~vtkElevationFilter() {};

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  double LowPoint[3];
  double HighPoint[3];
  double ScalarRange[2];
private:
  vtkElevationFilter(const vtkElevationFilter&);  // Not implemented.
  void operator=(const vtkElevationFilter&);  // Not implemented.
};

#endif


