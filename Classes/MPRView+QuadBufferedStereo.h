//
//  MPRView+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MPRView.h"


@interface MPRView (QuadBufferedStereo)

#pragma mark Initialization and Deallocation
- (void)awakeFromNib;

#pragma mark Stereo
- (IBAction)SwitchStereoMode:(id)sender; // Override MPRView

@end
