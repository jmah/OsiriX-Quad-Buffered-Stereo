//
//  QBSController.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-09.
//  Copyright (c) 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>


// NSUserDefaults keys
#define QBSStereoTypeKey @"QBSStereoType"
#define QBSEnableStereoKey @"QBSEnableStereo"
#define QBSForceBlueLineSyncKey @"QBSForceBlueLineSync"
#define QBSExportQuickTimeInStereoKey @"QBSExportQuickTimeInStereo"
#define QBSAskExportQuickTimeInStereoKey @"QBSAskExportQuickTimeInStereo"

typedef enum _QBSStereoType {
	QBSStereoTypeRedBlue = 0,
	QBSStereoTypeQuadBuffered = 1,
	QBSStereoTypeInterlaced = 2,
} QBSStereoType;


@interface QBSController : NSObject
{
	IBOutlet NSPanel *settingsPanel;
	IBOutlet NSTextView *creditsTextView;
}


#pragma mark Convenience Methods
+ (id)sharedController;

#pragma mark Utility Methods
- (void)registerUserDefaults;
- (void)setUpScreenForStereo:(NSTimer *)timer; // userInfo is an NSView

#pragma mark User Interface
- (IBAction)showSettingsPanel:(id)sender;
- (IBAction)beginQuadBufferedAlertSheet:(id)sender;

@end
