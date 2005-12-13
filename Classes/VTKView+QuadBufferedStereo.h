//
//  VTKView+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "VTKView.h"


@interface VTKView (QuadBufferedStereo)

- (id)QBS_initWithFrame:(NSRect)frame; // Will be swizzled for -initWithFrame:

@end
