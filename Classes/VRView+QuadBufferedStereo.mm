//
//  VRView+QuadBufferedStereo.mm
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-12-08.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import "VRView+QuadBufferedStereo.h"
#import "QBSController.h"


@implementation VRView (QuadBufferedStereo)


- (IBAction)SwitchStereoMode:(id)sender // Override VRView
{
	if ([[NSApp currentEvent] modifierFlags] & NSShiftKeyMask)
		[[QBSController sharedController] showSettingsPanel:self];
	else
	{
		if ([self renderWindow]->GetStereoType() == VTK_STEREO_CRYSTAL_EYES)
			// If we're already in quad-buffered mode, don't switch out of it
			[[QBSController sharedController] beginQuadBufferedAlertSheet:self];
		else
		{
			switch ([[NSUserDefaults standardUserDefaults] integerForKey:QBSStereoTypeKey])
			{
				case QBSStereoTypeQuadBuffered:
					[[QBSController sharedController] beginQuadBufferedAlertSheet:self];
					break;
				case QBSStereoTypeRedBlue:
					if( [self renderWindow]->GetStereoRender() == false)
					{
						orientationWidget->Off();
						
						[self renderWindow]->StereoRenderOn();
						[self renderWindow]->SetStereoTypeToRedBlue();
					}
					else
					{
						[self renderWindow]->StereoRenderOff();
						orientationWidget->On();
					}
					
					[self setNeedsDisplay:YES];
					break;
				case QBSStereoTypeInterlaced:
					if( [self renderWindow]->GetStereoRender() == false)
					{
						[self renderWindow]->StereoRenderOn();
						[self renderWindow]->SetStereoTypeToInterlaced();
					}
					else
						[self renderWindow]->StereoRenderOff();
					
					[self setNeedsDisplay:YES];
					break;
			}
		}
	}
}


@end
