//
//  NSOpenGLPixelFormat+QuadBufferedStereo.m
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "NSOpenGLPixelFormat+QuadBufferedStereo.h"
#import "QBSSwizzleMethod.h"


static BOOL forceStereo = NO;


@implementation NSOpenGLPixelFormat (QuadBufferedStereo)

#pragma mark Initialization and Deallocation

+ (void)load
{
	QBSSwizzleInstanceMethod([self class], @selector(initWithAttributes:), @selector(QBS_initWithAttributes:));
}


- (id)QBS_initWithAttributes:(NSOpenGLPixelFormatAttribute *)attrs // Will be swizzled for -initWithAttributes:
{
	id result = nil;
	
	if (forceStereo)
	{
		unsigned int attrCount = 0;
		NSOpenGLPixelFormatAttribute *remainingAttrs = attrs;
		while (*remainingAttrs++)
			attrCount++;
		
		// Add two for the stereo attribute and a nil terminator
		NSOpenGLPixelFormatAttribute *newAttrs = calloc(attrCount + 2, sizeof(NSOpenGLPixelFormatAttribute));
		
		// Add the stereo attributes
		newAttrs[0] = NSOpenGLPFAStereo;
		
		// Copy existing attributes
		remainingAttrs = attrs;
		NSOpenGLPixelFormatAttribute *remainingNewAttrs = newAttrs;
		remainingNewAttrs++;
		while (*remainingNewAttrs++ = *remainingAttrs++);
		
		result = [self QBS_initWithAttributes:newAttrs];
		if (!result)
		{
			NSLog(@"Quad-Buffered Stereo: Couldn't acquire a stereo pixel format; falling back to mono.");
			result = [self QBS_initWithAttributes:attrs];
		}
		
		free(newAttrs);
	}
	else
		result = [self QBS_initWithAttributes:attrs];
	
	return result;
}



#pragma mark Stereo

+ (void)QBS_forceStereo:(BOOL)stereo
{
	forceStereo = stereo;
}


@end
