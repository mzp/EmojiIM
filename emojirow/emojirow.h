//
//  emojirow.h
//  emojirow
//
//  Created by mzp on 2017/09/24.
//  Copyright © 2017 mzp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "emojirowProtocol.h"

// This object implements the protocol which we have defined. It provides the actual behavior for the service. It is 'exported' by the service to make it available to the process hosting the service over an NSXPCConnection.
@interface emojirow : NSObject <emojirowProtocol>
@end
