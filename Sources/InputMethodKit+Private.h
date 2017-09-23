//
//  InputMethodKit+Private.h
//  EmojiIM
//
//  Created by mzp on 2017/09/21.
//  Copyright © 2017 mzp. All rights reserved.
//

#ifndef InputMethodKit_Private_h
#define InputMethodKit_Private_h
#import <InputMethodKit/InputMethodKit.h>


@interface IPMDServerClientWrapper : NSObject <IMKTextInput, IMKUnicodeTextInput>
+ (void)terminateForClientXPCConn:(id)arg1;
+ (void)terminateForClientDOProxy:(id)arg1;
+ (id)clientWrapperWithClientDOProxy:(id)arg1;
+ (id)clientWrapperWithClientXPCConn:(id)arg1;
+ (id)_validateClientWrapper:(id)arg1;
+ (void)invalidateConnectionsAsNecessary:(id)arg1;
- (void)dismissFunctionRowItemTextInputView;
- (void)presentFunctionRowItemTextInputView;
@end

@protocol IMKCandidate <NSObject>
@property(readonly, copy, nonatomic) NSString *text;
@end

@interface IMKCandidate : NSObject <IMKCandidate>
{
    NSString *_text;
}

+ (id)candidateWithText:(id)arg1;
@property(readonly, copy, nonatomic) NSString *text; // @synthesize text=_text;
- (nonnull IMKCandidate*)initWithText:(id)arg1;
- (nonnull IMKCandidate*)init;
@end

@protocol IMKCandidateSelectionViewDelegate <NSObject>
- (void)didSelectSortingMode:(NSString *)arg1;
@end

@interface IMKCandidateData : NSObject
{
    NSArray *_keys;
    NSMutableDictionary *_keysToCandidates;
    NSArray *_candidates;
    BOOL _shouldShowGroups;
}

+ (nonnull IMKCandidateData* )candidateDataWithArray:(NSArray*)arg1;
@property(nonatomic) BOOL shouldShowGroups; // @synthesize shouldShowGroups=_shouldShowGroups;
@property(retain, nonatomic) NSMutableDictionary *keysToCandidates; // @synthesize keysToCandidates=_keysToCandidates;
@property(retain, nonatomic) NSArray *keys; // @synthesize keys=_keys;
- (unsigned long long)positionOfCandidateForKey:(id)arg1;
@property(readonly, nonatomic) BOOL hasGroups;
@property(readonly, nonatomic) NSArray *candidates;
- (unsigned long long)keyCount;
- (unsigned long long)candidateCount;
- (id)candidatesForKey:(id)arg1;
- (void)setCandidates:(id)arg1 forKey:(id)arg2;
- (void)dealloc;

@end

@protocol IMKCandidateControllerDelegate
- (id)textClient;
- (long long)windowType;
- (NSString *)displayMethod;
- (NSArray *)sortingMethods;
- (NSArray *)candidatesForSortingMethod:(NSString *)arg1;

@optional
- (BOOL)selectionShouldBeReflectedInTouchBar;
- (BOOL)touchesEndedOutsideView;
- (void)touchesEnded;
- (NSAttributedString *)currentInlineText;
- (NSArray *)localizedSortingMethods;
- (double)candidateThicknessForFontSize:(double)arg1;
- (NSString *)defaultDisplayMethod;
- (NSView *)informationView;
- (struct CGPoint)topWindowPositionForFrame:(struct CGRect)arg1;
- (BOOL)shouldUpdateExistingCandidates;
- (IMKCandidateData *)candidateDataForSortingMethod:(NSString *)arg1;
@end

