/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - GPL
  
  See http://homepage.mac.com/rossetantoine/osirix/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/




#import <AppKit/AppKit.h>
#import "VTKView.h"
#import "DCMPix.h"
#import "Camera.h"

#ifdef __cplusplus
#define id Id
#include "vtkCommand.h"
#include "vtkProperty.h"
#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume16Reader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkImageReader.h"
#include "vtkImageImport.h"
#include "vtkCamera.h"
#include "vtkStripper.h"
#include "vtkLookupTable.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkImageData.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkLight.h"

#include "vtkPlane.h"
#include "vtkPlanes.h"
#include "vtkPlaneSource.h"
#include "vtkBoxWidget.h"
#include "vtkPlaneWidget.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolumeRayCastMIPFunction.h"

#include "vtkTransform.h"
#include "vtkSphere.h"
#include "vtkImplicitBoolean.h"
#include "vtkExtractGeometry.h"
#include "vtkDataSetMapper.h"
#include "vtkPicker.h"
#include "vtkCellPicker.h"
#include "vtkPointPicker.h"
#include "vtkLineSource.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkActor2D.h"
#include "vtkExtractPolyDataGeometry.h"
#include "vtkProbeFilter.h"
#include "vtkCutter.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkXYPlotActor.h"
#include "vtkClipPolyData.h"
#include "vtkBox.h"
#include "vtkCallbackCommand.h"
#include "vtkImageResample.h"
#include "vtkDecimatePro.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkImageFlip.h"
#include "vtkTextActor.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkTextProperty.h"
#undef id

class vtkMyCallback;

#else
typedef char* vtkTransform;
typedef char* vtkImageActor;
typedef char* vtkImageMapToColors;
typedef char* vtkLookupTable;
typedef char* vtkImageReslice;
typedef char* vtkImageImport;
typedef char* vtkCamera;
typedef char* vtkActor;
typedef char* vtkPolyDataMapper;
typedef char* vtkOutlineFilter;
typedef char* vtkLineWidget;

typedef char* vtkTextActor;
typedef char* vtkVolumeRayCastMapper;
typedef char* vtkVolumeRayCastMIPFunction;
typedef char* vtkVolume;


typedef char* vtkPiecewiseFunction;
typedef char* vtkVolumeTextureMapper2D;
typedef char* vtkPolyData;
typedef char* vtkVolumeProperty;
typedef char* vtkPolyDataMapper2D;

typedef char* vtkColorTransferFunction;
typedef char* vtkActor2D;
typedef char* vtkMyCallback;
typedef char* vtkPlaneWidget;
typedef char* vtkBoxWidget;
typedef char* vtkImageFlip;
typedef char* vtkImageResample;
typedef char* vtkMatrix4x4;
typedef char* vtkDecimatePro;
typedef char* vtkSmoothPolyDataFilter;
typedef char* vtkContourFilter;
typedef char* vtkPolyDataNormals;
#endif

#include <Accelerate/Accelerate.h>
#import "ViewerController.h"
#import "WaitRendering.h"

@class Camera;
@class SRController;

@interface SRView : VTKView
{
    NSMutableArray				*blendingPixList;
    DCMPix						*blendingLastObject, *blendingFirstObject;
    float						*blendingData, blendingFactor;
	ViewerController			*blendingController;
	vtkImageImport				*blendingReader;
	vtkImageFlip				*flip, *blendingFlip;
	
	vtkTextActor				*textX;
	vtkTextActor				*oText[ 4];
	
    NSMutableArray				*pixList;
    DCMPix						*firstObject;
    float						*data, *dataFRGB;
    short						currentTool;
	float						cosines[ 9];
	float						blendingcosines[ 9];

	IBOutlet NSWindow			*export3DWindow;
	IBOutlet NSSlider			*framesSlider;
	IBOutlet NSMatrix			*rotation;
	
	IBOutlet NSWindow			*export3DVRWindow;
	IBOutlet NSMatrix			*VRFrames;
	double						camPosition[ 3];
	double						camFocal[ 3];
	
	long						numberOfFrames;
	float						rotationValue;
	
    vtkRenderer					*aRenderer;
    vtkCamera					*aCamera;

    vtkActor					*outlineRect;
    vtkPolyDataMapper			*mapOutline;
    vtkOutlineFilter			*outlineData;
	
	vtkImageImport				*reader;
	
	BOOL						noWaitDialog;
	WaitRendering				*splash;
	
	vtkImageResample			*isoResample;
	vtkDecimatePro				*isoDeci[ 2];
	vtkSmoothPolyDataFilter		*isoSmoother[ 2];
	vtkContourFilter			*isoExtractor [ 2];
	vtkPolyDataNormals			*isoNormals [ 2];
	vtkPolyDataMapper			*isoMapper [ 2];
	vtkActor					*iso [ 2];

