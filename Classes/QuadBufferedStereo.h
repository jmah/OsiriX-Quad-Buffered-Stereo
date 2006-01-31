//
//  QaudBufferedStereo.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright (c) 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PluginFilter.h"


@interface QuadBufferedStereo : PluginFilter
{
}


- (long)filterImage:(NSString *)menuName;

@end