@interface IMKUICandidateController : NSResponder
@property(readonly, nonatomic) BOOL shouldNotShowCandidates; // @synthesize shouldNotShowCandidates=_shouldNotShowCandidates;
@property(readonly, nonatomic) BOOL canExpand; // @synthesize canExpand=_canExpand;
@property(readonly, nonatomic) BOOL shouldLimitWindowSizeToCanvasSize; // @synthesize shouldLimitWindowSizeToCanvasSize=_shouldLimitWindowSizeToCanvasSize;
@property(readonly, nonatomic) BOOL hasCandidates; // @synthesize hasCandidates=_hasCandidates;
@property(copy, nonatomic) NSString *UISettingName; // @synthesize UISettingName=_UISettingName;
@property(retain, nonatomic) NSArray *sortingMethods; // @synthesize sortingMethods=_sortingMethods;
@property(copy, nonatomic) NSString *selectedCandidateKey; // @synthesize selectedCandidateKey=_selectedCandidateKey;
@property(copy, nonatomic) NSString *noCandidatesMessage; // @synthesize noCandidatesMessage=_noCandidatesMessage;
@property(nonatomic) double maxCandidateLineSize; // @synthesize maxCandidateLineSize=_maxCandidateLineSize;
@property(nonatomic) double fontSize; // @synthesize fontSize=_fontSize;
@property(copy, nonatomic) NSString *displayMethod; // @synthesize displayMethod=_displayMethod;
@property(nonatomic) id <IMKCandidateControllerDelegate> delegate;
@property(retain, nonatomic) IMKCandidateData *currentlyShownCandidates; 
@property(readonly, nonatomic) long long windowCategory;
@property(readonly, nonatomic) BOOL isWindowBacked;
@property(readonly, nonatomic) double numberOfRows;
@property(readonly, nonatomic) double numberOfColumns;
@property(readonly, nonatomic) BOOL showsAnnotations;
- (id)topVisibleCandidates;
- (BOOL)candidateIsVisible:(id)arg1;
@property(readonly, nonatomic) BOOL candidateWindowOnlyHasOneLine;
@property(readonly, nonatomic) BOOL flattensViewArchitecture;
@property(nonatomic) long long UIType;
@property(nonatomic) long long layoutOrientation;
@property(nonatomic) long long layoutDirection;
@property(nonatomic) double candidateThickness; // @synthesize candidateThickness=_candidateThickness;
- (void)selectCurrentlyFocusedItem;
@property(nonatomic) unsigned long long currentlySelectedIndex;
- (void)performVisualLineUpdates;
- (id)lineViewWithNumber:(unsigned long long)arg1;
- (struct CGRect)lineViewFrameWithNumber:(unsigned long long)arg1;
- (double)lineViewWidth;
- (void)updateAuxiliaryViews;
- (void)selectCandidate:(id)arg1 confirm:(BOOL)arg2;
- (void)didSelectCandidate:(id)arg1 confirm:(BOOL)arg2;
@property(nonatomic) unsigned long long topVisibleLine;
- (void)updateTopVisibleLineIfNecessary;
- (void)didUpdateTopVisibleLine;
- (void)topVisibleLineDidMoveTo:(unsigned long long)arg1;
- (void)setSelectedCandidateKey:(id)arg1 clickCount:(unsigned long long)arg2;
- (void)setSelectedCandidateKey:(id)arg1 clickCount:(unsigned long long)arg2 sendMessageToDelegate:(BOOL)arg3;
- (void)updateDebuggingInformation;
- (void)updateSelectionForKey:(id)arg1;
- (BOOL)layoutUnitsContainIdentifier:(id)arg1;
- (void)setupProperties;
- (void)setupUISettings;
- (void)unselectCandidates;
- (void)selectFirstCandidate;
- (void)changeGroupViewVisibility;
- (void)animateChanges;
- (void)reloadWithUpdatingFirstCandidate:(BOOL)arg1;
- (void)updateNumberOfLinesInWindow;
- (void)updateCandidateThickness;
- (void)reload;
- (struct CGRect)layout:(BOOL)arg1;
- (void)createNewLayout;
- (void)updateLayout:(id)arg1;
- (id)candidateDataForSortingMethod:(id)arg1;
- (id)layoutConstraintsForData:(id)arg1;
- (void)updateDocumentViewSize;
- (void)setDocumentSize:(struct CGSize)arg1;
- (struct CGSize)recommendedDocumentSizeWithSize:(struct CGSize)arg1;
- (BOOL)candidateViewCanScroll;
- (struct CGRect)recommendedWindowFrameWithFrame:(struct CGRect)arg1;
@property(readonly, nonatomic) struct CGSize customSize;
- (void)arrangeCanvasElements;
- (struct CGSize)preferredCanvasSize;
- (double)selectionViewHeight;
- (void)dealloc;
- (void)nilOutConnectionsToCandidateController;
- (id)init;

