//
//  NSURL+JEToolkit.h
//  JEToolkit
//
//  Created by John Rommel Estropia on 2013/10/05.
//  Copyright (c) 2013 John Rommel Estropia. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "JECompilerDefines.h"


@interface NSURL (JEToolkit)

#pragma mark - Directories

/*! Convenience method to get the app Application Support URL
 */
+ (NSURL *)applicationSupportDirectory JE_CONST;

/*! Convenience method to get the app Caches URL
 */
+ (NSURL *)cachesDirectory JE_CONST;

/*! Convenience method to get the app Documents URL
 */
+ (NSURL *)documentsDirectory JE_CONST;

/*! Convenience method to get the app Downloads URL
 */
+ (NSURL *)downloadsDirectory JE_CONST;

/*! Convenience method to get the app Library URL
 */
+ (NSURL *)libraryDirectory JE_CONST;

/*! Convenience method to get the app Temporary URL
 */
+ (NSURL *)temporaryDirectory JE_CONST;


#pragma mark - Inspecting URLs

/*! Returns the known UTI for the receiver
 */
- (NSString *)UTI;

/*! Returns the known mimetype for the receiver, or "application/octet-stream" if a known mimetype was not found
 */
- (NSString *)mimeType;

/*! Checks if the reciever is an assets library URL
 */
- (BOOL)isAssetsLibraryURL;

/*! Checks if the reciever is a data URL
 */
- (BOOL)isDataURL;


#pragma mark - Extended Attributes

/*! Reads the extended attribute of a file URL referred to by key. Note anything other than file system URLs will be ignored.
 @param extendedAttribute The destination address of the read attribute
 @param key The key for the extended attribute
 @param error The error if the process failed
 @return YES if the attribute was read successfully, NO otherwise.
 */
- (BOOL)getExtendedAttribute:(NSString **)extendedAttribute
                      forKey:(NSString *)key
                       error:(NSError **)error;

/*! Sets an extended attribute on the file refered by the receiver. Note anything other than file system URLs will be ignored.
 @param extendedAttribute The value for the extended attribute
 @param key The key for the extended attribute
 @param error The error if the process failed
 @return YES if the attribute was set successfully, NO otherwise.
 */
- (BOOL)setExtendedAttribute:(NSString *)extendedAttribute
                      forKey:(NSString *)key
                       error:(NSError **)error;


@end