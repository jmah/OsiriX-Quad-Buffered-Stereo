/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkVolumeProVP1000Mapper.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkVolumeProVP1000Mapper - Superclass for VP1000 board
//
// .SECTION Description
// vtkVolumeProVP1000Mapper is the superclass for VolumePRO volume rendering 
// mappers based on the VP1000 chip. Subclasses are for underlying graphics 
// languages. Users should not create subclasses directly - 
// a vtkVolumeProMapper will automatically create the object of the right 
// type.
//
// This class is not included in the Rendering CMakeLists by default. If you
// want to add this class to your vtk build, you need to have the vli header
// and library files, and you will need to perform the following steps:
//
// 1. Run cmake, and set the VTK_USE_VOLUMEPRO flag to true.
// 2. If the libary file (VLI_LIBRARY_FOR_VP1000) is not found by cmake, set
//    the path to that file, and rerun cmake.
// 3. If the header file (VLI_INCLUDE_PATH_FOR_VP1000) is not found by cmake,
//    set the path to that file, and rerun cmake.
// 4. Rebuild VTK.
//
// For more information on the VolumePRO hardware, please see:
//
//   http://www.terarecon.com/products/volumepro_prod.html
//
// If you encounter any problems with this class, please inform Kitware, Inc.
// at kitware@kitware.com.
//
//
// .SECTION See Also
// vtkVolumeMapper vtkVolumeProMapper vtkOpenGLVolumeProVP1000Mapper
//

#ifndef __vtkVolumeProVP1000Mapper_h
#define __vtkVolumeProVP1000Mapper_h

#include "vtkVolumeProMapper.h"
#include "vli.h"

#ifdef _WIN32
#include "VolumePro1000/inc/vli.h" // Needed for VLI internal types
#else
#include "vli.h" // Needed for VLI internal types
#endif

#define VTK_VOLUME_16BIT 3
#define VTK_VOLUME_32BIT 4

class VTK_EXPORT vtkVolumeProVP1000Mapper : public vtkVolumeProMapper
{
public:
  vtkTypeRevisionMacro(vtkVolumeProVP1000Mapper,vtkVolumeProMapper);
  static vtkVolumeProVP1000Mapper *New();
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Render the image using the hardware and place it in the frame buffer
  virtual void Render( vtkRenderer *, vtkVolume * );
  virtual int GetAvailableBoardMemory();
  virtual void GetLockSizesForBoardMemory(unsigned int type,
                                          unsigned int *xSize,
                                          unsigned int *ySize,
                                          unsigned int *zSize);
  

  vtkVolumeProVP1000Mapper();
  ~vtkVolumeProVP1000Mapper();

	void VolumeChanged(vtkRenderer *, vtkVolume * );

  // Update the camera - set the camera matrix
  void UpdateCamera( vtkRenderer *, vtkVolume * );

  // Update the lights
  void UpdateLights( vtkRenderer *, vtkVolume * );

  // Update the properties of the volume including transfer functions
  // and material properties
  void UpdateProperties( vtkRenderer *, vtkVolume * );

  // Update the volume - create it if necessary
  // Set the volume matrix.
  void UpdateVolume( vtkRenderer *, vtkVolume * );

  // Set the crop box (as defined in the vtkVolumeMapper superclass)
  void UpdateCropping( vtkRenderer *, vtkVolume * );

  // Set the cursor
  void UpdateCursor( vtkRenderer *, vtkVolume * );

  // Update the cut plane
  void UpdateCutPlane( vtkRenderer *, vtkVolume * );

  VLIContext* GetContextPointer();

	void SetMaxWindow( long m);
	void SetRenderFlag( long m);

  void SetLookUpTable( long start, long end, unsigned char	*r, unsigned char	*g, unsigned char	*b, unsigned short *o, vtkRenderer *ren, vtkVolume *vol);

  void SetShading(vtkRenderer *ren, vtkVolume *vol);

protected:

  // Render the image buffer to the screen
  // Defined in the specific graphics implementation.
  virtual void RenderImageBuffer( vtkRenderer  * vtkNotUsed(ren),
                                  vtkVolume    * vol,
                                  int          size[2],
                                  unsigned int * outData )
    {(void)vol; (void)size; (void)outData;}

  // Render a bounding box of the volume because the texture map would
  // be too large.
  virtual void RenderBoundingBox( vtkRenderer * vtkNotUsed(ren),
                                  vtkVolume   * vol )
    {(void)vol;}

  // Get the depth buffer values
  virtual void GetDepthBufferValues( vtkRenderer *vtkNotUsed(ren),
                                     int size[2],
                                     unsigned int *outData )
    { (void)outData; }

//#if ((VTK_MAJOR_VERSION == 3)&&(VTK_MINOR_VERSION == 2))
//  vtkGetVectorMacro( VoxelCroppingRegionPlanes, double, 6 );
//  void ConvertCroppingRegionPlanesToVoxels();
//  double                VoxelCroppingRegionPlanes[6];
//#endif

  
  // Keep track of the size of the data loaded so we know if we can
  // simply update when a change occurs or if we need to release and
  // create again
  int LoadedDataSize[3];

  long maxWindow;
  unsigned int *outData;
  int outDataSize[ 2];
  int renderFlag;
   
  VLIImageBuffer *ImageBuffer;
  VLIDepthBuffer *DepthBuffer;
  
  VLIStatus CheckSubSampling(const VLIVolume *inVolume,
                             const VLIContext *inContext,
                             int &outImageWidth, int &outImageHeight);
  
  int DrawBoundingBox;

private:
  vtkVolumeProVP1000Mapper(const vtkVolumeProVP1000Mapper&); // Not implemented
  void operator=(const vtkVolumeProVP1000Mapper&); // Not implemented
};



#endif



