//
//  FlyThruController+QuadBufferedStereo.mm
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-01-25.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "FlyThruController+QuadBufferedStereo.h"
#import "QBSSwizzleMethod.h"
#import "QBSController.h"
#import "VTKView.h"


// Suppress warnings
@interface VTKView (QBSStereoCapture)

#pragma mark Image Capture
- (void)QBS_setImageCaptureBufferToLeft;
- (void)QBS_setImageCaptureBufferToRight;

@end


@implementation FlyThruController (QuadBufferedStereo)

#pragma mark Initialization and Deallocation

+ (void)load
{
	QBSSwizzleInstanceMethod([self class], @selector(flyThruQuicktimeExport:), @selector(QBS_flyThruQuicktimeExport:));
}



#pragma mark QuickTime Export

- (IBAction)QBS_flyThruQuicktimeExport:(id)sender // Will be swizzled for -flyThruQuicktimeExport:
{
	BOOL handledExport = NO;
	
#warning Direct ivar access
	if ([[exportFormat selectedCell] tag] == 0) // QuickTime Export
	{
		BOOL exportStereo = [[NSUserDefaults standardUserDefaults] boolForKey:QBSExportQuickTimeInStereoKey];
		
		if ([[NSUserDefaults standardUserDefaults] boolForKey:QBSAskExportQuickTimeInStereoKey])
		{
			handledExport = YES;
			NSBundle *myBundle = [NSBundle bundleForClass:[self class]];
			NSString *stereoButtonTitle = NSLocalizedStringFromTableInBundle(@"Stereo", nil, myBundle, @"Ask to export stereo alert sheet stereo button title");
			NSString *monoButtonTitle = NSLocalizedStringFromTableInBundle(@"Mono", nil, myBundle, @"Ask to export stereo alert sheet mono button title");
			NSString *defaultButtonTitle = (exportStereo ? stereoButtonTitle : monoButtonTitle);
			NSString *otherButtonTitle = (exportStereo ? monoButtonTitle : stereoButtonTitle);
			
			NSBeginAlertSheet(NSLocalizedStringFromTableInBundle(@"Export Stereo QuickTime Movie", nil, myBundle, @"Ask to export stereo alert sheet title"),
			                  defaultButtonTitle, // defaultButton
			                  NSLocalizedStringFromTableInBundle(@"Open Settings", nil, myBundle, @"Ask to export stereo alert sheet open settings button title"),
			                  otherButtonTitle, // otherButton
			                  [NSApp mainWindow], // docWindow
			                  self, // modalDelegate
			                  NULL, // didEndSelector
			                  @selector(QBS_flyThruAskQuicktimeExportStereoAlertDidEnd:returnCode:contextInfo:), //didDismissSelector
			                  sender, // contextInfo
			                  NSLocalizedStringFromTableInBundle(@"Would you like the exported QuickTime movie to be in stereo? A separate movie will be created for the left and right eyes.", nil, myBundle, @"Ask to export stereo alert sheet message"));
		}
		else if (exportStereo)
		{
			handledExport = YES;
			[self QBS_flyThruQuicktimeExportStereo:sender];
		}
	}
	
	if (!handledExport)
		[self QBS_flyThruQuicktimeExport:sender];
}


- (IBAction)QBS_flyThruQuicktimeExportStereo:(id)sender
{
	NSString *baseName = [[[[self window3DController] fileList] objectAtIndex:0] valueForKeyPath:@"series.study.name"];
	NSString *leftName = [NSString stringWithFormat:@"%@ - Left", baseName];
	NSString *rightName = [NSString stringWithFormat:@"%@ - Right", baseName];
	VTKView *vtkView = [[self window3DController] view];
	vtkRenderWindow *renderWindow = [vtkView renderWindow];
	
	Boolean oldStereoOn = renderWindow->GetStereoRender();
	int oldStereoType = renderWindow->GetStereoType();
	
	// Left movie
	if (oldStereoOn && (oldStereoType == VTK_STEREO_CRYSTAL_EYES) && [vtkView respondsToSelector:@selector(QBS_setImageCaptureBufferToLeft)])
		[vtkView QBS_setImageCaptureBufferToLeft];
	else
	{
		renderWindow->SetStereoRender(true);
		renderWindow->SetStereoTypeToLeft();
	}
	
	QuicktimeExport *leftMov = [[QuicktimeExport alloc] initWithSelector:self
	                                                                    :@selector(imageForFrame:maxFrame:)
	                                                                    :[FT numberOfFrames]];
	[leftMov generateMovie:YES
	                      :[[[self window3DController] view] bounds]
	                      :NO
	                      :leftName];
	[leftMov release];
	
	
	// Right movie
	if (oldStereoOn && (oldStereoType == VTK_STEREO_CRYSTAL_EYES) && [vtkView respondsToSelector:@selector(QBS_setImageCaptureBufferToRight)])
		[vtkView QBS_setImageCaptureBufferToRight];
	else
	{
		renderWindow->SetStereoRender(true);
		renderWindow->SetStereoTypeToRight();
	}
	
	QuicktimeExport *rightMov = [[QuicktimeExport alloc] initWithSelector:self
	                                                                     :@selector(imageForFrame:maxFrame:)
	                                                                     :[FT numberOfFrames]];
	[rightMov generateMovie:YES
	                       :[[[self window3DController] view] bounds]
	                       :NO
	                       :rightName];
	[rightMov release];
	
	
	// Reset window
	renderWindow->SetStereoRender(oldStereoOn);
	renderWindow->SetStereoType(oldStereoType);
}


- (void)QBS_flyThruAskQuicktimeExportStereoAlertDidEnd:(NSWindow *)alertSheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	if (returnCode == NSAlertAlternateReturn)
		[[QBSController sharedController] showSettingsPanel:nil];
	else
	{
		if ((returnCode == NSAlertDefaultReturn) == [[NSUserDefaults standardUserDefaults] boolForKey:QBSExportQuickTimeInStereoKey])
			[self QBS_flyThruQuicktimeExportStereo:(id)contextInfo];
		else
			[self QBS_flyThruQuicktimeExport:(id)contextInfo];
	}
}


@end