	vtkImageResample			*BisoResample;
	vtkDecimatePro				*BisoDeci[ 2];
	vtkSmoothPolyDataFilter		*BisoSmoother[ 2];
	vtkContourFilter			*BisoExtractor [ 2];
	vtkPolyDataNormals			*BisoNormals [ 2];
	vtkPolyDataMapper			*BisoMapper [ 2];
	vtkActor					*Biso [ 2];
	
	vtkMatrix4x4				*matrice;
	vtkMatrix4x4				*matriceBlending;
	vtkOrientationMarkerWidget	*orientationWidget;
	
	NSDate						*startRenderingTime;
	
	NSMutableArray				*point3DActorArray;
	NSMutableArray				*point3DPositionsArray;
	NSMutableArray				*point3DRadiusArray;
	NSMutableArray				*point3DColorsArray;
	BOOL						display3DPoints;
	IBOutlet NSPanel			*point3DInfoPanel;
	IBOutlet NSSlider			*point3DRadiusSlider;
	IBOutlet NSColorWell		*point3DColorWell;
	IBOutlet NSButton			*point3DPropagateToAll, *point3DSetDefault;
	IBOutlet SRController		*controller;
	float						point3DDefaultRadius, point3DDefaultColorRed, point3DDefaultColorGreen, point3DDefaultColorBlue, point3DDefaultColorAlpha;
}

-(unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits;
-(NSDate*) startRenderingTime;
-(void) newStartRenderingTime;
-(void) runRendering;
-(void) startRendering;
-(void) stopRendering;
-(void) setCurrentTool:(short) i;
-(id) initWithFrame:(NSRect)frame;
-(short) setPixSource:(NSMutableArray*)pix :(float*) volumeData;
-(void) dealloc;
-(void) setBlendingPixSource:(ViewerController*) bC;
-(void) changeActor:(long) actor :(float) resolution :(float) transparency :(float) r :(float) g :(float) b :(float) isocontour;
-(void) deleteActor:(long) actor;
-(void) BchangeActor:(long) actor :(float) resolution :(float) transparency :(float) r :(float) g :(float) b :(float) isocontour;
-(void) BdeleteActor:(long) actor;
-(IBAction) endQuicktimeSettings:(id) sender;
-(IBAction) exportQuicktime :(id) sender;
-(IBAction) endQuicktimeVRSettings:(id) sender;
-(float) rotation;
-(float) numberOfFrames;
-(void) Azimuth:(float) z;
-(NSImage*) nsimageQuicktime;
-(NSImage*) nsimage:(BOOL) q;
-(IBAction) export3DFileFormat :(id) sender;
-(IBAction) SwitchStereoMode :(id) sender;
- (void) setCamera: (Camera*) cam;
- (Camera*) camera;
-(void) switchOrientationWidget:(id) sender;
- (void) computeOrientationText;
- (void) getOrientation: (float*) o;

// 3D Points
- (void) add3DPoint: (double) x : (double) y : (double) z : (float) radius : (float) r : (float) g : (float) b;
- (void) add3DPoint: (double) x : (double) y : (double) z;
- (void) add3DPointActor: (vtkActor*) actor;
- (void) addRandomPoints: (int) n : (int) r;
- (void) throw3DPointOnSurface: (double) x : (double) y;
- (void) setDisplay3DPoints: (BOOL) on;
- (void) toggleDisplay3DPoints;
- (BOOL) isAny3DPointSelected;
- (unsigned int) selected3DPointIndex;
- (void) unselectAllActors;
- (void) remove3DPointAtIndex: (unsigned int) index;
- (void) removeSelected3DPoint;
- (IBAction) IBSetSelected3DPointColor: (id) sender;
- (IBAction) IBSetSelected3DPointRadius: (id) sender;
- (IBAction) IBPropagate3DPointsSettings: (id) sender;
- (void) setSelected3DPointColor: (NSColor*) color;
- (void) setAll3DPointsColor: (NSColor*) color;
- (void) set3DPointAtIndex:(unsigned int) index Color: (NSColor*) color;
- (void) setSelected3DPointRadius: (float) radius;
- (void) setAll3DPointsRadius: (float) radius;
- (void) set3DPointAtIndex:(unsigned int) index Radius: (float) radius;
- (IBAction) save3DPointsDefaultProperties: (id) sender;
- (void) load3DPointsDefaultProperties;
- (void) convert3Dto2Dpoint:(float*) pt3D :(float*) pt2D;
@end
