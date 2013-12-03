//
//  JEToolkitTests.m
//  JEToolkitTests
//
//  Created by John Rommel Estropia on 2013/08/10.
//  Copyright (c) 2013 John Rommel Estropia. All rights reserved.
//

#import <XCTest/XCTest.h>

#import <Foundation/Foundation.h>

#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>
#import <float.h>

#import "JEToolkit.h"
#import "JEOrderedDictionary.h"


@interface JEToolkitTests : XCTestCase

@end


@implementation JEToolkitTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testDumps
{
    [JEDebugging setFileLogLevelMask:JELogLevelAll];
    JEDump("This will be 2", 1+1);
    
    JEDump(100);
    int oneHundred = 100;
    JEDump(oneHundred);
    JEDump(&oneHundred);
    JEDump([NSValue valueWithBytes:&oneHundred objCType:@encode(typeof(oneHundred))]);
    JEDump((50 + 50));
    
    JEDump(12345.12345f);
    JEDump([NSNumber numberWithFloat:12345.12345f]);
    JEDump(12345678901234567890.0f);
    JEDump([NSNumber numberWithFloat:12345678901234567890.0f]);
    JEDump(12345678901234567890.0);
    JEDump([NSNumber numberWithDouble:12345678901234567890.0]);
    JEDump(M_PI);
    JEDump([NSNumber numberWithDouble:M_PI]);
    JEDump(NSIntegerMax);
    JEDump(NSIntegerMin);
    JEDump(CGFLOAT_MAX);
    JEDump([NSNumber numberWithFloat:CGFLOAT_MAX]);
    JEDump(CGFLOAT_MIN);
    JEDump([NSNumber numberWithFloat:CGFLOAT_MIN]);
    JEDump(DBL_MAX);
    JEDump([NSNumber numberWithDouble:DBL_MAX]);
    JEDump(DBL_MIN);
    JEDump([NSNumber numberWithDouble:DBL_MIN]);
    
    JEDump("cstring");
    char *cstringPtr = NULL;
    JEDump(cstringPtr);
    JEDump(&cstringPtr);
    JEDump([NSValue valueWithBytes:&cstringPtr objCType:@encode(typeof(cstringPtr))]);
    cstringPtr = "cstring";
    JEDump(cstringPtr);
    JEDump("This is a dump", &cstringPtr);
    char cstringArray[7] = "cstring";
    JEDump(cstringArray);
    JEDump(@encode(typeof(cstringArray)));
    JEDump(@encode(typeof(nil, cstringArray)));
    JEDump(sizeof(cstringArray));
    JEDump(sizeof(nil, cstringArray));
    JEDump(strlen(cstringArray));
    JEDump(strlen((nil, cstringArray)));
    
    
    JEDump(&cstringArray);
    JEDump([NSValue valueWithBytes:cstringArray objCType:@encode(typeof(cstringArray))]);
    char asciiArray[CHAR_MAX + 1] = {};
    for(int i = 0; i <= CHAR_MAX; ++i)
    {
        asciiArray[i] = i;
    }
    JEDump(asciiArray);
    JEDump(asciiArray);
    JEDump(&asciiArray);

    JEDump(_cmd);
    JEDump(@selector(viewDidAppear:));
    SEL selector = NULL;
    JEDump(selector);
    JEDump(&selector);
    JEDump([NSValue valueWithBytes:&selector objCType:@encode(typeof(selector))]);
    selector = _cmd;
    JEDump(selector);
    JEDump(&selector);
    JEDump([NSValue valueWithBytes:&selector objCType:@encode(typeof(selector))]);
    
    
    JEDump([UIView new]);
    JEDump(@"日本語😈");
    UIView * view = nil;
    JEDump(view);
    JEDump(&view);
    JEDump([NSValue valueWithBytes:&view objCType:@encode(typeof(view))]);
    view = [UIView new];
    JEDump(view);
    JEDump(&view);
    JEDump([NSValue valueWithBytes:&view objCType:@encode(typeof(view))]);
    
    NSValue *value = [NSValue valueWithNonretainedObject:view];
    JEDump(value);
    value = [NSValue valueWithPointer:CGColorCreate];
    JEDump(value);
    
    JEDump([view class]);
    JEDump([UIView class]);
    Class class = Nil;
    JEDump(class);
    JEDump(&class);
    JEDump([NSValue valueWithBytes:&class objCType:@encode(typeof(class))]);
    class = [UIView class];
    JEDump(class);
    JEDump(&class);
    JEDump([NSValue valueWithBytes:&class objCType:@encode(typeof(class))]);
    
    NSError *error = nil;
    JEDump([[NSFileManager defaultManager]
            moveItemAtPath:@"testdir"
            toPath:@"testdir"
            error:&error]);
    JEDumpAlert(error);
    
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    dictionary[@12] = @"cccc";
    dictionary[@34] = @"gggg";
    dictionary[@56] = @"iiii";
    dictionary[@"j"] = @"jjjj";
    dictionary[@"three"] = @{ @"threeone" : @31, @"threetwo" : @"three-two" };
    dictionary[@"e"] = @"eeee";
    dictionary[@"a"] = @1;
    dictionary[@"f"] = @"ffff";
    dictionary[@{ @"oneone" : @11 }] = @{ @"oneone" : @11 };
    dictionary[@"d"] = @"dddd";
    dictionary[@"b"] = @"bbbb";
    dictionary[@"h"] = @"hhhh";
    JEDump(dictionary);
    
    JEDump([dictionary allKeys]);
    JEDump([NSOrderedSet orderedSetWithArray:[dictionary allKeys]]);
    JEDump([NSSet setWithArray:[dictionary allValues]]);
    
    
    NSMapTable *mapTable = [NSMapTable strongToWeakObjectsMapTable];
    NSHashTable *hashTable = [NSHashTable weakObjectsHashTable];
    NSPointerArray *pointerArray = [NSPointerArray weakObjectsPointerArray];
    [dictionary enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
        
        [mapTable setObject:obj forKey:key];
        [hashTable addObject:key];
        [pointerArray addPointer:(__bridge void *)(obj)];
        
    }];
    JEDump(mapTable);
    JEDump(hashTable);
    JEDump(pointerArray);
    
    JEDump(CGRectZero);
    
    JEDump((CGPoint){ 1.999, 2.999 });
    JEDump((CGSize){ 1.999, 2.999 });
    JEDump((CGRect){ {1.999, 2.999 }, { 3.999, 4.999 }});
    JEDump((CGAffineTransform){ 1.999, 2.999, 3.999, 4.999, 5.999, 6.999 });
    JEDump((UIEdgeInsets){ 1.999, 2.999, 3.999, 4.999 });
    JEDump((UIOffset){ 1.999, 2.999 });
    JEDump((NSRange){ 1, 2 });
    JEDump((CLLocationCoordinate2D){ 1.999, 2.999 });
    JEDump((MKCoordinateSpan){ 1.999, 2.999 });
    JEDump((MKCoordinateRegion){ { 1.999, 2.999 }, { 3.999, 4.999 } });
    JEDump((MKMapPoint){ 1.999, 2.999 });
    JEDump((MKMapSize){ 1.999, 2.999 });
    JEDump((MKMapRect){ { 1.999, 2.999 }, { 3.999, 4.999 } });
    struct { int i1; int i2; int i3; } unnamedStruct;
    JEDump(unnamedStruct);
    
    CGRect rect = (CGRect){{1, 2}, {3, 4}};
    JEDump(rect);
    JEDump(&rect);
    JEDump([NSValue valueWithBytes:&rect objCType:@encode(typeof(rect))]);
    JEDump((CGRect [3]){(CGRect){ {1.999, 2.999 }, { 3.999, 4.999 }}, (CGRect){ {1.999, 2.999 }, { 3.999, 4.999 }}, (CGRect){ {1.999, 2.999 }, { 3.999, 4.999 }}});
    
    JEDump(&CGImageCreate);
    
    int intArray[2][3] = {{1, 2, 3}, {4, 5, 6}};
    JEDump(intArray);
    JEDump("intArray !!", &intArray);
    JEDump(&intArray);
    JEDump([NSValue valueWithBytes:intArray objCType:@encode(typeof(intArray))]);
    
    JEDump(^(int intParam, id idParam, CGRect rectParam, NSError ** outErrorParam){ return intParam + 100; });
    int (^block)(int intParam) = NULL;
    JEDump(block);
    JEDump(&block);
    JEDump([NSValue valueWithBytes:&block objCType:@encode(typeof(block))]);
    block = ^(int intParam){ return intParam + 100; };
    JEDump(block);
    JEDump(&block);
    JEDump([NSValue valueWithBytes:&block objCType:@encode(typeof(block))]);
    dispatch_block_t voidBlock = ^{ };
    JEDump(voidBlock);
    
    JEDump(FLT_DIG);
    JEDump(DBL_DIG);
    JEDump(LDBL_DIG);
    JEDump(DECIMAL_DIG);
    
    long double longDouble = 11111.9999888888888888;
    JEDump(longDouble);
    
    JEDump(0.12345f);
    JEDump([[NSNumber numberWithFloat:0.12345f] stringValue]);
    JEDump(0.123456f);
    JEDump([[NSNumber numberWithFloat:0.123456f] stringValue]);
    JEDump(0.1234567f);
    JEDump([[NSNumber numberWithFloat:0.1234567f] stringValue]);
    JEDump(0.12345678f);
    JEDump([[NSNumber numberWithFloat:0.12345678f] stringValue]);
    JEDump(0.123456789f);
    JEDump([[NSNumber numberWithFloat:0.123456789f] stringValue]);
    JEDump(0.1234567899f);
    JEDump([[NSNumber numberWithFloat:0.1234567899f] stringValue]);
    JEDump(0.12345678991f);
    JEDump([[NSNumber numberWithFloat:0.12345678991f] stringValue]);
    JEDump(0.123456789912f);
    JEDump([[NSNumber numberWithFloat:0.123456789912f] stringValue]);
    JEDump(123.123f);
    JEDump([[NSNumber numberWithFloat:123.123f] stringValue]);
    JEDump(1234.1234f);
    JEDump([[NSNumber numberWithFloat:1234.1234f] stringValue]);
    JEDump(12345.12345f);
    JEDump([[NSNumber numberWithFloat:12345.12345f] stringValue]);
    JEDump(123456.123456f);
    JEDump([[NSNumber numberWithFloat:123456.123456f] stringValue]);
    JEDump(1234567.1234567f);
    JEDump([[NSNumber numberWithFloat:1234567.1234567f] stringValue]);
    JEDump(12345678.12345678f);
    JEDump([[NSNumber numberWithFloat:12345678.12345678f] stringValue]);
    JEDump(123456789.123456789f);
    JEDump([[NSNumber numberWithFloat:123456789.123456789f] stringValue]);
    JEDump(1234567899.1234567899f);
    JEDump([[NSNumber numberWithFloat:1234567899.1234567899f] stringValue]);
    
    JEDump(0.1234567);
    JEDump([[NSNumber numberWithDouble:0.1234567] stringValue]);
    JEDump(0.12345678);
    JEDump(0.123456789);
    JEDump(0.1234567899);
    JEDump(0.12345678991);
    JEDump(0.123456789912);
    JEDump(0.1234567899123);
    JEDump(0.12345678991234);
    JEDump(0.123456789912345);
    JEDump(0.1234567899123456);
    JEDump(0.12345678991234567);
    JEDump(0.123456789912345678);
    JEDump(0.1234567899123456789);
    JEDump(0.12345678991234567899);
    JEDump(0.123456789912345678991);
    JEDump([[NSNumber numberWithDouble:0.123456789912345678991] stringValue]);
    JEDump(123456.123456);
    JEDump([[NSNumber numberWithDouble:123456.123456] stringValue]);
    JEDump(1234567.1234567);
    JEDump(12345678.12345678);
    JEDump(123456789.123456789);
    JEDump(1234567899.1234567899);
    JEDump(12345678991.12345678991);
    JEDump(123456789912.123456789912);
    JEDump(1234567899123.1234567899123);
    JEDump(12345678991234.12345678991234);
    JEDump(123456789912345.123456789912345);
    JEDump(1234567899123456.1234567899123456);
    JEDump(12345678991234567.12345678991234567);
    JEDump(123456789912345678.123456789912345678);
    JEDump(1234567899123456789.1234567899123456789);
    JEDump(12345678991234567899.0);
    JEDump([[NSNumber numberWithDouble:12345678991234567899.0] stringValue]);
    
    JEDump(0.123456789912l);
    JEDump(0.1234567899123l);
    JEDump(0.12345678991234l);
    JEDump(0.123456789912345l);
    JEDump(0.1234567899123456l);
    JEDump(0.12345678991234567l);
    JEDump(0.123456789912345678l);
    JEDump(0.1234567899123456789l);
    JEDump(0.12345678991234567899l);
    JEDump(0.123456789912345678991l);
    JEDump(0.1234567899123456789912l);
    JEDump(0.12345678991234567899123l);
    JEDump(0.123456789912345678991234l);
    JEDump(123456.123456l);
    JEDump(1234567.1234567l);
    JEDump(12345678.12345678l);
    JEDump(123456789.123456789l);
    JEDump(1234567899.1234567899l);
    JEDump(12345678991.12345678991l);
    JEDump(123456789912.123456789912l);
    JEDump(1234567899123.1234567899123l);
    JEDump(12345678991234.12345678991234l);
    JEDump(123456789912345.123456789912345l);
    JEDump(1234567899123456.1234567899123456l);
    JEDump(12345678991234567.1234567l);
    JEDump(123456789912345678.12345678l);
    JEDump(1234567899123456789.123456789l);
    JEDump(12345678991234567899.1234567899l);
    JEDump(123456789912345678991.12345678991l);
    JEDump(1234567899123456789912.123456789912l);
    JEDump(12345678991234567899123.1234567899123l);
    
    JEDump((CGColorRef)NULL);
    JEDump([UIColor clearColor].CGColor);
    JEDump(CFGetTypeID([UIColor clearColor].CGColor));
    
    @try {
        
        [[NSException
          exceptionWithName:@"Test Exception"
          reason:@"This exception was raised to test exception logging"
          userInfo:dictionary] raise];
    }
    @catch (NSException *exception) {
        
        JEDumpAlert(exception);
    }
    
    JEOrderedDictionary *orderedDictionary = [[JEOrderedDictionary alloc] init];
    orderedDictionary[@"500"] = @5,000;
    orderedDictionary[@"200"] = @NO;
    orderedDictionary[@3000] = @"300";
    orderedDictionary[@"100"] = @1,000;
    orderedDictionary[@"000"] = @0;
    JEDump(orderedDictionary);
    
    orderedDictionary[@"500"] = @YES;
    JEDump(orderedDictionary);
    
    JEDump([NSNumber numberWithBool:YES]);
    JEDump([NSNumber numberWithBool:NO]);
    JEDump([NSNumber numberWithChar:YES]);
    JEDump([NSNumber numberWithChar:NO]);
    JEDump(@YES);
    JEDump(@NO);
    JEDump(@([orderedDictionary count] == 5));
    JEDump(@([orderedDictionary count] < 5));
    JEDump(@((BOOL)([orderedDictionary count] == 5)));
    JEDump(@((BOOL)([orderedDictionary count] < 5)));
    
    NSString *string = @"string";
    id idArray[] = { string, string, string };
    JEDump(idArray);
    JEDump(&idArray);
    
    JEDump([NSNull null]);
    
    JELog(@"Trace No Parameters");
    JELogNotice(@"Log No Parameters");
    JELogAlert(@"Alert No Parameters");
    
    JELog(@"Trace Many Parameters: %@, %d, %f", @"yo", 10, 20.4f);
    JELogNotice(@"Log Many Parameters: %@, %d, %f", @"yo", 10, 20.4f);
    JELogAlert(@"Alert Many Parameters: %@, %d, %f", @"yo", 10, 20.4f);
    
    dispatch_queue_t queue = dispatch_queue_create("TestQueue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_barrier_sync(queue, ^{
        
        JELogLevel((1 << 5), @"Named queue");
        
    });
    
    queue = dispatch_queue_create(NULL, DISPATCH_QUEUE_CONCURRENT);
    dispatch_barrier_sync(queue, ^{
        
        JELogLevel((1 << 5), @"Unnamed queue");
        
    });
}

JESynthesizeObject(id, synthesizedId, setSynthesizedId, JESynthesizeRetainNonatomic);
JESynthesizeObject(void(^)(void), synthesizedBlock, setSynthesizedBlock, JESynthesizeCopyNonatomic);
JESynthesizeObject(id, synthesizedAssign, setSynthesizedAssign, JESynthesizeAssign);
JESynthesizeScalar(CGRect, synthesizedRect, setSynthesizedRect);

- (void)testSynthesized
{
    JEDump("Before assignment", self.synthesizedId);
    self.synthesizedId = @"test";
    JEDump("After assignment", self.synthesizedId);
    
    JEDump("Before assignment", self.synthesizedBlock);
    self.synthesizedBlock = ^{ };
    JEDump("After assignment", self.synthesizedBlock);
    
    JEDump("Before assignment", self.synthesizedAssign);
    self.synthesizedAssign = self;
    JEDump("After assignment", self.synthesizedAssign);
    
    JEDump("Before assignment", self.synthesizedRect);
    self.synthesizedRect = (CGRect){ {1, 2}, {3, 4} };
    JEDump("After assignment", self.synthesizedRect);
}


@end