@end


@interface IMKUIWindowBasedCandidateController : IMKUICandidateController
+ (id)mutableCandidateWindowIDs;
+ (id)candidateWindowIDs;
+ (id)defaultSelectionKeyTitles;
@property(readonly, nonatomic) BOOL isSortable; // @synthesize isSortable=_isSortable;
@property(nonatomic) BOOL windowVisibilityDidChange; // @synthesize windowVisibilityDidChange=_windowVisibilityDidChange;
@property(nonatomic) BOOL windowVisibleWithDeferral; // @synthesize windowVisibleWithDeferral=_windowVisibleWithDeferral;
@property(nonatomic) BOOL showsSortingBar; // @synthesize showsSortingBar=_showsSortingBar;
@property(retain, nonatomic) NSArray *selectionKeyTitles; // @synthesize selectionKeyTitles=_selectionKeyTitles;
@property(nonatomic) BOOL resizeOnSelectionChanged; // @synthesize resizeOnSelectionChanged=_resizeOnSelectionChanged;
@property(nonatomic) BOOL resetCandidatesOnRelayout; // @synthesize resetCandidatesOnRelayout=_resetCandidatesOnRelayout;
@property(nonatomic) struct CGPoint previousPosition; // @synthesize previousPosition=_previousPosition;
@property(nonatomic) BOOL previousActionWasSortingChange; // @synthesize previousActionWasSortingChange=_previousActionWasSortingChange;
@property(nonatomic) struct CGSize positionalGridSize; // @synthesize positionalGridSize=_positionalGridSize;
@property(nonatomic) unsigned long long numberOfSimilarWidthCandidates; // @synthesize numberOfSimilarWidthCandidates=_numberOfSimilarWidthCandidates;
@property(nonatomic) double informationViewMinimumSize; // @synthesize informationViewMinimumSize=_informationViewMinimumSize;
@property(retain, nonatomic) NSView *informationView; // @synthesize informationView=_informationView;
@property(nonatomic, getter=isGrouping) BOOL grouping; // @synthesize grouping=_grouping;
@property(nonatomic) BOOL forceNoIncrementalSearchPositioning; // @synthesize forceNoIncrementalSearchPositioning=_forceNoIncrementalSearchPositioning;
@property(nonatomic) BOOL descriptionEnabled; // @synthesize descriptionEnabled=_descriptionEnabled;
@property(nonatomic) struct __IDXIndex *definitionIndexRef; // @synthesize definitionIndexRef=_definitionIndexRef;
@property(nonatomic) struct __DCSDictionary *definitionDictionary; // @synthesize definitionDictionary=_definitionDictionary;
@property(nonatomic) BOOL deferredWindowVisibility; // @synthesize deferredWindowVisibility=_deferredWindowVisibility;
- (void)selectSortingMethod:(id)arg1 expand:(BOOL)arg2;
- (void)selectPreviousSortingMethod;
- (void)selectNextSortingMethod;
@property(readonly, nonatomic) NSArray *topVisibleCandidates;
- (void)setSelectedCandidateKey:(id)arg1 clickCount:(unsigned long long)arg2 sendMessageToDelegate:(BOOL)arg3;
@property(readonly, nonatomic) BOOL shouldNotShowCandidates;
- (struct CGRect)layout:(BOOL)arg1;
- (struct CGRect)recommendedWindowFrameWithFrame:(struct CGRect)arg1;
@property(readonly, nonatomic) BOOL showsLegacyScroller;
- (void)updateDebuggingInformation;
- (void)performVisualLineUpdates;
- (void)updateSelectionKeys;
- (void)updateHighlights;
- (void)updateHighlightForLineView:(id)arg1;
- (void)updateGroupNames;
- (BOOL)isWindowBacked;
- (void)didSelectCandidate:(id)arg1 confirm:(BOOL)arg2;
- (void)updateCandidateCanvas;
- (void)willUpdateCandidateCanvas;
- (void)updateUIType;
- (void)initializeCanvas;
@property(retain, nonatomic) NSURL *descriptionStyleSheet; // @synthesize descriptionStyleSheet=_descriptionStyleSheet;
- (id)styleSheet;
- (BOOL)numberKeyPressed:(unsigned long long)arg1;
- (BOOL)selectionKeyPressed:(id)arg1;
- (void)moveToEnd;
- (void)moveToBeginning;
- (void)pageDown:(id)arg1;
- (void)pageUp:(id)arg1;
- (void)moveDown:(id)arg1;
- (void)moveUp:(id)arg1;
- (void)moveToPreviousCandidate:(id)arg1;
- (void)moveToNextCandidate:(id)arg1;
- (void)moveForward:(id)arg1;
- (void)moveBackwards:(id)arg1;
- (void)moveRight:(id)arg1;
- (void)moveLeft:(id)arg1;
- (void)updateVisibleSelectionOnMovement;
- (BOOL)handleKeyboardEvent:(id)arg1;
- (void)resizeWindow:(struct CGRect)arg1;
- (void)resizeWindowIfNecessary:(struct CGRect)arg1;
- (void)windowAnimationDidFinish;
- (void)addInformationView;
- (void)updateCanvasAfterSizeChange;
- (struct CGSize)preferredCanvasSize;
- (void)createNewLayout;
@property(readonly, nonatomic) struct CGSize extraSize;
@property(readonly, nonatomic) BOOL windowWillClose;
- (void)updateIncrementalSearchState;
@property(readonly, nonatomic) BOOL isUsingIncrementalSearch;
- (void)updatePreviousPosition;
- (void)resetPreviousPosition;
- (void)endGrouping;
- (void)beginGrouping;
- (struct CGPoint)topWindowPositionForFrame:(struct CGRect)arg1 withClient:(id)arg2;
- (struct CGPoint)topPositionForFrame:(struct CGRect)arg1;
- (struct CGPoint)adjustedPositionWithGrid:(struct CGPoint)arg1;
@property(nonatomic) long long windowLevel;
@property(readonly, nonatomic) BOOL windowTextIsVerticallyAligned;
@property(readonly, nonatomic, getter=isExpanded) BOOL expanded;
@property(readonly, nonatomic) BOOL windowIsHorizontal;
- (void)requestRadar;
- (BOOL)shouldShowRadarButton;
- (void)didSelectSortingMode:(id)arg1;
- (void)hide;
- (void)windowDidHide;
@property(nonatomic, getter=isVisible) BOOL visible;
- (double)lineViewWidth;
- (void)reloadWithUpdatingFirstCandidate:(BOOL)arg1;
- (void)updateCandidateSelection;
- (void)updateWindowLevel;
- (id)textClient;
- (void)addCandidatesToPasteboard;
- (void)clearPasteboard;
- (void)dealloc;
- (id)init;

