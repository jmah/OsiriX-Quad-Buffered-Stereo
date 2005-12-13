/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkColorTransferFunction.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkColorTransferFunction - Defines a transfer function for mapping a property to an RGB color value.

// .SECTION Description
// vtkColorTransferFunction encapsulates three vtkPiecewiseFunction instances
// to provide a full RGB transfer function.

// .SECTION see also
// vtkPiecewiseFunction

#ifndef __vtkColorTransferFunction_h
#define __vtkColorTransferFunction_h

#include "vtkScalarsToColors.h"

class vtkPiecewiseFunction;

#define VTK_CTF_RGB           0
#define VTK_CTF_HSV           1

class VTK_FILTERING_EXPORT vtkColorTransferFunction : public vtkScalarsToColors 
{
public:
  static vtkColorTransferFunction *New();
  vtkTypeRevisionMacro(vtkColorTransferFunction,vtkScalarsToColors);
  void DeepCopy( vtkColorTransferFunction *f );

  // Description:
  // Print method for vtkColorTransferFunction
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // How many points are there defining this function?
  int GetSize() {return this->NumberOfPoints;};
  
  // Description:
  // Add/Remove a point to/from the function defined in RGB or HSV
  // Return the index of the point (0 based), or -1 on error.
  int AddRGBPoint( double x, double r, double g, double b );
  int AddHSVPoint( double x, double h, double s, double v );
  int RemovePoint( double x );

  // Description:
  // Add two points to the function and remove all the points 
  // between them
  void AddRGBSegment( double x1, double r1, double g1, double b1, 
                      double x2, double r2, double g2, double b2 );
  void AddHSVSegment( double x1, double h1, double s1, double v1, 
                      double x2, double h2, double s2, double v2 );
  
  // Description:
  // Remove all points
  void RemoveAllPoints();

  // Description:
  // Returns an RGB color for the specified scalar value 
  double *GetColor(double x) {
    return vtkScalarsToColors::GetColor(x); }
  void GetColor(double x, double rgb[3]);

  // Description:
  // Get the color components individually.
  double GetRedValue( double x );
  double GetGreenValue( double x );
  double GetBlueValue( double x );

  // Description:
  // Map one value through the lookup table.
  virtual unsigned char *MapValue(double v);

  // Description:
  // Returns min and max position of all function points.
  vtkGetVector2Macro( Range, double );

  // Description:
  // Remove all points out of the new range, and make sure there is a point
  // at each end of that range.
  // Return 1 on success, 0 otherwise.
  int AdjustRange(double range[2]);

  // Description:
  // Fills in a table of n function values between x1 and x2
  void GetTable( double x1, double x2, int n, double* table );
  void GetTable( double x1, double x2, int n, float* table );
  const unsigned char *GetTable( double x1, double x2, int n);

  // Description:
  // Construct a color transfer function from a table. Function range is
  // is set to [x1, x2], each function size is set to size, and function 
  // points are regularly spaced between x1 and x2. Parameter "table" is 
  // assumed to be a block of memory of size [3*size]
  void BuildFunctionFromTable( double x1, double x2, int size, double *table);

  // Description:
  // Sets and gets the clamping value for this transfer function.
  vtkSetClampMacro( Clamping, int, 0, 1 );
  vtkGetMacro( Clamping, int );
  vtkBooleanMacro( Clamping, int );
  
  // Description:
  // Set/Get the color space used for interpolation: RGB, or HSV.
  // In HSV mode, if HSVWrap is on, it  will take the shortest path in Hue
  // (going back through 0 if that is the shortest way around the hue circle)
  // whereas if HSVWrap is off it will not go through 0 (in order the match
  // the current functionality of vtkLookupTable)
  vtkSetClampMacro( ColorSpace, int, VTK_CTF_RGB, VTK_CTF_HSV );
  void SetColorSpaceToRGB(){this->SetColorSpace(VTK_CTF_RGB);};
  void SetColorSpaceToHSV(){this->SetColorSpace(VTK_CTF_HSV);};
  vtkGetMacro( ColorSpace, int );
  vtkSetMacro(HSVWrap, int);
  vtkGetMacro(HSVWrap, int);
  vtkBooleanMacro(HSVWrap, int);
  VTK_LEGACY(void SetColorSpaceToHSVNoWrap());
    
  // Description:
  // Returns a list of all nodes
  // Fills from a pointer to data stored in a similar list of nodes.
  double *GetDataPointer() {return this->Function;};
  void FillFromDataPointer(int, double*);

  // Description:
  // map a set of scalars through the lookup table
  virtual void MapScalarsThroughTable2(void *input, unsigned char *output,
                                     int inputDataType, int numberOfValues,
                                     int inputIncrement, int outputIncrement);
  
protected:
  vtkColorTransferFunction();
  ~vtkColorTransferFunction();

  // Determines the function value outside of defined points
  // Zero = always return 0.0 outside of defined points
  // One  = clamp to the lowest value below defined points and
  //        highest value above defined points
  int Clamping;

  // The color space in which interpolation is performed
  int ColorSpace;

  // Specify if HSW is warp or not
  int HSVWrap;
  
  // The color function
  double     *Function;
  int         FunctionSize;
  int         NumberOfPoints;

  // An evaluated color (0 to 255 RGBA A=255)
  unsigned char UnsignedCharRGBAValue[4];

  // The min and max point locations for all three transfer functions
  double Range[2]; 

  // Transfer functions for each color component
  // Remove after corresponding depricated methods are removed
  vtkPiecewiseFunction  *Red;
  vtkPiecewiseFunction  *Green;
  vtkPiecewiseFunction  *Blue;
  vtkTimeStamp BuildTime;
  unsigned char *Table;
  int TableSize;
  
  // Description:
  // Set the range of scalars being mapped. The set has no functionality
  // in this subclass of vtkScalarsToColors.
  virtual void SetRange(double, double) {};
  void SetRange(double rng[2]) {this->SetRange(rng[0],rng[1]);};


private:
  vtkColorTransferFunction(const vtkColorTransferFunction&);  // Not implemented.
  void operator=(const vtkColorTransferFunction&);  // Not implemented.
};

#endif

