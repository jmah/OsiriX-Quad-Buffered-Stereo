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




#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>


#define STAT_UPDATE                0.6f
#define IMAGE_COUNT                1
#define IMAGE_DEPTH                32


enum
{
    tWL = 0,
    tTranslate =1,
    tZoom =2,
    tRotate =3,
    tNext =4,
    tMesure =5,
    tROI =6,
	t3DRotate =7,
	tCross = 8,
	
	// ROIs
	tOval = 9,
	tOPolygon = 10,
	tCPolygon = 11,
	tAngle = 12,
	tText = 13,
	tArrow = 14,
	tPencil = 15,
	
	t3Dpoint = 16,
	
	t3DCut = 17,
	
	tCamera3D = 18,
	
	t2DPoint = 19,
	
	tPlain = 20
};

@class DCMPix;
@class DCMView;
@class ROI;

@interface DCMView: NSOpenGLView
{
	int				_imageRows;
	int				_imageColumns;
	int				_tag;
	
	int				YearOld;
	
	ROI				*curROI;
	BOOL			drawingROI, noScale, volumicSeries;
	DCMView			*blendingView;
	float			blendingFactor, blendingFactorStart;
	BOOL			eraserFlag; // use by the PaletteController to switch between the Brush and the Eraser
	BOOL			colorTransfer;
	unsigned char   *colorBuff;
	unsigned char   alphaTable[256], redTable[256], greenTable[256], blueTable[256];
	float			redFactor, greenFactor, blueFactor;
	long			blendingMode;
	float			sliceVector[ 3], slicePoint[ 3], slicePointO[ 3], slicePointI[ 3];
	float			sliceVector2[ 3], slicePoint2[ 3], slicePointO2[ 3], slicePointI2[ 3];
	float			slicePoint3D[ 3];
	float			syncRelativeDiff;
	long			syncSeriesIndex;
	
	float			mprVector[ 3], mprPoint[ 3];
	
	short			thickSlabMode, thickSlabStacks;
	
    NSImage         *myImage;
	
    NSMutableArray  *dcmPixList;
    NSArray			*dcmFilesList;
	NSMutableArray  *dcmRoiList, *curRoiList;
    DCMPix			*curDCM;
	
    
    char            listType;
    
    short           curImage, startImage;
    
    short           currentTool, currentToolRight;
    
	NSString		*shortDateString;
	NSDictionary	*localeDictionnary;

    NSPoint         start, originStart, originOffsetStart, originOffsetRegistrationStart, previous;
    long            startWW, curWW;
    long            startWL, curWL;
    NSSize          scaleStart, scaleInit;
    
	BOOL			convolution;
	short			kernelsize, normalization;
	short			kernel[ 25];
	
    float           scaleValue, startScaleValue, scaleOffsetRegistration, scaleOffsetRegistrationStart;
    float           rotation, rotationStart, rotationOffsetRegistration, rotationOffsetRegistrationStart;
    NSPoint			origin, originOffset, originOffsetRegistration;
	NSPoint			cross, crossPrev;
	float			angle, slab, switchAngle;
	short			crossMove;
    
    NSMatrix        *matrix;
    
    long            count;
	
    BOOL            QuartzExtreme;
	
    BOOL            xFlipped, yFlipped;

	long			fontListGLSize[256];
	long			labelFontListGLSize[ 256];
	NSSize			stringSize;
	NSFont			*labelFont;
	NSFont			*fontGL;
	NSColor			*fontColor;
    GLuint          fontListGL;
	GLuint          labelFontListGL;
    
    NSPoint         mesureA, mesureB;
    NSRect          roiRect;
	NSString		*stringID;
	NSSize			previousViewSize;
	
	float			mouseXPos, mouseYPos;
	long			pixelMouseValue;
	long			pixelMouseValueR, pixelMouseValueG, pixelMouseValueB;
    
