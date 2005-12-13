//
//  QBSSwizzleMethod.h
//  Quad-Buffered Stereo
//
//  Created by Jonathon Mah on 2005-03-19.
//  Copyright 2005 Jonathon Mah, SAPAC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/objc-class.h>


inline void QBSSwizzleClassMethod(Class klass, SEL originalSelector, SEL newSelector)
{
    Method originalMethod = nil, newMethod = nil;
	
    originalMethod = class_getClassMethod(klass, originalSelector);
    newMethod = class_getClassMethod(klass, newSelector);
	
    // If both are found, swizzle them
    if (originalMethod && newMethod)
	{
        IMP originalMethodImp;
		
		// Swap method implementations
        originalMethodImp = originalMethod->method_imp;
        originalMethod->method_imp = newMethod->method_imp;
        newMethod->method_imp = originalMethodImp;
	}
	else
		NSLog(@"Error: Methods not swizzled! (Old: +%@  New: +%@  Class:%@)", NSStringFromSelector(originalSelector), NSStringFromSelector(newSelector), NSStringFromClass(klass));
}


inline void QBSSwizzleInstanceMethod(Class klass, SEL originalSelector, SEL newSelector)
{
    Method originalMethod = nil, newMethod = nil;
	
    originalMethod = class_getInstanceMethod(klass, originalSelector);
    newMethod = class_getInstanceMethod(klass, newSelector);
	
    // If both are found, swizzle them
    if (originalMethod && newMethod)
	{
        IMP originalMethodImp;
		
		// Swap method implementations
        originalMethodImp = originalMethod->method_imp;
        originalMethod->method_imp = newMethod->method_imp;
        newMethod->method_imp = originalMethodImp;
	}
	else
		NSLog(@"Error: Methods not swizzled! (Old: -%@  New: -%@  Class:%@)", NSStringFromSelector(originalSelector), NSStringFromSelector(newSelector), NSStringFromClass(klass));
}
