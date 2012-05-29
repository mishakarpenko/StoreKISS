//
//  StoreKISSDataRequest.h
//  StoreKISS
//
//  Created by Misha Karpenko on 5/24/12.
//  Copyright (c) 2012 Redigion. All rights reserved.
//

#import "StoreKISSShared.h"

@class StoreKISSDataRequest;

typedef enum {
	StoreKISSDataRequestStatusNew,
	StoreKISSDataRequestStatusStarted,
	StoreKISSDataRequestStatusFinished
} StoreKISSDataRequestStatus;

typedef void (^StoreKISSDataRequestSuccessBlock)(StoreKISSDataRequest *request,
												 SKProductsResponse *response);
typedef void (^StoreKISSDataRequestFailureBlock)(NSError *error);

extern NSString * const StoreKISSNotificationDataRequestStarted;
extern NSString * const StoreKISSNotificationDataRequestSuccess;
extern NSString * const StoreKISSNotificationDataRequestSuccessResponseKey;
extern NSString * const StoreKISSNotificationDataRequestFailure;
extern NSString * const StoreKISSNotificationDataRequestFailureErrorKey;

/**
 Class for fetching payment data from iTunesConnect using Product IDs.
 
 There are two methods to accomplish that:
 
 - `requestDataForItemWithProductId:success:failure:` for a single product;
 - `requestDataForItemsWithProductIds:success:failure:` for a bulk request.
 
 As soon as request finishes either success or failure block will be called.
 
 Success block will be called with the request itself and `SKProductsResponse` object in the parameters.
 
 Failure block will contain only the `NSError` object in the parameters.
 
 You can also track request execution using notifications. Each notification is a `NSNotification` instance and you can get the `StoreKISSDataRequest` object by accessing its `- object` property.
 
 Here are notification types:
 
 - `StoreKISSNotificationDataRequestStarted` &mdash; data request started;
 - `StoreKISSNotificationDataRequestSuccess` &mdash; data request finished with success, the `SKProductsRespinse` object is contained in `userInfo` dictionary by `StoreKISSNotificationDataRequestSuccessResponseKey` key;
 - `StoreKISSNotificationDataRequestFailure` &mdash; data request finished with failure, the `NSError` object is contained in `userInfo` dictionary by `StoreKISSNotificationDataRequestFailureErrorKey` key.
 */
@interface StoreKISSDataRequest : NSObject<SKProductsRequestDelegate>

///-----------------
/// @name Properties
///-----------------

/**
 Status of the request.
 */
@property (nonatomic) StoreKISSDataRequestStatus status;

///----------------------
/// @name Requesting data
///----------------------

/**
 Requests payment data from iTunesConnect for the item with a concrete Product ID.
 
 @param productId Product ID of the item for which payment data is fetched.
 @param success Success block.
 @param failure Failure block.
 */
- (void)requestDataForItemWithProductId:(NSString *)productId
								success:(StoreKISSDataRequestSuccessBlock)success
								failure:(StoreKISSDataRequestFailureBlock)failure;

/**
 Requests payment data from iTunesConnect for items with a set of Product IDs.
 
 @param productIds Set of Product IDs of the items for which payment data is fetched.
 @param success Success block.
 @param failure Failure block.
 */
- (void)requestDataForItemsWithProductIds:(NSSet *)productIds
								  success:(StoreKISSDataRequestSuccessBlock)success
								  failure:(StoreKISSDataRequestFailureBlock)failure;

@end
