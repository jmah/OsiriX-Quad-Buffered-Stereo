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


@implementation VTKView (QuadBufferedStereo)


+ (void)load
{
	QBSSwizzleInstanceMethod([self class], @selector(initWithFrame:), @selector(QBS_initWithFrame:));
}


- (id)QBS_initWithFrame:(NSRect)frame // Will be swizzled for -initWithFrame:
{
	if ([self isKindOfClass:[VRView class]])
		return [self QBS_initWithFrame:frame];
	
	switch ([[NSUserDefaults standardUserDefaults] integerForKey:QBSStereoTypeKey])
	{
		case QBSStereoTypeQuadBuffered:
			if (self = [super initWithFrame:frame])
			{
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
			break;
		default:
			self = [self QBS_initWithFrame:frame];
	}
    return self;
}


@end
