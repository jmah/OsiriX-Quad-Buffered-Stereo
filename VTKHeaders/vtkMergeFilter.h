/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMergeFilter.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkMergeFilter - extract separate components of data from different datasets
// .SECTION Description
// vtkMergeFilter is a filter that extracts separate components of data from
// different datasets and merges them into a single dataset. The output from
// this filter is of the same type as the input (i.e., vtkDataSet.) It treats 
// both cell and point data set attributes.

#ifndef __vtkMergeFilter_h
#define __vtkMergeFilter_h

#include "vtkDataSetAlgorithm.h"

class vtkFieldList;

class VTK_GRAPHICS_EXPORT vtkMergeFilter : public vtkDataSetAlgorithm
{
public:
  static vtkMergeFilter *New();
  vtkTypeRevisionMacro(vtkMergeFilter,vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify object from which to extract geometry information.
  void SetGeometry(vtkDataSet *input) {this->SetInput(input);};
  vtkDataSet *GetGeometry();

  // Description:
  // Specify object from which to extract scalar information.
  void SetScalars(vtkDataSet *);
  vtkDataSet *GetScalars();

  // Description:
  // Set / get the object from which to extract vector information.
  void SetVectors(vtkDataSet *);
  vtkDataSet *GetVectors();
  
  // Description:
  // Set / get the object from which to extract normal information.
  void SetNormals(vtkDataSet *);
  vtkDataSet *GetNormals();
  
  // Description:
  // Set / get the object from which to extract texture coordinates
  // information.
  void SetTCoords(vtkDataSet *);
  vtkDataSet *GetTCoords();

  // Description:
  // Set / get the object from which to extract tensor data.
  void SetTensors(vtkDataSet *);
  vtkDataSet *GetTensors();

  // Description:
  // Set the object from which to extract a field and the name
  // of the field
  void AddField(const char* name, vtkDataSet* input);

protected:
  vtkMergeFilter();
  ~vtkMergeFilter();

  // Usual data generation method
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  int RequestUpdateExtent(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  int FillInputPortInformation(int port, vtkInformation *info);

  vtkFieldList* FieldList;
private:
  vtkMergeFilter(const vtkMergeFilter&);  // Not implemented.
  void operator=(const vtkMergeFilter&);  // Not implemented.
  };

#endif


