//
//  InputMethodKit+Private.h
//  EmojiIM
//
//  Created by mzp on 2017/09/29.
//  Copyright © 2017 mzp. All rights reserved.
//

#ifndef InputMethodKit_Private_h
#define InputMethodKit_Private_h

#import <InputMethodKit/InputMethodKit.h>

@protocol IMKExtensionMainInit
+ (void)mainThreadIMKInit;
@end

@interface IPMDServerClientWrapper : NSObject <IMKTextInput, IMKUnicodeTextInput>
- (void)dismissFunctionRowItemTextInputView;
- (void)presentFunctionRowItemTextInputView;
@end

@protocol IMKCandidate <NSObject>
@property(readonly, copy, nonatomic) NSString *text;
@end

@interface IMKCandidate : NSObject <IMKCandidate>
@property(readonly, copy, nonatomic) NSString *text; // @synthesize text=_text;
@end

@protocol IMKCandidateIndexing <NSObject>
@property(readonly, nonatomic) NSString *uniqueKey;
@end

@interface IMKCandidateDefinitionUnit : NSObject <IMKCandidateIndexing>
+ (id)dictionaryFromDebugLog:(id)arg1;
+ (id)sharedTextStorage;
@property(nonatomic) BOOL selectionTurnedOff; // @synthesize selectionTurnedOff=_selectionTurnedOff;
@property(copy, nonatomic) NSAttributedString *extraAnnotation; // @synthesize extraAnnotation=_extraAnnotation;
@property(copy, nonatomic) NSString *annotation; // @synthesize annotation=_annotation;
@property(copy, nonatomic) NSString *text; // @synthesize text=_text;
@property(nonatomic) BOOL hasNote; // @synthesize hasNote=_hasNote;
@property(nonatomic) BOOL hasDefinition; // @synthesize hasDefinition=_hasDefinition;
@property(readonly, copy) NSString *debugDescription;
@property(readonly, nonatomic) NSString *axHelpString;
@property(readonly, nonatomic) NSString *axValueString;
@end

@interface IMKCandidateData : NSObject
+ (nonnull IMKCandidateData* )candidateDataWithArray:(nonnull NSArray<IMKCandidateDefinitionUnit*>*)arg1;
@end

@class IMKUICandidateController;

@protocol IMKUIDelegate
- (nonnull IMKCandidateData *)candidateDataForController:(nonnull IMKUICandidateController *)controller;
@end

@interface IMKUICandidateController : NSResponder
@property(nonatomic) id <IMKUIDelegate> delegate;
@end

@interface IMKUICandidateTouchBarController : IMKUICandidateController
@property(nonatomic) BOOL secondaryCandidatesShowChevron;
@property(nonatomic) unsigned long long numberOfSimilarWidthCandidates;
- (void)reloadWithUpdatingFirstCandidate:(BOOL)arg1;
@property(readonly, nonatomic) NSViewController *viewController;
@end

@interface IMKUIInformation : NSObject
+ (nullable IMKUIInformation *)sharedInformation;
+ (BOOL)isTouchBarAvailable;
@end

#endif /* InputMethodKit_Private_h */
