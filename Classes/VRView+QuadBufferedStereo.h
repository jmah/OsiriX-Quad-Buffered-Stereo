//
//  VRView+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "VRView.h"


@interface VRView (QuadBufferedStereo)

#pragma mark Stereo
- (IBAction)SwitchStereoMode:(id)sender; // Override VRView

@end
