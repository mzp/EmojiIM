//
//  InputMethodKit+Private.h
//  EmojiIM
//
//  Created by mzp on 2017/09/29.
//  Copyright © 2017 mzp. All rights reserved.
//

#ifndef InputMethodKit_Private_h
#define InputMethodKit_Private_h
#import <Foundation/Foundation.h>

@protocol IMKExtensionDelegate <NSObject>
- (void)extensionWillTerminate;
- (void)extensionDidLaunch;
@end

#endif /* InputMethodKit_Private_h */
