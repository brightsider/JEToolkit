//
//  JEDebugging.h
//  JEToolkit
//
//  Created by John Rommel Estropia on 2013/09/28.
//  Copyright (c) 2013 John Rommel Estropia. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "NSArray+JEDebugging.h"
#import "NSDate+JEDebugging.h"
#import "NSDictionary+JEDebugging.h"
#import "NSError+JEDebugging.h"
#import "NSException+JEDebugging.h"
#import "NSHashTable+JEDebugging.h"
#import "NSMapTable+JEDebugging.h"
#import "NSMutableString+JEDebugging.h"
#import "NSNumber+JEDebugging.h"
#import "NSObject+JEDebugging.h"
#import "NSOrderedSet+JEDebugging.h"
#import "NSPointerArray+JEDebugging.h"
#import "NSSet+JEDebugging.h"
#import "NSString+JEDebugging.h"
#import "NSValue+JEDebugging.h"
#import "UIColor+JEDebugging.h"
#import "UIImage+JEDebugging.h"

#import "JECompilerDefines.h"

#import "JEConsoleLoggerSettings.h"
#import "JEHUDLoggerSettings.h"
#import "JEFileLoggerSettings.h"






#pragma mark - JEAssert() variants

#ifdef NS_BLOCK_ASSERTIONS

#define JEAssert(condition, formatString, ...)  do {} while (NO)
#define JEAssertParameter(condition)            do {} while (NO)
#define JEAssertMainThread()                    do {} while (NO)
#define JEAssertBackgroundThread()              do {} while (NO)

#else

