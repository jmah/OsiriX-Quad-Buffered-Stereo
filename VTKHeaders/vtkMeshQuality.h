/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkMeshQuality.h,v $
  Language:  C++
  Date:      $Date: 2005/02/19 01:50:46 $ 
  Version:   $Revision: 1.21 $

  Copyright 2003 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
  license for use of this work by or on behalf of the
  U.S. Government. Redistribution and use in source and binary forms, with
  or without modification, are permitted provided that this Notice and any
  statement of authorship are reproduced on all copies.

  Contact: dcthomp@sandia.gov,pppebay@ca.sandia.gov

=========================================================================*/
// .NAME vtkMeshQuality - Calculate measures of quality of a mesh
//
// .SECTION Description
// vtkMeshQuality computes one or more measures of (geometric)
// quality for each 2-D and 3-D cell (triangle, quadrilateral, tetrahedron,
// or hexahedron) of a mesh. These measures of quality are then averaged
// over the entire mesh. The minimum, average, maximum, and variance
// of quality for each type of cell is stored in the output mesh's FieldData.
// The FieldData arrays are named "Mesh Triangle Quality,"
// "Mesh Quadrilateral Quality," "Mesh Tetrahedron Quality,"
// and "Mesh Hexahedron Quality." Each array has a single tuple
// with 5 components. The first 4 components are the quality statistics
// mentioned above; the final value is the number of cells of the given type.
// This final component makes aggregation of statistics for distributed
// mesh data possible.
//
// By default, the per-cell quality is added to the mesh's cell data, in
// an array named "Quality." Cell types not supported by
// this filter will have an entry of 0. Use SaveCellQualityOff() to
// store only the final statistics.
//
// This version of the filter overtakes an older version written by
// Leila Baghdadi, Hanif Ladak, and David Steinman at the Imaging Research
// Labs, Robarts Research Institute. That version focused solely on
// tetrahedra. See the CompatibilityModeOn() member for information on
// how to make this filter behave like the previous implementation.
//
// .SECTION Caveats
// While more general than before, this class does not address many
// cell types, including wedges and pyramids in 3D and triangle strips
// and fans in 2D (among others). 
// Most quadrilateral quality measures are intended for planar quadrilaterals
// only. 
// The minimal angle is not, strictly speaking, a quality measure, but it is
// provided because of its useage by many authors.

#ifndef vtkMeshQuality_h
#define vtkMeshQuality_h

#include "vtkDataSetAlgorithm.h"

class vtkCell;

#define VTK_QUALITY_EDGE_RATIO 0
#define VTK_QUALITY_ASPECT_RATIO 1
#define VTK_QUALITY_RADIUS_RATIO 2
#define VTK_QUALITY_FROBENIUS_NORM 3
#define VTK_QUALITY_MED_FROBENIUS_NORM 4
#define VTK_QUALITY_MAX_FROBENIUS_NORM 5
#define VTK_QUALITY_MIN_ANGLE 6

class VTK_GRAPHICS_EXPORT vtkMeshQuality : public vtkDataSetAlgorithm
{
public:
  void PrintSelf(ostream& os, vtkIndent indent);
  vtkTypeRevisionMacro(vtkMeshQuality,vtkDataSetAlgorithm);
  static vtkMeshQuality* New();

  // Description:
  // This variable controls whether or not cell quality is stored as
  // cell data in the resulting mesh or discarded (leaving only the
  // aggregate quality average of the entire mesh, recorded in the
  // FieldData).
  vtkSetMacro(SaveCellQuality,int);
  vtkGetMacro(SaveCellQuality,int);
  vtkBooleanMacro(SaveCellQuality,int);

  // Description:
  // Set/Get the particular estimator used to measure the quality of triangles.
  // The default is VTK_QUALITY_RADIUS_RATIO and valid values also include
  // VTK_QUALITY_ASPECT_RATIO, VTK_QUALITY_FROBENIUS_NORM, and VTK_QUALITY_EDGE_RATIO.
  vtkSetMacro(TriangleQualityMeasure,int);
  vtkGetMacro(TriangleQualityMeasure,int);
  void SetTriangleQualityMeasureToEdgeRatio()
    {
    this->SetTriangleQualityMeasure( VTK_QUALITY_EDGE_RATIO );
    }
  void SetTriangleQualityMeasureToAspectRatio()
    {
    this->SetTriangleQualityMeasure( VTK_QUALITY_ASPECT_RATIO );
    }
  void SetTriangleQualityMeasureToRadiusRatio()
    {
    this->SetTriangleQualityMeasure( VTK_QUALITY_RADIUS_RATIO );
    }
  void SetTriangleQualityMeasureToFrobeniusNorm()
    {
    this->SetTriangleQualityMeasure( VTK_QUALITY_FROBENIUS_NORM );
    }
  void SetTriangleQualityMeasureToMinAngle()
    {
    this->SetTriangleQualityMeasure( VTK_QUALITY_MIN_ANGLE );
    }

