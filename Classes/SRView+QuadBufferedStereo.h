//
//  SRView+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "SRView.h"


@interface SRView (QuadBufferedStereo)

#pragma mark Initialization and Deallocation
- (void)QBS_dealloc; // Will be swizzled for -dealloc

#pragma mark Stereo
- (IBAction)SwitchStereoMode:(id)sender; // Override SRView

#pragma mark Image Capture
- (void)QBS_setImageCaptureBufferToLeft;
- (void)QBS_setImageCaptureBufferToRight;
- (NSImage *)QBS_nsimage:(BOOL)originalSize; // Will be swizzled for -nsimage:

@end
