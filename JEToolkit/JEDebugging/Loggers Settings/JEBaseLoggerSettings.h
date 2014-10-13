//
//  JEBaseLoggerSettings.h
//  JEToolkit
//
//  Copyright (c) 2013 John Rommel Estropia
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#import <Foundation/Foundation.h>


typedef NS_OPTIONS(NSUInteger, JELogLevelMask) {
    
    JELogLevelNone      = 0,
    JELogLevelTrace     = (1 << 0),
    JELogLevelNotice    = (1 << 1),
    JELogLevelAlert     = (1 << 2),
    // add custom masks here
    
    JELogLevelAll       = ~0u
};

typedef NS_OPTIONS(NSUInteger, JELogMessageHeaderMask) {
    
    JELogMessageHeaderNone          = 0,
    JELogMessageHeaderDate          = (1 << 0),
    JELogMessageHeaderQueue         = (1 << 1),
    
    JELogMessageHeaderSourceFile    = (1 << 2), // includes line number
    JELogMessageHeaderFunction      = (1 << 3),
    
    JELogMessageHeaderAll           = ~0u
};


@interface JEBaseLoggerSettings : NSObject <NSCopying>

/*!
 The combination of JELogLevelMask flags that will be output by this logger.
 */
@property (nonatomic, assign) JELogLevelMask logLevelMask;

/*!
 The combination of JELogMessageHeaderMask flags for log headers that will be displayed by this logger.
 */
@property (nonatomic, assign) JELogMessageHeaderMask logMessageHeaderMask;

@end
