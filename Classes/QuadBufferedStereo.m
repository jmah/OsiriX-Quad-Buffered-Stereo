//
//  QuadBufferedStereo.m
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright (c) 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "QuadBufferedStereo.h"
#import "QBSController.h"


@implementation QuadBufferedStereo


- (void)initPlugin
{
	[[QBSController sharedController] registerUserDefaults];
}


- (long)filterImage:(NSString *)menuName
{
	if ([menuName isEqualToString:@"Quad-Buffered Stereo"])
	{
		[[QBSController sharedController] showSettingsPanel:self];
		return 0;
	}
	else
	{
		NSBeep();
		NSLog(@"Quad-Buffered Stereo: Asked to handle unknown menu choice: %@", menuName);
		return -1;
	}
}


@end
