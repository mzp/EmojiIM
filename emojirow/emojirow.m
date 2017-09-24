//
//  emojirow.m
//  emojirow
//
//  Created by mzp on 2017/09/24.
//  Copyright © 2017 mzp. All rights reserved.
//

#import "emojirow.h"

@implementation emojirow

// This implements the example protocol. Replace the body of this class with the implementation of this service's protocol.
- (void)upperCaseString:(NSString *)aString withReply:(void (^)(NSString *))reply {
    NSString *response = [aString uppercaseString];
    reply(response);
}

@end
