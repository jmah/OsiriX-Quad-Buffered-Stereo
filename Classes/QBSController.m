//
//  QBSController.m
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-09.
//  Copyright (c) 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "QBSController.h"


@interface QBSController (QBSPrivateMethods)

- (void)quadBufferedAlertSheetDidDismiss:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;

@end


@implementation QBSController

#pragma mark Convenience Methods

+ (id)sharedController
{
	static QBSController *sharedController = nil;
	if (!sharedController)
		sharedController = [[QBSController alloc] init];
	return sharedController;
}



#pragma mark Initialization and Deallocation

- (void)awakeFromNib
{
	NSBundle *myBundle = [NSBundle bundleForClass:[self class]];
	NSString *creditsPath = [myBundle pathForResource:@"Credits" ofType:@"rtf"];
	NSData *creditsRTFData = [NSData dataWithContentsOfFile:creditsPath];
	if (creditsRTFData)
	{
		NSAttributedString *creditsAttrString = [[NSAttributedString alloc] initWithRTF:creditsRTFData documentAttributes:NULL];
		[[creditsTextView textStorage] setAttributedString:creditsAttrString];
		[creditsAttrString release];
	}
}



#pragma mark Utility Methods

- (void)registerUserDefaults
{
	NSDictionary *regDefaults = [NSDictionary dictionaryWithObjectsAndKeys:
		[NSNumber numberWithUnsignedInt:QBSStereoTypeRedBlue], QBSStereoTypeKey,
		[NSNumber numberWithBool:YES], QBSForceBlueLineSyncKey,
		[NSNumber numberWithBool:NO], QBSExportQuickTimeInStereoKey,
		[NSNumber numberWithBool:YES], QBSAskExportQuickTimeInStereoKey,
		nil];
	[[NSUserDefaults standardUserDefaults] registerDefaults:regDefaults];
}


- (void)setUpScreenForStereo:(NSTimer *)timer // userInfo is an NSView
{
	boolean_t forceBlueLineSync = ([[NSUserDefaults standardUserDefaults] boolForKey:QBSForceBlueLineSyncKey] ? true : false);
	
	CGDirectDisplayID currDisplay = (CGDirectDisplayID)[[[[[[timer userInfo] window] screen] deviceDescription] objectForKey:@"NSScreenNumber"] pointerValue];
	CGDisplayConfigRef confRef;
	CGBeginDisplayConfiguration(&confRef);
	CGConfigureDisplayStereoOperation(confRef, currDisplay, true, forceBlueLineSync);
	CGCompleteDisplayConfiguration(confRef, kCGConfigureForAppOnly);
}



#pragma mark User Interface

- (IBAction)showSettingsPanel:(id)sender
{
	if (!settingsPanel)
	{
		[NSBundle loadNibNamed:@"QBSSettings" owner:self];
		[settingsPanel center];
	}
	[settingsPanel makeKeyAndOrderFront:self];
}


- (IBAction)beginQuadBufferedAlertSheet:(id)sender
{
	static NSBundle *myBundle = nil;
	if (!myBundle)
		myBundle = [NSBundle bundleForClass:[self class]];
	NSBeginAlertSheet(NSLocalizedStringFromTableInBundle(@"Quad-Buffered Stereo Cannot Be Switched", nil, myBundle, @"Quad-buffered alert sheet title"),
	                  nil, // defaultButton: OK
	                  NSLocalizedStringFromTableInBundle(@"Open Settings", nil, myBundle, @"Quad-buffered alert sheet open settings button title"),
	                  nil, // otherButton: none
	                  [NSApp mainWindow], // docWindow
	                  self, // modalDelegate
	                  NULL, // didEndSelector
	                  @selector(quadBufferedAlertSheetDidDismiss:returnCode:contextInfo:), //didDismissSelector
	                  NULL, // contextInfo
	                  NSLocalizedStringFromTableInBundle(@"Quad-buffered stereo cannot be switched on and off whilst a 3D view is open. To change stereo settings, shift-click the Stereo toolbar button or select the Plugins > Others > Quad-Buffered Stereo menu item when viewing an image series.", nil, myBundle, @"Quad-buffered alert sheet message"));
}


- (void)quadBufferedAlertSheetDidDismiss:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo // QBSController (QBSPrivateMethods)
{
	if (returnCode == NSAlertAlternateReturn)
		[self showSettingsPanel:nil];
}


@end
