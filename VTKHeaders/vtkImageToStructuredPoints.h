/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkImageToStructuredPoints.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageToStructuredPoints - Attaches image pipeline to VTK. 
// .SECTION Description
// vtkImageToStructuredPoints changes an image cache format to
// a structured points dataset.  It takes an Input plus an optional
// VectorInput. The VectorInput converts the RGB scalar components
// of the VectorInput to vector pointdata attributes. This filter
// will try to reference count the data but in some cases it must
// make a copy.

#ifndef __vtkImageToStructuredPoints_h
#define __vtkImageToStructuredPoints_h

#include "vtkImageAlgorithm.h"
 
class vtkImageData;
class vtkStructuredPoints;

class VTK_FILTERING_EXPORT vtkImageToStructuredPoints : public vtkImageAlgorithm
{
public:
  static vtkImageToStructuredPoints *New();
  vtkTypeRevisionMacro(vtkImageToStructuredPoints,vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Set/Get the input object from the image pipeline.
  void SetVectorInput(vtkImageData *input);
  vtkImageData *GetVectorInput();

protected:
  vtkImageToStructuredPoints();
  ~vtkImageToStructuredPoints();

  // to translate the wholeExtent to have min 0 ( I do not like this hack).
  int Translate[3];
  
  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int RequestInformation (vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  virtual int RequestUpdateExtent(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  virtual int FillOutputPortInformation(int, vtkInformation*);
  virtual int FillInputPortInformation(int, vtkInformation*);

private:
  vtkImageToStructuredPoints(const vtkImageToStructuredPoints&);  // Not implemented.
  void operator=(const vtkImageToStructuredPoints&);  // Not implemented.
};


#endif


