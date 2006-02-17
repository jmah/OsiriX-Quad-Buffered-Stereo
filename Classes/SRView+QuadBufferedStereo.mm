//
//  SRView+QuadBufferedStereo.mm
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "SRView+QuadBufferedStereo.h"
#import "VTKView+QuadBufferedStereo.h"
#import "QBSController.h"
#import "QBSSwizzleMethod.h"


static NSMutableDictionary *ivarMapping = nil; // Keys are NSValue objects with pointer values


@implementation SRView (QuadBufferedStereo)

#pragma mark Initialization and Deallocation

+ (void)load
{
	QBSSwizzleInstanceMethod([self class], @selector(dealloc), @selector(QBS_dealloc));
	QBSSwizzleInstanceMethod([self class], @selector(nsimage:), @selector(QBS_nsimage:));
}


+ (void)initialize
{
	[VTKView QBS_registerClassForStereo:[self class]];
	ivarMapping = [[NSMutableDictionary alloc] init];
}


- (void)awakeFromNib
{
	// Switch into stereo mode if need be
	if (([self renderWindow]->GetStereoRender() == false) &&
	    [[NSUserDefaults standardUserDefaults] boolForKey:QBSEnableStereoKey])
		[self SwitchStereoMode:nil];
}


- (void)QBS_dealloc // Will be swizzled for -dealloc
{
	[ivarMapping removeObjectForKey:[NSValue valueWithPointer:self]];
	[self QBS_dealloc];
}



#pragma mark Stereo

- (IBAction)SwitchStereoMode:(id)sender // Override SRView
{
	if ([[NSApp currentEvent] modifierFlags] & NSShiftKeyMask)
		[[QBSController sharedController] showSettingsPanel:self];
	else
	{
		if ([self renderWindow]->GetStereoType() == VTK_STEREO_CRYSTAL_EYES)
			// If we're already in quad-buffered mode, don't switch out of it
			[[QBSController sharedController] beginQuadBufferedAlertSheet:self];
		else
		{
			switch ([[NSUserDefaults standardUserDefaults] integerForKey:QBSStereoTypeKey])
			{
				case QBSStereoTypeQuadBuffered:
					[[QBSController sharedController] beginQuadBufferedAlertSheet:self];
					break;
				
				case QBSStereoTypeRedBlue:
					if([self renderWindow]->GetStereoRender() == false)
					{
#warning Direct ivar access
						orientationWidget->Off();
						
						[self renderWindow]->StereoRenderOn();
						[self renderWindow]->SetStereoTypeToRedBlue();
					}
					else
					{
						[self renderWindow]->StereoRenderOff();
						orientationWidget->On();
					}
					
					[self setNeedsDisplay:YES];
					break;
				
				case QBSStereoTypeInterlaced:
					if( [self renderWindow]->GetStereoRender() == false)
					{
						orientationWidget->Off();
						
						[self renderWindow]->StereoRenderOn();
						[self renderWindow]->SetStereoTypeToInterlaced();
					}
					else
					{
						[self renderWindow]->StereoRenderOff();
						orientationWidget->On();
					}
					
					[self setNeedsDisplay:YES];
					break;
			}
		}
	}
}



#pragma mark Image Capture

- (void)QBS_setImageCaptureBufferToLeft
{
	NSMutableDictionary *ivarDict = [ivarMapping objectForKey:[NSValue valueWithPointer:self]];
	if (!ivarDict)
	{
		ivarDict = [NSMutableDictionary dictionary];
		[ivarMapping setObject:ivarDict forKey:[NSValue valueWithPointer:self]];
	}
	
	[ivarDict setObject:@"Left" forKey:@"currImageCaptureBuffer"];
}


- (void)QBS_setImageCaptureBufferToRight
{
	NSMutableDictionary *ivarDict = [ivarMapping objectForKey:[NSValue valueWithPointer:self]];
	if (!ivarDict)
	{
		ivarDict = [NSMutableDictionary dictionary];
		[ivarMapping setObject:ivarDict forKey:[NSValue valueWithPointer:self]];
	}
	
	[ivarDict setObject:@"Right" forKey:@"currImageCaptureBuffer"];
}


- (NSImage *)QBS_nsimage:(BOOL)originalSize // Will be swizzled for -nsimage:
{
	NSString *bufferString = nil;
	NSMutableDictionary *ivarDict = [ivarMapping objectForKey:[NSValue valueWithPointer:self]];
	if (ivarDict)
		bufferString = [ivarDict objectForKey:@"currImageCaptureBuffer"];
	
	vtkRenderWindow *renderWindow = [self getVTKRenderWindow];
	if (renderWindow->GetStereoRender() && (renderWindow->GetStereoType() == VTK_STEREO_CRYSTAL_EYES) && bufferString)
	{
		renderWindow->MakeCurrent();
		if ([bufferString isEqualToString:@"Left"])
			glReadBuffer(GL_FRONT_LEFT);
		else if ([bufferString isEqualToString:@"Right"])
			glReadBuffer(GL_FRONT_RIGHT);
	}
	
	return [self QBS_nsimage:YES];
}


@end