@end

@interface IMKUICandidateTouchBarController : IMKUICandidateController

@property(nonatomic) BOOL secondaryCandidatesShowChevron; // @synthesize secondaryCandidatesShowChevron=_secondaryCandidatesShowChevron;
@property(nonatomic) unsigned long long numberOfSimilarWidthCandidates; // @synthesize numberOfSimilarWidthCandidates=_numberOfSimilarWidthCandidates;
- (void)touchesEndedOutsideView;
- (void)touchesEnded;
- (void)showPrimaryCandidateWindowAndSelectCandidate:(id)arg1;
- (void)shouldUpdateForPressAndHold:(id)arg1;
- (void)scrubbedCandidate:(id)arg1;
- (BOOL)handleKeyboardEvent:(id)arg1;
- (id)candidateDataToFit:(id)arg1;
- (double)minimumWidthForCandidate:(id)arg1;
- (void)reloadWithUpdatingFirstCandidate:(BOOL)arg1;
- (id)candidateDataForSortingMethod:(id)arg1;
- (void)arrangeCanvasElements;
- (BOOL)showsAnnotations;
@property(readonly, nonatomic) NSViewController *viewController;
- (double)lineViewWidth;
- (void)updateHighlightForLineView:(id)arg1;
- (void)updateCandidateThickness;
- (id)layoutConstraintsForData:(id)arg1;
- (double)maxWidthForTouchBarCandidates;
- (struct CGSize)customSize;
- (double)numberOfColumns;
- (struct CGSize)preferredCanvasSize;
- (double)widthOfStandardRow;
- (void)updateCandidateCanvas;
- (void)initializeCanvas;
- (void)dealloc;
- (id)init;