    long imageWidth; // height of orginal image
    long imageHeight; // width of orginal image
    float imageAspect; // width / height or aspect ratio of orginal image
    long imageDepth; // depth of image (after loading into gworld, will be either 32 or 16 bits)
    long textureX; // number of horizontal textures
    long textureY; // number of vertical textures
    GLuint * pTextureName; // array for texture names (# = textureX * textureY)
	GLuint * blendingTextureName; // array for texture names (# = textureX * textureY)
	GLuint * subtractedTextureName; // array for texture names (# = textureX * textureY)
    long textureWidth; // total width of texels with cover image (including any border on image, but not internal texture overlaps)
    long textureHeight; // total height of texels with cover image (including any border on image, but not internal texture overlaps)
    
	BOOL f_ext_texture_rectangle; // is texture rectangle extension supported
	BOOL f_ext_client_storage; // is client storage extension supported
	BOOL f_ext_packed_pixel; // is packed pixel extension supported
	BOOL f_ext_texture_edge_clamp; // is SGI texture edge clamp extension supported
	BOOL f_gl_texture_edge_clamp; // is OpenGL texture edge clamp support (1.2+)
	unsigned long edgeClampParam; // the param that is passed to the texturing parmeteres
	long maxTextureSize; // the minimum max texture size across all GPUs
	long maxNOPTDTextureSize; // the minimum max texture size across all GPUs that support non-power of two texture dimensions
	long TEXTRECTMODE;
	
	BOOL isKeyView; //needed for Image View subclass
	NSCursor *cursor;
	BOOL cursorSet;
}
 -(NSMutableArray*) dcmPixList;
