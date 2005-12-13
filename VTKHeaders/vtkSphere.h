/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkSphere.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSphere - implicit function for a sphere
// .SECTION Description
// vtkSphere computes the implicit function and/or gradient for a sphere.
// vtkSphere is a concrete implementation of vtkImplicitFunction.

#ifndef __vtkSphere_h
#define __vtkSphere_h

#include "vtkImplicitFunction.h"

class VTK_FILTERING_EXPORT vtkSphere : public vtkImplicitFunction
{
public:
  vtkTypeRevisionMacro(vtkSphere,vtkImplicitFunction);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description
  // Construct sphere with center at (0,0,0) and radius=0.5.
  static vtkSphere *New();

  // Description
  // Evaluate sphere equation ((x-x0)^2 + (y-y0)^2 + (z-z0)^2) - R^2.
  double EvaluateFunction(double x[3]);
  double EvaluateFunction(double x, double y, double z)
    {return this->vtkImplicitFunction::EvaluateFunction(x, y, z); } ;

  // Description
  // Evaluate sphere gradient.
  void EvaluateGradient(double x[3], double n[3]);

  // Description:
  // Set / get the radius of the sphere.
  vtkSetMacro(Radius,double);
  vtkGetMacro(Radius,double);

  // Description:
  // Set / get the center of the sphere.
  vtkSetVector3Macro(Center,double);
  vtkGetVectorMacro(Center,double,3);

protected:
  vtkSphere();
  ~vtkSphere() {};

  double Radius;
  double Center[3];

private:
  vtkSphere(const vtkSphere&);  // Not implemented.
  void operator=(const vtkSphere&);  // Not implemented.
};

#endif