@end

@interface IMKUIInformation : NSObject
{
//    IMKUICandidateTouchBarController *_touchBarController;
//    IMKUIWindowBasedCandidateController *_visibleOnscreenController;
}

+ (nullable IMKUIInformation *)sharedInformation;
+ (BOOL)isUsingSubclassingImplementation;
+ (BOOL)isAppleInternal;
+ (BOOL)isTouchBarAvailable;
@property(nullable, retain, nonatomic) IMKUIWindowBasedCandidateController* visibleOnscreenController; // @synthesize visibleOnscreenController=_visibleOnscreenController;
@property(nullable, retain, nonatomic) IMKUICandidateTouchBarController* touchBarController; // @synthesize touchBarController=_touchBarController;
- (void)dealloc;
@property(readonly, nonatomic) IMKInputController *inputController;
@property(readonly, nonatomic) id textClient;

@end

@protocol IMKUIDelegate
- (IMKCandidateData *)candidateDataForController:(IMKUICandidateController *)arg1;
@end


@interface IMKUICandidateTouchBarOnScreenBridge : NSObject <IMKCandidateControllerDelegate, IMKUIDelegate>
+ (nonnull IMKUICandidateTouchBarOnScreenBridge*)sharedBridge;
@property(retain, nonatomic) IMKCandidateData *secondaryCandidates; // @synthesize secondaryCandidates=_secondaryCandidates;
@property(nonatomic) BOOL scrubbingInTouchBarUpdatesOnscreenCandidates; // @synthesize scrubbingInTouchBarUpdatesOnscreenCandidates=_scrubbingInTouchBarUpdatesOnscreenCandidates;
@property(nonatomic) BOOL shouldRouteTouchBarSelectionEventsToInputController; // @synthesize shouldRouteTouchBarSelectionEventsToInputController=_shouldRouteTouchBarSelectionEventsToInputController;
@property(nonatomic) BOOL onscreenCandidatesReflectedInTouchBar; // @synthesize onscreenCandidatesReflectedInTouchBar=_onscreenCandidatesReflectedInTouchBar;
@property(nonatomic) Class auxiliaryOnscreenControllerClass; // @synthesize auxiliaryOnscreenControllerClass=_auxiliaryOnscreenControllerClass;
- (void)handleCandidateSelected:(id)arg1 candidateController:(id)arg2;
- (void)handleCandidateSelectionChanged:(id)arg1 candidateController:(id)arg2;
- (id)selectedCandidateKey:(id)arg1;
- (id)displayMethod;
- (id)sortingMethods;
- (id)candidateDataForController:(id)arg1;
- (void)onscreenCandidatesDidHide:(id)arg1;
- (void)onscreenCandidatesDidReload:(id)arg1;
- (void)onscreenCandidateSelectionDidChange:(id)arg1 committed:(BOOL)arg2;
@property(readonly, nonatomic) BOOL onscreenCandidatesCorrespondToTouchBarCandidates;
- (void)closeAuxiliaryWindowController;
- (void)shouldUpdateForPressAndHold:(id)arg1;
- (void)touchesEndedOutsideView;
- (void)touchesEnded;
- (void)scrubbedCandidate:(id)arg1;
- (void)showAuxiliaryWindowIfNecessary;
@property(readonly, nonatomic) IMKUICandidateTouchBarController *touchBarController;
- (void)dealloc;
- (id)init;