#define JEAssert(condition, formatString, ...) \
    do { \
        if (!(condition)) { \
            [JEDebugging \
             logFailureInAssertionCondition:@"" #condition \
             location:JELogLocationCurrent()]; \
            JE_PRAGMA_PUSH \
            JE_PRAGMA_IGNORE("-Wformat-extra-args") \
            [NSException \
             raise:NSInternalInconsistencyException \
             format:(formatString), ##__VA_ARGS__]; \
            JE_PRAGMA_POP \
        } \
    } while(NO)

#define JEAssertParameter(condition) \
    JEAssert((condition), @"Invalid parameter not satisfying: (%s)", #condition)

#define JEAssertMainThread() \
    JEAssert([NSThread isMainThread], @"Code expected to run on the main thread")

#define JEAssertBackgroundThread() \
    JEAssert(![NSThread isMainThread], @"Code expected to run on a background thread")

#endif



#pragma mark - JEDump() variants

/*! Dumps detailed information of any variable or expression to the console.
 
 The macro argument is variadic to allow expressions that have commas in them. You can use this as a trick to use the comma operator to attach a string before the expression, such as JEDump("This will be 2", 1+1); Be warned though that if you are using the comma operator for arrays you need to pass the address instead: JEDump("This is safe", &arrayVariable);
 Otherwise, only the first item in the array will be printed (or crash if you passed an empty array).
 
 Note that a bug(?) with NSGetSizeAndAlignment() prevents structs and unions with bitfields to be wrapped in NSValue, in which case JEDump() will just print "(?){ ... }".
 */
#define JEDump(expression...) \
    JEDumpLevel(JELogLevelTrace, ##expression)

#define JEDumpTrace(expression...) \
    JEDumpLevel(JELogLevelTrace, ##expression)

#define JEDumpNotice(expression...) \
    JEDumpLevel(JELogLevelNotice, ##expression)

#define JEDumpAlert(expression...) \
    JEDumpLevel(JELogLevelAlert, ##expression)

#define JEDumpLevel(level, expression...) \
    do { \
        JE_PRAGMA_PUSH \
        JE_PRAGMA_IGNORE("-Wunused-value") \
        /* We need to assign the expression to a variable in case it is an rvalue. */ \
        /* Since arrays cannot be assigned to another array, we use the comma operator in typeof(0, expression) to demote array types to their pointer counterparts. */ \
        const typeof(0, expression) _je_value = (expression); \
        JE_PRAGMA_POP \
        [JEDebugging \
         dumpLevel:level \
         location:JELogLocationCurrent() \
         label:(@""#expression) \
         value:[NSValue \
                valueWithBytes:({ \
                    /* We need to get the proper address to pass to NSValue. That is, if an array we need to pass itself, otherwise its address. Hopefully, this all gets optimized out by the compiler. */ \
                    const void *const _je_pointer = &_je_value; \
                    (@encode(typeof(expression))[0] == '[' \
                        ? *(const void *const *)_je_pointer \
                        : _je_pointer); \
                }) \
                objCType:@encode(typeof(expression))]]; \
    } while(NO)



#pragma mark - JELog() variants

/*! Logs a format string to the console. Also displays the source filename, line number, and method name.
 */
#define JELog(formatString, ...) \
    JELogLevel(JELogLevelTrace, (formatString), ##__VA_ARGS__)

#define JELogTrace(formatString, ...) \
    JELogLevel(JELogLevelTrace, (formatString), ##__VA_ARGS__)

#define JELogNotice(formatString, ...) \
    JELogLevel(JELogLevelNotice, (formatString), ##__VA_ARGS__)

#define JELogAlert(formatString, ...) \
    JELogLevel(JELogLevelAlert, (formatString), ##__VA_ARGS__)

#define JELogLevel(level, formatString, ...) \
    do { \
        JE_PRAGMA_PUSH \
        JE_PRAGMA_IGNORE("-Wformat-extra-args") \
        [JEDebugging \
         logLevel:level \
         location:JELogLocationCurrent() \
         format:(formatString), ##__VA_ARGS__]; \
        JE_PRAGMA_POP \
    } while(NO)



#pragma mark - Log message header constants container

typedef struct JELogLocation {

    const char *fileName;
    const char *functionName;
    int lineNumber;

} JELogLocation;

#define JELogLocationCurrent()  ((JELogLocation){ __JE_FILE_NAME__, __PRETTY_FUNCTION__, __LINE__ })



#pragma mark - Breakpoint utility

#if !DEBUG
#define JEDebugBreak()  do {} while (NO)

#elif TARGET_CPU_ARM
#define JEDebugBreak() \
    do { \
        if (![JEDebugging isDebuggerAttached]) { \
            break; \
        } \
        /* http://iphone.m20.nl/wp/2010/10/xcode-iphone-debugger-halt-assertions/ */ \
        __asm__ __volatile__ ( \
            "mov r0, %0\n" \
            "mov r1, %1\n" \
            "mov r12, #37\n" \
            "swi 128\n" \
            "nop\n" \
            : \
            : "r" (getpid()), "r" (SIGINT) \
            : "r12", "r0", "r1", "cc" \
        ); \
    } while (NO)

#elif TARGET_CPU_ARM64
#define JEDebugBreak() \
    do { \
        if (![JEDebugging isDebuggerAttached]) { \
            break; \
        } \
        __asm__ __volatile__ ( \
            "movq r0, %0\n" \
            "movq r1, %1\n" \
            "movq r12, #37\n" \
            "swi 128\n" \
            "nop\n" \
            : \
            : "r" (getpid()), "r" (SIGINT) \
            : "r12", "r0", "r1", "cc" \
        ); \
    } while (NO)

#elif TARGET_CPU_X86
#define JEDebugBreak() \
    do { \
        if (![JEDebugging isDebuggerAttached]) { \
            break; \
        } \
        /* http://iphone.m20.nl/wp/2010/10/xcode-iphone-debugger-halt-assertions/ */ \
        __asm__ __volatile__ ( \
            "pushl %0\n" \
            "pushl %1\n" \
            "push $0\n" \
            "movl %2, %%eax\n" \
            "int $0x80\n" \
            "add $12, %%esp" \
            : \
            : "g" (SIGINT), "g" (getpid()), "n" (37) \
            : "eax", "cc" \
        ); \
    } while (NO)

#elif TARGET_CPU_X86_64
#define JEDebugBreak() \
    do { \
        if (![JEDebugging isDebuggerAttached]) { \
            break; \
        } \
        __asm__ __volatile__ ( \
            "pushq %0\n" \
            "pushq %1\n" \
            "push $0\n" \
            "movq %2, %%rax\n" \
            "syscall\n" \
            "addq $24, %%rsp" \
            : \
            : "g" (SIGINT), "g" (getpid()), "n" (37) \
            : "rax", "cc" \
        ); \
    } while (NO)

#else
#define JEDebugBreak()  do {} while (NO)

#endif

#define JEDebugBreakIf(condition) \
    do { \
        if (condition) { \
            JEDebugBreak(); \
        } \
    } while(NO)



#pragma mark - JEDebugging class

/*! @p JEDebugging is the central hub for configuring, submitting, and extracting logs.
 */
@interface JEDebugging : NSObject

#pragma mark - utilities

/*! Provides the value of the @p DEBUG preprocessor flag during runtime.
 @return @p YES if the @p DEBUG flag is set, @p NO otherwise.
 */
+ (BOOL)isDebugBuild;

/*! Checks if the debugger is currently attached to the app.
 @return @p YES if the debugger is attached to the running app process, @p NO otherwise.
 */
+ (BOOL)isDebuggerAttached;


#pragma mark - configuring

/*! Returns a configurable copy of the current console logger settings.
 @return a configurable copy of the current console logger settings. The changes to the returned object will not be reflected until it is passed back to @p setConsoleLoggerSettings:
 */
+ (JEConsoleLoggerSettings *)copyConsoleLoggerSettings JE_WARN_UNUSED_RESULT;

/*! Updates the current console logger settings. Note that the settings object passed to this method will be copied by the receiver, thus, further changes to the settings object will not be reflected until it is again passed to @p setConsoleLoggerSettings:
 @param consoleLoggerSettings the settings object holding new configuration values
 */
+ (void)setConsoleLoggerSettings:(JEConsoleLoggerSettings *)consoleLoggerSettings;

/*! Returns a configurable copy of the current HUD logger settings.
 @return a configurable copy of the current HUD logger settings. The changes to the returned object will not be reflected until it is passed back to @p setHUDLoggerSettings:
 */
+ (JEHUDLoggerSettings *)copyHUDLoggerSettings JE_WARN_UNUSED_RESULT;

/*! Updates the current HUD logger settings. Note that the settings object passed to this method will be copied by the receiver, thus, further changes to the settings object will not be reflected until it is again passed to @p setHUDLoggerSettings:
 @param HUDLoggerSettings the settings object holding new configuration values
 */
+ (void)setHUDLoggerSettings:(JEHUDLoggerSettings *)HUDLoggerSettings;

/*! Returns a configurable copy of the current file logger settings.
 @return a configurable copy of the current file logger settings. The changes to the returned object will not be reflected until it is passed back to @p setFileLoggerSettings:
 */
+ (JEFileLoggerSettings *)copyFileLoggerSettings JE_WARN_UNUSED_RESULT;

/*! Updates the current file logger settings. Note that the settings object passed to this method will be copied by the receiver, thus, further changes to the settings object will not be reflected until it is again passed to @p setFileLoggerSettings:
 @param fileLoggerSettings the settings object holding new configuration values
 */
+ (void)setFileLoggerSettings:(JEFileLoggerSettings *)fileLoggerSettings;

/*! Enable or disable exception logging. Note that setting enabled to @p YES will detach the previously set exception handler, such as handlers provided by analytics frameworks or other debugging frameworks.
 @param enabled @p YES to enable exception logging and detach the previous exception handler; @p NO to disable exception logging and restore the original exception handler. Defaults to @p NO.
 */
+ (void)setExceptionLoggingEnabled:(BOOL)enabled;

/*! Enable or disable application lifecycle logging. Logged events include foreground and background events, active and inactive events.
 @param enabled @p YES to enable application lifecycle logging, @p NO to disable. Defaults to @p NO.
 */
+ (void)setApplicationLifecycleLoggingEnabled:(BOOL)enabled;

/*!
 Starts the logging session. All logs are ignored until this method is called.
 */
+ (void)start;


#pragma mark - logging

/*!
 Use the @p JEDump(...) family of utilities instead of this method.
 */
+ (void)dumpLevel:(JELogLevelMask)level
         location:(JELogLocation)location
            label:(NSString *)label
            value:(NSValue *)wrappedValue;

/*!
 Use the @p JELog(...) family of utilities instead of this method.
 */
+ (void)logLevel:(JELogLevelMask)level
        location:(JELogLocation)location
          format:(NSString *)format, ... JE_FORMAT_STRING(3, 4);

/*!
 Use the @p JELog(...) family of utilities instead of this method.
 */
+ (void)logLevel:(JELogLevelMask)level
        location:(JELogLocation)location
          format:(NSString *)format
       arguments:(va_list)arguments;

/*!
 Use the @p JEAssert(...) family of utilities instead of this method.
 */
+ (void)logFailureInAssertionCondition:(NSString *)conditionString
                              location:(JELogLocation)location;


#pragma mark - retrieving

/*!
 Enumerates all log files' data synchronously, starting with the most recent up to the oldest file.
 @param block The iteration block. Set the @p stop argument to @p YES to terminate the enumeration.
 */
+ (void)enumerateFileLogDataWithBlock:(void (^)(NSString *fileName, NSData *data, BOOL *stop))block;

/*!
 Enumerates all log files' URLs synchronously, starting with the most recent up to the oldest file.
 @param block The iteration block. Set the @p stop argument to @p YES to terminate the enumeration.
 */
+ (void)enumerateFileLogURLsWithBlock:(void (^)(NSURL *fileURL, BOOL *stop))block;

@end
