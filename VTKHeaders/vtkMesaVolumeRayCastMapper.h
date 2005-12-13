/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMesaVolumeRayCastMapper.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkMesaVolumeRayCastMapper - Mesa subclass that draws the image to the screen
// .SECTION Description
// This is the concrete implementation of a ray cast mapper - it is 
// responsible for drawing the image to the screen. The remaining
// functionality all comes from vtkVolumeRayCastMapper

// .SECTION see also
// vtkVolumeRayCastMapper vtkVolumeMapper

#ifndef __vtkMesaVolumeRayCastMapper_h
#define __vtkMesaVolumeRayCastMapper_h

#include "vtkVolumeRayCastMapper.h"


class VTK_RENDERING_EXPORT vtkMesaVolumeRayCastMapper : public vtkVolumeRayCastMapper
{
public:
  static vtkMesaVolumeRayCastMapper *New();
  vtkTypeRevisionMacro(vtkMesaVolumeRayCastMapper,vtkVolumeRayCastMapper);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkMesaVolumeRayCastMapper();
  ~vtkMesaVolumeRayCastMapper();

  void RenderTexture( vtkVolume *vol, vtkRenderer *ren);

private:
  vtkMesaVolumeRayCastMapper(const vtkMesaVolumeRayCastMapper&);  // Not implemented.
  void operator=(const vtkMesaVolumeRayCastMapper&);  // Not implemented.
};

#endif