- (long) indexForPix: (long) pixIndex; // Return the index into fileList that coresponds to the index in pixList
- (long) syncSeriesIndex;
- (void) setSyncSeriesIndex:(long) i;
- (float) syncRelativeDiff;
- (void) setSyncRelativeDiff: (float) v;
- (long) findPlaneAndPoint:(float*) pt :(float*) location;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits;
- (void) setCrossPrev:(NSPoint) c;
-(NSPoint) cross;
-(NSPoint) crossPrev;
-(void) setSlab:(float) s;
-(void) blendingPropagate;
-(void) subtract:(DCMView*) bV;
-(void) multiply:(DCMView*) bV;
-(void) setBlendingMode:(long) f;
-(GLuint *) loadTextureIn:(GLuint *) texture :(BOOL) blending;
- (void) setSubtraction:(long) imID :(NSPoint) offset;
- (void) setYFlipped:(BOOL) v;
- (BOOL) roiTool:(long) tool;
- (void) sliderAction2DMPR:(id) sender;
- (void) setStringID:(NSString*) str;
-(NSString*) stringID;
- (float) angle;
- (void) setCrossCoordinatesPer:(float) val;
- (void) setCrossCoordinates:(float) x :(float) y :(BOOL) update;
- (void) setCross:(long) x :(long)y :(BOOL) update;
- (void) setMPRAngle: (float) vectorMPR;
- (NSPoint) ConvertFromView2GL:(NSPoint) a;
- (void) cross3D:(float*) x :(float*) y :(float*) z;
- (void) setWLWW:(long) wl :(long) ww;
- (void) getWLWW:(long*) wl :(long*) ww;
- (void) setConv:(short*) matrix :(short) size :(short) norm;
- (void) setCLUT:( unsigned char*) r :(unsigned char*) g :(unsigned char*) b;
- (void) setCurrentTool:(short)i;
- (short) currentTool;
- (short) currentToolRight;
- (void) setRightTool:(short) i;
- (void) dealloc;
- (NSImage*) nsimage:(BOOL) originalSize;
- (void) setTheMatrix:(NSMatrix*)m;
- (void) setIndex:(short) index;
- (void) setIndexWithReset:(short) index :(BOOL)sizeToFit;
- (void) setDCM:(NSMutableArray*) c :(NSArray*)d :(NSMutableArray*)e :(short) firstImage :(char) type :(BOOL) reset;
- (short) curImage;
- (void) sendSyncMessage:(short) inc;
- (void) setQuartzExtreme:(BOOL) set;
- (void) loadTextures;
- (void) flipVertical:(id) sender;
- (void) flipHorizontal:(id) sender;
- (void) setFusion:(short) mode :(short) stacks;
- (void) FindMinimumOpenGLCapabilities;
- (float) scaleValue;
- (float) scaleOffsetRegistration;
- (void) setScaleValue:(float) x;
- (void) setScaleOffsetRegistration:(float) x;
- (float) rotation;
- (float) rotationOffsetRegistration;
- (void) setRotation:(float) x;
- (void) setRotationOffsetRegistration:(float) x;
-(NSPoint) rotatePoint:(NSPoint) a;
- (NSPoint) origin;
- (NSPoint) originOffset;
- (NSPoint) originOffsetRegistration;
- (void) setOrigin:(NSPoint) x;
- (void) setOriginOffset:(NSPoint) x;
- (void) setOriginOffsetRegistration:(NSPoint) x;
- (void) setBlending:(DCMView*) bV;
- (float) pixelSpacing;
- (void) scaleToFit;
- (void) setBlendingFactor:(float) f;
- (void) sliderAction:(id) sender;
- (DCMPix*)curDCM;
- (void) roiSet;
-(void) roiSet:(ROI*) aRoi;
- (void) colorTables:(unsigned char **) a :(unsigned char **) r :(unsigned char **)g :(unsigned char **) b;
- (void )changeFont:(id)sender;
- (NSSize)sizeOfString:(NSString *)string forFont:(NSFont *)font;
- (long) lengthOfString:( char *) cstr forFont:(long *)fontSizeArray;
- (void) getCrossCoordinates:(float*) x: (float*) y;
- (IBAction) sliderRGBFactor:(id) sender;
- (IBAction) alwaysSyncMenu:(id) sender;
- (void) getCLUT:( unsigned char**) r : (unsigned char**) g : (unsigned char**) b;
-(void) doSyncronize:(NSNotification*)note;
-(BOOL) volumicSeries;
- (id)initWithFrame:(NSRect)frame imageRows:(int)rows  imageColumns:(int)columns;
- (BOOL)hasSUV;
- (float)getSUV;
- (IBAction) roiLoadFromXMLFiles: (id) sender;
- (float)mouseXPos;
- (float)mouseYPos;
+ (void)setPluginOverridesMouse: (BOOL)override;
- (GLuint)fontListGL;
- (void) DrawCStringGL: ( char *) cstrOut :(GLuint) fontL :(long) x :(long) y;
- (void) setSyncro:(long) s;
- (long) syncro;
- (NSFont*)fontGL;

//notifications
-(void) updateCurrentImage: (NSNotification*) note;
-(void)updateImageTiling:(NSNotification *)note;
-(void)setImageParamatersFromView:(DCMView *)aView;
-(void) setRows:(int)rows columns:(int)columns;
-(void)setTag:(int)aTag;
-(int)tag;
-(long)curWW;
-(long)curWL;
-(float)scaleValue;
-(BOOL)xFlipped;
-(BOOL)yFlipped;
-(NSPoint)origin;
- (int)rows;
- (int)columns;
-(DCMView *)blendingView;
- (float)blendingFactor;
- (float)blendingMode;
- (NSCursor *)cursor;
- (void)setCursor:(NSCursor *)aCursor;
-(void) becomeMainWindow;
- (BOOL)eraserFlag;
- (void)setEraserFlag: (BOOL)aFlag;
- (NSManagedObject *)imageObj;
- (NSManagedObject *)seriesObj;
- (void)updatePresentationStateFromSeries;
- (void) setXFlipped:(BOOL) v;
- (void) subDrawRect:(NSRect)aRect;
- (IBAction)resetSeriesPresentationState:(id)sender;
- (IBAction)resetImagePresentationState:(id)sender;

@end
