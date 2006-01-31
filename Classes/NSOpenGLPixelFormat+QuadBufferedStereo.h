//
//  NSOpenGLPixelFormat+QuadBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface NSOpenGLPixelFormat (QuadBufferedStereo)

#pragma mark Initialization and Deallocation
- (id)QBS_initWithAttributes:(NSOpenGLPixelFormatAttribute *)attribs; // Will be swizzled for -initWithAttributes:

#pragma mark Stereo
+ (void)QBS_forceStereo:(BOOL)stereo;

@end