  // Description:
  // Set/Get the particular estimator used to measure the quality of quadrilaterals.
  // The default is VTK_QUALITY_EDGE_RATIO and valid values also include
  // VTK_QUALITY_RADIUS_RATIO and VTK_QUALITY_ASPECT_RATIO.
  // Scope: Except for VTK_QUALITY_EDGE_RATIO, these estimators are intended for planar
  // quadrilaterals only; use at your own risk if you really want to assess non-planar
  // quadrilateral quality with those.
  vtkSetMacro(QuadQualityMeasure,int);
  vtkGetMacro(QuadQualityMeasure,int);
  void SetQuadQualityMeasureToEdgeRatio()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_EDGE_RATIO );
    }
  void SetQuadQualityMeasureToAspectRatio()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_ASPECT_RATIO );
    }
  void SetQuadQualityMeasureToRadiusRatio()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_RADIUS_RATIO );
    }
  void SetQuadQualityMeasureToMedFrobeniusNorm()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_MED_FROBENIUS_NORM );
    }
  void SetQuadQualityMeasureToMaxFrobeniusNorm()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_MAX_FROBENIUS_NORM );
    }
  void SetQuadQualityMeasureToMinAngle()
    {
    this->SetQuadQualityMeasure( VTK_QUALITY_MIN_ANGLE );
    }

  // Description:
  // Set/Get the particular estimator used to measure the quality of tetrahedra.
  // The default is VTK_QUALITY_RADIUS_RATIO and valid values also include
  // VTK_QUALITY_ASPECT_RATIO, VTK_QUALITY_FROBENIUS_NORM, and VTK_QUALITY_EDGE_RATIO.
  vtkSetMacro(TetQualityMeasure,int);
  vtkGetMacro(TetQualityMeasure,int);
  void SetTetQualityMeasureToEdgeRatio()
    {
    this->SetTetQualityMeasure( VTK_QUALITY_EDGE_RATIO );
    }
  void SetTetQualityMeasureToAspectRatio()
    {
    this->SetTetQualityMeasure( VTK_QUALITY_ASPECT_RATIO );
    }
  void SetTetQualityMeasureToRadiusRatio()
    {
    this->SetTetQualityMeasure( VTK_QUALITY_RADIUS_RATIO );
    }
  void SetTetQualityMeasureToFrobeniusNorm()
    {
    this->SetTetQualityMeasure( VTK_QUALITY_FROBENIUS_NORM );
    }
  void SetTetQualityMeasureToMinAngle()
    {
    this->SetTetQualityMeasure( VTK_QUALITY_MIN_ANGLE );
    }

  // Description:
  // Set/Get the particular estimator used to measure the quality of hexahedra.
  // The default is VTK_QUALITY_RADIUS_RATIO and valid values also include
  // VTK_QUALITY_ASPECT_RATIO.
  vtkSetMacro(HexQualityMeasure,int);
  vtkGetMacro(HexQualityMeasure,int);
  void SetHexQualityMeasureToEdgeRatio()
    {
    this->SetHexQualityMeasure( VTK_QUALITY_EDGE_RATIO );
    }

  // Description:
  // This is a static function used to calculate the edge ratio of a triangle.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The edge ratio of a triangle \f$t\f$ is: 
  // \f$\frac{|t|_\infty}{|t|_0}\f$,
  // where \f$|t|_\infty\f$ and \f$|t|_0\f$ respectively denote the greatest and
  // the smallest edge lengths of \f$t\f$.
  static double TriangleEdgeRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the aspect ratio of a triangle.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The aspect ratio of a triangle \f$t\f$ is: 
  // \f$\frac{|t|_\infty}{2\sqrt{3}r}\f$,
  // where \f$|t|_\infty\f$ and \f$r\f$ respectively denote the greatest edge 
  // length and the inradius of \f$t\f$.
  static double TriangleAspectRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the radius ratio of a triangle.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The radius ratio of a triangle \f$t\f$ is: 
  // \f$\frac{R}{2r}\f$,
  // where \f$R\f$ and \f$r\f$ respectively denote the circumradius and 
  // the inradius of \f$t\f$.
  static double TriangleRadiusRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the Frobenius norm of a triangle
  // when the reference element is equilateral.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The Frobenius norm of a triangle \f$t\f$, when the reference element is 
  // equilateral, is: 
  // \f$\frac{|t|^2_2}{2\sqrt{3}{\cal A}}\f$,
  // where \f$|t|^2_2\f$ and \f$\cal A\f$ respectively denote the sum of the 
  // squared edge lengths and the area of \f$t\f$.
  static double TriangleFrobeniusNorm( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the minimal (nonoriented) angle
  // of a triangle, expressed in degrees.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  static double TriangleMinAngle( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the edge ratio of a quadrilateral.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The edge ratio of a quadrilateral \f$q\f$ is: 
  // \f$\frac{|q|_\infty}{|q|_0}\f$,
  // where \f$|q|_\infty\f$ and \f$|q|_0\f$ respectively denote the greatest and
  // the smallest edge lengths of \f$q\f$.
  static double QuadEdgeRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the aspect ratio of a planar 
  // quadrilateral.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function. Use at your own risk with nonplanar quadrilaterals.
  // The aspect ratio of a planar quadrilateral \f$q\f$ is: 
  // \f$\frac{|q|_1|q|_\infty}{4{\cal A}}\f$,
  // where \f$|q|_1\f$, $|q|_\infty\f$ and \f${\cal A}\f$ respectively denote the 
  // perimeter, the greatest edge length and the area of \f$q\f$.
  static double QuadAspectRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the radius ratio of a planar 
  // quadrilateral. The name is only used by analogy with the triangle radius 
  // ratio, because in general a quadrilateral does not have a circumcircle nor
  // an incircle. 
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function. Use at your own risk with nonplanar quadrilaterals.
  // The radius ratio of a planar quadrilateral \f$q\f$ is: 
  // \f$\frac{|q|_2h_{\max}}{\min_i{\cal A}_i}\f$,
  // where \f$|q|_2\f$, \f$h_{\max}\f$ and \f$\min{\cal A}_i\f$ respectively denote 
  // the sum of the squared edge lengths, the greatest amongst diagonal and edge 
  // lengths and the smallest area of the 4 triangles extractable from \f$q\f$.
  static double QuadRadiusRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the average Frobenius norm of the
  // 4 triangles extractable from a planar quadrilateral, when the reference 
  // triangle elements are right isosceles at the quadrangle vertices.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function. Use at your own risk with nonplanar quadrilaterals.
  // The Frobenius norm of a triangle \f$t\f$, when the reference element is 
  // right isosceles at vertex \f$V\f$, is: 
  // \f$\frac{f^2+g^2}{4{\cal A}}\f$,
  // where \f$f^2+g^2\f$ and \f$\cal A\f$ respectively denote the sum of the 
  // squared lengths of the edges attached to \f$V\f$ and the area of \f$t\f$.
  static double QuadMedFrobeniusNorm( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the maximal Frobenius norm of the
  // 4 triangles extractable from a planar quadrilateral, when the reference 
  // triangle elements are right isosceles at the quadrangle vertices.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function. Use at your own risk with nonplanar quadrilaterals.
  // The Frobenius norm of a triangle \f$t\f$, when the reference element is 
  // right isosceles at vertex \f$V\f$, is: 
  // \f$\frac{f^2+g^2}{4{\cal A}}\f$,
  // where \f$f^2+g^2\f$ and \f$\cal A\f$ respectively denote the sum of the 
  // squared lengths of the edges attached to \f$V\f$ and the area of \f$t\f$.
  static double QuadMaxFrobeniusNorm( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the minimal (nonoriented) angle
  // of a quadrilateral, expressed in degrees.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  static double QuadMinAngle( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the edge ratio of a tetrahedron.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The edge ratio of a tetrahedron \f$K\f$ is: 
  // \f$\frac{|K|_\infty}{|K|_0}\f$,
  // where \f$|K|_\infty\f$ and \f$|K|_0\f$ respectively denote the greatest and
  // the smallest edge lengths of \f$K\f$.
  static double TetEdgeRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the aspect ratio of a tetrahedron.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The aspect ratio of a tetrahedron \f$K\f$ is: 
  // \f$\frac{|K|_\infty}{2\sqrt{6}r}\f$,
  // where \f$|K|_\infty\f$ and \f$r\f$ respectively denote the greatest edge 
  // length and the inradius of \f$K\f$.
  static double TetAspectRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the radius ratio of a tetrahedron.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The radius ratio of a tetrahedron \f$K\f$ is: 
  // \f$\frac{R}{3r}\f$,
  // where \f$R\f$ and \f$r\f$ respectively denote the circumradius and 
  // the inradius of \f$K\f$.
  static double TetRadiusRatio( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the Frobenius norm of a tetrahedron
  // when the reference element is regular.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The Frobenius norm of a tetrahedron \f$K\f$, when the reference element is 
  // regular, is: 
  // \f$\frac{\frac{3}{2}(l_{11}+l_{22}+l_{33}) - (l_{12}+l_{13}+l_{23})}
  // {3(\sqrt{2}\det{T})^\frac{2}{3}}\f$,
  // where \f$T\f$ and \f$l_{ij}\f$ respectively denote the edge matrix of \f$K\f$
  // and the entries of \f$L=T^t\,T\f$.
  static double TetFrobeniusNorm( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the minimal (nonoriented) dihedral
  // angle of a tetrahedron, expressed in degrees.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  static double TetMinAngle( vtkCell* cell );

  // Description:
  // This is a static function used to calculate the edge ratio of a hexahedron.
  // It assumes that you pass the correct type of cell -- no type checking is
  // performed because this method is called from the inner loop of the Execute()
  // member function.
  // The edge ratio of a tetrahedron \f$H\f$ is: 
  // \f$\frac{|H|_\infty}{|H|_0}\f$,
  // where \f$|H|_\infty\f$ and \f$|H|_0\f$ respectively denote the greatest and
  // the smallest edge lengths of \f$H\f$.
  static double HexEdgeRatio( vtkCell* cell );

  // Description:
  // These methods are deprecated. Use Get/SetSaveCellQuality() instead.
  //
  // Formerly, SetRatio could be used to disable computation
  // of the tetrahedral radius ratio so that volume alone could be computed.
  // Now, cell quality is always computed, but you may decide not
  // to store the result for each cell.
  // This allows average cell quality of a mesh to be
  // calculated without requiring per-cell storage.
  virtual void SetRatio( int r ) { this->SetSaveCellQuality( r ); }
  int GetRatio() { return this->GetSaveCellQuality(); }
  vtkBooleanMacro(Ratio,int);

  // Description:
  // These methods are deprecated. The functionality of computing cell
  // volume is being removed until it can be computed for any 3D cell.
  // (The previous implementation only worked for tetrahedra.)
  //
  // For now, turning on the volume computation will put this
  // filter into "compatibility mode," where tetrahedral cell
  // volume is stored in first component of each output tuple and
  // the radius ratio is stored in the second component. You may
  // also use CompatibilityModeOn()/Off() to enter this mode.
  // In this mode, cells other than tetrahedra will have report
  // a volume of 0.0 (if volume computation is enabled).
  //
  // By default, volume computation is disabled and compatibility
  // mode is off, since it does not make a lot of sense for
  // meshes with non-tetrahedral cells.
  virtual void SetVolume( int cv )
    {
    if ( ! ((cv != 0) ^ (this->Volume != 0)) )
      {
      return;
      }
    this->Modified();
    this->Volume = cv;
    if ( this->Volume )
      {
      this->CompatibilityModeOn();
      }
    }
  int GetVolume()
    {
    return this->Volume;
    }
  vtkBooleanMacro(Volume,int);

  // Description:
  // CompatibilityMode governs whether, when both a quality measure
  // and cell volume are to be stored as cell data, the two values
  // are stored in a single array. When compatibility mode is off
  // (the default), two separate arrays are used -- one labeled
  // "Quality" and the other labeled "Volume".
  // When compatibility mode is on, both values are stored in a
  // single array, with volume as the first component and quality
  // as the second component.
  //
  // Enabling CompatibilityMode changes the default tetrahedral
  // quality measure to VTK_QUALITY_RADIUS_RATIO and turns volume
  // computation on. (This matches the default behavior of the
  // initial implementation of vtkMeshQuality.) You may change
  // quality measure and volume computation without leaving
  // compatibility mode.
  //
  // Disabling compatibility mode does not affect the current
  // volume computation or tetrahedral quality measure settings. 
  //
  // The final caveat to CompatibilityMode is that regardless of
  // its setting, the resulting array will be of type vtkDoubleArray
  // rather than the original vtkFloatArray.
  // This is a safety measure to keep the authors from
  // diving off of the Combinatorial Coding Cliff into
  // Certain Insanity.
  virtual void SetCompatibilityMode( int cm )
    {
    if ( !((cm != 0) ^ (this->CompatibilityMode != 0)) )
      {
      return;
      }
    this->CompatibilityMode = cm;
    this->Modified();
    if ( this->CompatibilityMode )
      {
      this->Volume = 1;
      this->TetQualityMeasure = VTK_QUALITY_RADIUS_RATIO;
      }
    }
  vtkGetMacro(CompatibilityMode,int);
  vtkBooleanMacro(CompatibilityMode,int);

protected:
  vtkMeshQuality();
  ~vtkMeshQuality();

  virtual int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  int SaveCellQuality;
  int TriangleQualityMeasure;
  int QuadQualityMeasure;
  int TetQualityMeasure;
  int HexQualityMeasure;

  int CompatibilityMode;
  int Volume;

private:
  vtkMeshQuality( const vtkMeshQuality& ); // Not implemented.
  void operator = ( const vtkMeshQuality& ); // Not implemented.
};

#endif // vtkMeshQuality_h
