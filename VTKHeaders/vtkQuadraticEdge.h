/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkQuadraticEdge.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkQuadraticEdge - cell represents a parabolic, isoparametric edge
// .SECTION Description
// vtkQuadraticEdge is a concrete implementation of vtkNonLinearCell to
// represent a one-dimensional, 3-nodes, isoparametric parabolic line. The
// interpolation is the standard finite element, quadratic isoparametric
// shape function. The cell includes a mid-edge node. The ordering of the
// three points defining the cell is point ids (0,1,2) where id #2 is the
// midedge node.

// .SECTION See Also
// vtkQuadraticTriangle vtkQuadraticTetra vtkQuadraticWedge
// vtkQuadraticQuad vtkQuadraticHexahedron vtkQuadraticPyramid

#ifndef __vtkQuadraticEdge_h
#define __vtkQuadraticEdge_h

#include "vtkNonLinearCell.h"

class vtkPolyData;
class vtkLine;

class VTK_FILTERING_EXPORT vtkQuadraticEdge : public vtkNonLinearCell
{
public:
  static vtkQuadraticEdge *New();
  vtkTypeRevisionMacro(vtkQuadraticEdge,vtkNonLinearCell);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Implement the vtkCell API. See the vtkCell API for descriptions 
  // of these methods.
  int GetCellType() {return VTK_QUADRATIC_EDGE;};
  int GetCellDimension() {return 1;}
  int GetNumberOfEdges() {return 0;}
  int GetNumberOfFaces() {return 0;}
  vtkCell *GetEdge(int) {return 0;}
  vtkCell *GetFace(int) {return 0;}

  int CellBoundary(int subId, double pcoords[3], vtkIdList *pts);
  void Contour(double value, vtkDataArray *cellScalars, 
               vtkPointLocator *locator, vtkCellArray *verts, 
               vtkCellArray *lines, vtkCellArray *polys, 
               vtkPointData *inPd, vtkPointData *outPd,
               vtkCellData *inCd, vtkIdType cellId, vtkCellData *outCd);
  int EvaluatePosition(double x[3], double* closestPoint,
                       int& subId, double pcoords[3], 
                       double& dist2, double *weights);
  void EvaluateLocation(int& subId, double pcoords[3], double x[3],
                        double *weights);
  int Triangulate(int index, vtkIdList *ptIds, vtkPoints *pts);
  void Derivatives(int subId, double pcoords[3], double *values, 
                   int dim, double *derivs);
  virtual double *GetParametricCoords();

  // Description:
  // Clip this edge using scalar value provided. Like contouring, except
  // that it cuts the edge to produce linear line segments.
  void Clip(double value, vtkDataArray *cellScalars, 
            vtkPointLocator *locator, vtkCellArray *lines,
            vtkPointData *inPd, vtkPointData *outPd,
            vtkCellData *inCd, vtkIdType cellId, vtkCellData *outCd,
            int insideOut);

  // Description:
  // Line-edge intersection. Intersection has to occur within [0,1] parametric
  // coordinates and with specified tolerance.
  int IntersectWithLine(double p1[3], double p2[3], double tol, double& t,
                        double x[3], double pcoords[3], int& subId);

  
  // Description:
  // Quadratic edge specific methods. 
  static void InterpolationFunctions(double pcoords[3], double weights[3]);
  static void InterpolationDerivs(double pcoords[3], double derivs[3]);

protected:
  vtkQuadraticEdge();
  ~vtkQuadraticEdge();

  vtkLine *Line;
  vtkDoubleArray *Scalars; //used to avoid New/Delete in contouring/clipping

private:
  vtkQuadraticEdge(const vtkQuadraticEdge&);  // Not implemented.
  void operator=(const vtkQuadraticEdge&);  // Not implemented.
};

#endif


