//
//  FlyThruController+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2006-01-25.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "FlyThruController.h"


@interface FlyThruController (QuadBufferedStereo)

#pragma mark QuickTime Export
- (IBAction)QBS_flyThruQuicktimeExport:(id)sender; // Will be swizzled for -flyThruQuicktimeExport:
- (IBAction)QBS_flyThruQuicktimeExportStereo:(id)sender;
- (void)QBS_flyThruAskQuicktimeExportStereoAlertDidEnd:(NSWindow *)alertSheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;

@end