@end

@interface IMKCandidateBasedInputController : IMKInputController <IMKCandidateControllerDelegate, IMKCandidateSelectionViewDelegate>

@property(retain, nonatomic) NSArray *secondaryCandidates; // @synthesize secondaryCandidates=_secondaryCandidates;
@property(nonatomic) BOOL sInvalidateIncrementalSearchClientGeometry; // @synthesize sInvalidateIncrementalSearchClientGeometry=_sInvalidateIncrementalSearchClientGeometry;
@property(nonatomic) BOOL sInvalidateIsIncrementalSearchInputContext; // @synthesize sInvalidateIsIncrementalSearchInputContext=_sInvalidateIsIncrementalSearchInputContext;
@property(nonatomic) BOOL sInvalidateIMKTextOrientation; // @synthesize sInvalidateIMKTextOrientation=_sInvalidateIMKTextOrientation;
@property(nonatomic) unsigned long long windowLevel; // @synthesize windowLevel=_windowLevel;
@property(nonatomic) struct _NSRange selectedRange; // @synthesize selectedRange=_selectedRange;
@property(nonatomic) BOOL primaryCandidatesShownByScrubbing; // @synthesize primaryCandidatesShownByScrubbing=_primaryCandidatesShownByScrubbing;
- (void)setMarkedText:(id)arg1 selectionRange:(struct _NSRange)arg2 replacementRange:(struct _NSRange)arg3;
- (void)insertText:(id)arg1 replacementRange:(struct _NSRange)arg2;
- (id)secondaryCandidateControllerAuxiliaryViews;
- (BOOL)touchesEndedOutsideView;
- (void)touchesEnded;
- (void)shouldUpdateForPressAndHold:(id)arg1;
- (void)scrubbedCandidate:(id)arg1;
@property(readonly, nonatomic) BOOL automaticallyRestrictLayoutToPrimaryCandidateControllerLayout;
@property(readonly, nonatomic) BOOL automaticallyShowPrimaryCandidatesInSecondaryController;
- (id)currentInlineText;
- (id)textClient;
@property(readonly, nonatomic) unsigned long long incrementalSearchClientGeometry;
@property(readonly, nonatomic) BOOL isIncrementalSearchInputContext;
- (id)informationView;
- (BOOL)isUsingIncrementalSearch;
- (id)defaultDisplayMethod;
- (void)didSelectSortingMode:(id)arg1;
- (BOOL)shouldUpdateExistingCandidates;
- (id)candidatesForSortingMethod:(id)arg1;
- (long long)windowType;
- (id)sortingMethods;
- (id)displayMethod;
- (id)functionRowItemTextInputViewController;
- (id)inlineText;
- (void)hideSecondaryCandidatesOnly;
- (void)reloadSecondaryCandidatesOnly;
- (void)hideCandidates;
- (void)reloadCandidates;
- (void)dismissSecondaryCandidates;
- (void)presentSecondaryCandidates;
- (BOOL)selectDisplayMethod:(id)arg1;
- (void)handleCandidateSelected:(id)arg1 candidateController:(id)arg2;
- (void)handleCandidateSelectionChanged:(id)arg1 candidateController:(id)arg2;
- (id)candidateDataForDisplayMethod:(id)arg1 candidateController:(id)arg2;
@property(readonly, nonatomic) NSString *selectedDisplayMethod;
@property(readonly, nonatomic) BOOL isVerticalLayout;
@property(readonly, nonatomic) NSArray *displayMethods;
- (void)dealloc;
- (void)invalidateClientSideInfoCache;
- (Class)touchBarControllerClass;
@property(readonly, nonatomic) Class onscreenCandidateWindowClass;
@property(readonly, nonatomic) Class auxiliaryCandidateWindowClass;
- (void)deactivateServer:(id)arg1;
- (void)activateServer:(id)arg1;
@end

#endif /* InputMethodKit_Private_h */
