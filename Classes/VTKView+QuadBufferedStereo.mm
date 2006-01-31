//
//  VTKView+QuadBufferedStereo.mm
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "VTKView+QuadBufferedStereo.h"
#import "NSOpenGLPixelFormat+QuadBufferedStereo.h"
#import "QBSSwizzleMethod.h"
#import "QBSController.h"
#import "VRView.h"

#define id Id
#include "vtkInteractorStyleTrackballCamera.h"
#undef id


typedef struct _QBSClassNode {
	Class klass;
	struct _QBSClassNode *next;
} QBSClassNode;

static QBSClassNode *registeredClasses = NULL;


@implementation VTKView (QuadBufferedStereo)

#pragma mark Initialization and Deallocation

+ (void)load
{
	QBSSwizzleInstanceMethod([self class], @selector(initWithFrame:), @selector(QBS_initWithFrame:));
}


- (id)QBS_initWithFrame:(NSRect)frame // Will be swizzled for -initWithFrame:
{
	BOOL matchingClass = NO;
	QBSClassNode *currClassNode = registeredClasses;
	while (!matchingClass && currClassNode)
		if ([self isKindOfClass:currClassNode->klass])
			matchingClass = YES;
		else
			currClassNode = currClassNode->next;
	
	BOOL enableQuadBufferedStereo = NO;
	if (matchingClass && ([[NSUserDefaults standardUserDefaults] integerForKey:QBSStereoTypeKey] == QBSStereoTypeQuadBuffered))
		enableQuadBufferedStereo = YES;
	
	if (enableQuadBufferedStereo)
	{
		if (self = [super initWithFrame:frame])
		{
#warning Direct ivar access
			_renderer = vtkRenderer::New();
			
			[NSOpenGLPixelFormat QBS_forceStereo:YES]; // Force the OpenGL context to be created in stereo
			_cocoaRenderWindow = vtkCocoaRenderWindow::New();
			_cocoaRenderWindow->StereoCapableWindowOn(); // Yes! Do this before the window ID is set
			_cocoaRenderWindow->SetWindowId([self window]);
			_cocoaRenderWindow->SetDisplayId(self);
			
			_cocoaRenderWindow->AddRenderer(_renderer);
			_interactor = vtkCocoaRenderWindowInteractor::New();
			_interactor->SetRenderWindow(_cocoaRenderWindow);
			
			vtkInteractorStyle *interactorStyle;
			interactorStyle = vtkInteractorStyleTrackballCamera::New();
			_interactor->SetInteractorStyle(interactorStyle);
			interactorStyle->Delete();
			
			[self setVTKRenderWindow:_cocoaRenderWindow];
			
			_interactor->Initialize();
			
			[NSOpenGLPixelFormat QBS_forceStereo:NO];
			
			[self renderWindow]->StereoRenderOn();
			[self renderWindow]->SetStereoTypeToCrystalEyes(); // Quad-Buffered!
			
			// Set display in stereo mode once we know what screen we're on (next run loop cycle)
			[NSTimer scheduledTimerWithTimeInterval:0
			                                 target:[QBSController sharedController]
			                               selector:@selector(setUpScreenForStereo:)
			                               userInfo:self
			                                repeats:NO];
		}
	}
	else
		self = [self QBS_initWithFrame:frame];
	
    return self;
}



#pragma mark Stereo Registration

+ (void)QBS_registerClassForStereo:(Class)klass
{
	QBSClassNode *newNode = (QBSClassNode *)malloc(sizeof(QBSClassNode));
	newNode->klass = klass;
	newNode->next = registeredClasses;
	registeredClasses = newNode;
}


@end
