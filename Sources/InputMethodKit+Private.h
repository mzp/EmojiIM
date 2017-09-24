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

@protocol IMKCandidateIndexing <NSObject>
@property(readonly, nonatomic) NSString *uniqueKey;
@end

@interface IMKCandidateDefinitionUnit : NSObject <IMKCandidateIndexing>
{
    NSString *_text;
    NSString *_annotation;
    NSAttributedString *_extraAnnotation;
    BOOL _hasDefinition;
    BOOL _hasNote;
    BOOL _selectionTurnedOff;
}

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
- (void)dealloc;
- (id)descriptionHTMLAndBaseURL:(id *)arg1;
@property(readonly, nonatomic) NSString *uniqueKey;
- (void)drawInRect:(struct CGRect)arg1 layoutUnit:(id)arg2 selectionKey:(id)arg3 properties:(id)arg4 backgroundColor:(id)arg5 drawsBackgroundColor:(BOOL)arg6 roundsLeftCorners:(BOOL)arg7 roundsRightCorners:(BOOL)arg8;
- (void)drawAnnotationsInRect:(struct CGRect)arg1 layoutUnit:(id)arg2 properties:(id)arg3;
- (void)drawCandidateDataInRect:(struct CGRect)arg1 layoutUnit:(id)arg2 properties:(id)arg3;
- (void)drawSelectionKey:(id)arg1 inRect:(struct CGRect)arg2 layoutUnit:(id)arg3 properties:(id)arg4;
- (void)drawBackgroundInRect:(struct CGRect)arg1 selected:(BOOL)arg2 properties:(id)arg3 backgroundColor:(id)arg4 drawsBackgroundColor:(BOOL)arg5;
- (void)drawBackgroundForTouchBarInRect:(struct CGRect)arg1 selected:(BOOL)arg2 roundLeftCorners:(BOOL)arg3 roundRightCorners:(BOOL)arg4;
- (void)drawFunctionKeyInRect:(struct CGRect)arg1 selected:(BOOL)arg2;
- (void)turnOffFontSmoothing:(id)arg1;

// Remaining properties
@property(readonly, copy) NSString *description;
@property(readonly) unsigned long long hash;
@property(readonly) Class superclass;

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



@interface IMKCandidateController : NSObject

+ (BOOL)isAppleInternal;
+ (id)defaultSelectionKeyTitles;
+ (BOOL)touchBarAvailable;
+ (id)sharedFunctionRowCandidateController;
+ (id)sharedCandidateController;
+ (id)mutableCandidateWindowIDs;
+ (id)candidateWindowIDs;
@property(nonatomic) BOOL windowVisibilityDidChange; // @synthesize windowVisibilityDidChange=_windowVisibilityDidChange;
@property(nonatomic) BOOL windowVisibleWithDeferral; // @synthesize windowVisibleWithDeferral=_windowVisibleWithDeferral;
@property(nonatomic) long long windowType; // @synthesize windowType=_windowType;
//@property(retain, nonatomic) IMKCandidateWindowPositioning *windowPositioning; // @synthesize windowPositioning=_windowPositioning;
//@property(retain, nonatomic) IMKWindowController *windowController; // @synthesize windowController=_windowController;
@property(nonatomic) long long UIState; // @synthesize UIState=_UIState;
@property(copy, nonatomic) NSString *UISettingName; // @synthesize UISettingName=_UISettingName;
//@property(retain, nonatomic) IMKCandidateUIProperties *UIProperties; // @synthesize UIProperties=_UIProperties;
@property(nonatomic) double totalCandidateLineSize; // @synthesize totalCandidateLineSize=_totalCandidateLineSize;
@property(nonatomic) id textClient; // @synthesize textClient=_textClient;
@property(retain, nonatomic) NSArray *sortingMethods; // @synthesize sortingMethods=_sortingMethods;
@property(retain, nonatomic) NSArray *selectionKeyTitles; // @synthesize selectionKeyTitles=_selectionKeyTitles;
@property(copy, nonatomic) NSString *selectedCandidateKey; // @synthesize selectedCandidateKey=_selectedCandidateKey;
@property(nonatomic) BOOL secondaryCandidatesShowChevron; // @synthesize secondaryCandidatesShowChevron=_secondaryCandidatesShowChevron;
@property(nonatomic) BOOL resizeOnSelectionChanged; // @synthesize resizeOnSelectionChanged=_resizeOnSelectionChanged;
@property(nonatomic) BOOL resetCandidatesOnRelayout; // @synthesize resetCandidatesOnRelayout=_resetCandidatesOnRelayout;
//@property(retain, nonatomic) IMKUIProperties *properties; // @synthesize properties=_properties;
@property(nonatomic) struct CGPoint previousPosition; // @synthesize previousPosition=_previousPosition;
@property(nonatomic) BOOL previousActionWasSortingChange; // @synthesize previousActionWasSortingChange=_previousActionWasSortingChange;
@property(nonatomic) struct CGSize positionalGridSize; // @synthesize positionalGridSize=_positionalGridSize;
//@property(retain, nonatomic) IMKCandidatePopoverController *popoverController; // @synthesize popoverController=_popoverController;
@property(nonatomic) BOOL optimizeLayoutForFixedSize; // @synthesize optimizeLayoutForFixedSize=_optimizeLayoutForFixedSize;
@property(nonatomic) unsigned long long numberOfSimilarWidthCandidates; // @synthesize numberOfSimilarWidthCandidates=_numberOfSimilarWidthCandidates;
@property(nonatomic) double numberOfRows; // @synthesize numberOfRows=_numberOfRows;
@property(nonatomic) double numberOfColumns; // @synthesize numberOfColumns=_numberOfColumns;
@property(copy, nonatomic) NSString *noCandidatesMessage; // @synthesize noCandidatesMessage=_noCandidatesMessage;
//@property(retain, nonatomic) IMKCandidateNavigationController *navigationController; // @synthesize navigationController=_navigationController;
@property(nonatomic) double maxCandidateLineSize; // @synthesize maxCandidateLineSize=_maxCandidateLineSize;
//@property(retain, nonatomic) IMKLayoutToViewController *layoutToViewController; // @synthesize layoutToViewController=_layoutToViewController;
@property(retain, nonatomic) IMKServer *inputServer; // @synthesize inputServer=_inputServer;
@property(nonatomic) double informationViewMinimumSize; // @synthesize informationViewMinimumSize=_informationViewMinimumSize;
@property(retain, nonatomic) NSView *informationView; // @synthesize informationView=_informationView;
@property(nonatomic, getter=isGrouping) BOOL grouping; // @synthesize grouping=_grouping;
@property(nonatomic) BOOL forceNoIncrementalSearchPositioning; // @synthesize forceNoIncrementalSearchPositioning=_forceNoIncrementalSearchPositioning;
@property(nonatomic) double fontSize; // @synthesize fontSize=_fontSize;
@property(nonatomic) BOOL expandedInternal; // @synthesize expandedInternal=_expandedInternal;
@property(copy, nonatomic) NSString *displayMethod; // @synthesize displayMethod=_displayMethod;
@property(nonatomic) id <IMKCandidateControllerDelegate, IMKCandidateSelectionViewDelegate> delegate; // @synthesize delegate=_delegate;
@property(nonatomic) BOOL descriptionEnabled; // @synthesize descriptionEnabled=_descriptionEnabled;
//@property(retain, nonatomic) IMKDefinitionToLayoutController *definitionToLayoutController; // @synthesize definitionToLayoutController=_definitionToLayoutController;
@property(nonatomic) struct __DCSDictionary *definitionDictionary; // @synthesize definitionDictionary=_definitionDictionary;
@property(nonatomic) BOOL deferredWindowVisibility; // @synthesize deferredWindowVisibility=_deferredWindowVisibility;
@property(retain, nonatomic) IMKCandidateData *currentlyShownCandidates; // @synthesize currentlyShownCandidates=_currentlyShownCandidates;
//@property(retain, nonatomic) IMKCandidateCanvas *canvas; // @synthesize canvas=_canvas;
@property(readonly, nonatomic) BOOL showsAnnotations;
- (id)restrictedLayoutForCandidates:(id)arg1;
- (id)topVisibleCandidates;
- (BOOL)candidateIsVisible:(id)arg1;
@property(readonly, nonatomic) BOOL candidateWindowOnlyHasOneLine;
@property(readonly, nonatomic) BOOL flattensViewArchitecture;
- (id)viewController;
@property(readonly, nonatomic) BOOL windowWillClose;
@property(readonly, nonatomic) struct CGSize extraSize;
@property(readonly, nonatomic) BOOL showsLegacyScroller;
- (BOOL)handleKeyboardEvent:(id)arg1;
- (struct CGPoint)topWindowPositionForFrame:(struct CGRect)arg1 withClient:(id)arg2;
- (struct CGPoint)topPositionForFrame:(struct CGRect)arg1;
- (struct CGPoint)adjustedPositionWithGrid:(struct CGPoint)arg1;
@property(retain, nonatomic) NSURL *descriptionStyleSheet;
- (id)styleSheet;
@property(nonatomic) long long windowLevel;
@property(nonatomic) unsigned long long truncationType;
@property(nonatomic) long long UIType;
@property(nonatomic) long long layoutOrientation;
@property(nonatomic) long long layoutDirection;
@property(nonatomic) double candidateThickness;
@property(readonly, nonatomic) BOOL isUsingIncrementalSearch;
- (void)updateIncrementalSearchStateWithClient:(id)arg1;
@property(readonly, nonatomic) BOOL hasCandidates;
- (void)stepperViewDownArrowPressed;
- (void)stepperViewUpArrowPressed;
- (void)requestRadar;
- (BOOL)shouldShowRadarButton;
- (void)didSelectSortingMode:(id)arg1;
- (void)selectCurrentlyFocusedItem;
- (BOOL)windowTypeIsSortable;
- (void)endGrouping;
- (void)beginGrouping;
@property(readonly, nonatomic) IMKCandidateDefinitionUnit *currentlySelectedCandidate;
- (void)forceCollapse;
- (void)arrowViewPressed:(id)arg1;
- (void)setCurrentlySelectedIndex:(unsigned long long)arg1;
- (unsigned long long)currentlySelectedIndex;
- (void)selectDefaultSortingMethod;
- (void)selectSortingMethod:(id)arg1 expand:(BOOL)arg2;
- (void)selectPreviousSortingMethod;
- (void)selectNextSortingMethod;
@property(readonly, nonatomic) BOOL windowTextIsVerticallyAligned;
@property(readonly, nonatomic, getter=isExpanded) BOOL expanded;
@property(readonly, nonatomic) BOOL windowIsHorizontal;
- (void)hide;
@property(nonatomic, getter=isVisible) BOOL visible;
- (id)lineViewWithNumber:(unsigned long long)arg1;
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
- (void)updateVisibleSelection;
@property(readonly, nonatomic) BOOL canExpand;
- (void)updateSelectionKeys;
- (void)updateHighlights;
- (void)updateGroupNames;
- (void)performVisualLineUpdates;
- (void)updateStepper;
- (void)updateAuxilliaryViews;
- (void)touchesEndedOutsideView;
- (void)touchesEnded;
- (void)showPrimaryCandidateWindowAndSelectCandidate:(id)arg1;
- (void)shouldUpdateForPressAndHold:(id)arg1;
- (void)scrubbedCandidate:(id)arg1;
- (void)selectCandidate:(id)arg1 confirm:(BOOL)arg2;
@property(nonatomic) unsigned long long topVisibleLine;
- (void)updateTopVisibleLineIfNecessary;
- (void)topVisibleLineDidMoveTo:(unsigned long long)arg1;
- (void)setSelectedCandidateKey:(id)arg1 clickCount:(unsigned long long)arg2;
- (void)setSelectedCandidateKey:(id)arg1 clickCount:(unsigned long long)arg2 sendMessageToDelegate:(BOOL)arg3;
- (void)updateSelectionForKey:(id)arg1;
- (BOOL)shouldShowSelectionUpdateInTouchBar;
- (BOOL)layoutUnitsContainIdentifier:(id)arg1;
- (void)setupProperties;
- (void)setupUISettings;
- (void)unselectCandidates;
- (void)selectFirstCandidate;
- (void)changeGroupViewVisibility;
- (void)animateChanges;
- (void)reloadWithUpdatingFirstCandidate:(BOOL)arg1;
- (void)reload;
- (void)addCandidatesToPasteboard;
- (void)clearPasteboard;
- (void)updateWindowLevelWithClient:(id)arg1;
- (void)updateUIType;
- (void)updateWindowType;
- (void)resizeWindow:(struct CGRect)arg1;
- (void)layoutAccordingToWindowType;
- (struct CGRect)layoutWithoutResizingCandidateView;
- (void)layoutAndResizeCandidateView;
- (struct CGRect)layout:(BOOL)arg1;
- (void)transformDefinitionUnitsIntoLayoutUnits;
- (id)candidateDataForSortingMethod:(id)arg1;
- (void)setLayoutConstraintsForWindowTypeWithCandidates:(id)arg1;
- (void)prepareNewLayoutForAnimation:(id)arg1;
- (void)setOriginalFramesForNewLine:(id)arg1 originalLine:(id)arg2;
- (void)moveElementsOutToTheLeft:(id)arg1 inLine:(id)arg2;
- (void)moveElementsInFromTheLeft:(id)arg1 inLine:(id)arg2;
- (id)elementsPresentInLine:(id)arg1 andLine:(id)arg2;
- (void)updateDocumentViewSize;
- (struct CGRect)resizedWindowFrame;
@property(readonly, nonatomic) BOOL shouldLimitWindowSizeToCanvasSize;
@property(readonly, nonatomic) struct CGSize customSize;
- (struct CGSize)customSizeWithWindowType:(long long)arg1 expanded:(BOOL)arg2;
@property(readonly, nonatomic) double minCandidateLineSize;
- (double)auxilliaryViewWidthForWindowType:(long long)arg1;
- (void)setCandidateWindowCanvas;
- (double)minimumSelectionViewWidth;
- (double)selectionViewHeight;
- (void)collapse;
- (void)expand;
- (void)collapseWindowWithoutAnimation;
- (void)collapseWindowWithAnimation;
- (void)expandWindowWithAnimation;
- (void)updateArrowView;
- (void)setWindowFrameWithAnimation:(BOOL)arg1;
- (void)calibrateLayoutForCollapsedHorizontalView;
- (void)calibrateLayoutForExpandedHorizontalView;
- (void)initializeViews;
- (void)updatePreviousPosition;
- (void)resetPreviousPosition;
- (void)dealloc;
- (void)nilOutConnectionsToCandidateController;
- (id)init;
- (double)widthOfStandardRow;

@end

@interface IMKCandidateBasedInputController : IMKInputController <IMKCandidateControllerDelegate, IMKCandidateSelectionViewDelegate>

@property(retain, nonatomic) IMKUIWindowBasedCandidateController *candidateController;
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
- (NSViewController*)functionRowItemTextInputViewController;
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
@property(readonly, nonatomic) IMKUICandidateTouchBarController *secondaryCandidateController;
@property(readonly, nonatomic) Class onscreenCandidateWindowClass;
@property(readonly, nonatomic) Class auxiliaryCandidateWindowClass;
- (void)deactivateServer:(id)arg1;
- (void)activateServer:(id)arg1;
@end


@interface IMKServer(Internal)
+ (void)presentFunctionRowItemTextInputView;
+ (id)inputDelegateClassNameFor:(id)arg1;
+ (id)inputControllerClassNameFor:(id)arg1;
+ (id)connectionNameFor:(id)arg1;
+ (id)_clientWrapperForXPCConn:(id)arg1;
+ (id)_clientWrapperForDOProxy:(id)arg1;
+ (id)imkServerSingleton;
- (id)keyBindingManager;
- (void)setEventHandlingStatus:(int)arg1;
- (id)keyBindingState;
- (void)ironwoodPlaceholderWasInvalidated_Common:(id)arg1 clientWrapper:(id)arg2 controller:(id)arg3;
- (void)ironwoodPlaceholderWasInvalidated:(id)arg1 client:(id)arg2;
- (void)ironwoodTextWasCorrected_Common:(id)arg1 clientWrapper:(id)arg2 controller:(id)arg3;
- (void)ironwoodTextWasCorrected:(id)arg1 client:(id)arg2;
- (void)sendInputSessionSessAction_Common:(unsigned int)arg1 timestamp:(double)arg2 withInfo:(id)arg3 clientWrapper:(id)arg4 controller:(id)arg5;
- (void)sendInputSessionSessAction:(unsigned int)arg1 timestamp:(double)arg2 withInfo:(id)arg3 client:(id)arg4;
- (void)sendInputSessionSessAction_Common:(unsigned int)arg1 clientWrapper:(id)arg2 controller:(id)arg3;
- (void)sendInputSessionSessAction:(unsigned int)arg1 client:(id)arg2;
- (void)invalidateClientGeometry_CommonWithController:(id)arg1;
- (void)invalidateClientGeometry:(id)arg1;
- (void)hidePalettes_CommonWithController:(id)arg1;
- (void)hidePalettes:(id)arg1;
- (void)commitComposition_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (void)commitComposition:(id)arg1;
- (BOOL)handleEvent_Common:(id)arg1 characterIndex:(unsigned long long)arg2 edge:(unsigned long long)arg3 clientWrapper:(id)arg4 controller:(id)arg5;
- (BOOL)handleEvent:(bycopy id)arg1 characterIndex:(unsigned long long)arg2 edge:(unsigned long long)arg3 client:(id)arg4;
- (BOOL)_insertTextForEvent:(id)arg1;
- (void)_setCurrentIMKEvent:(id)arg1;
- (id)_currentIMKEvent;
- (BOOL)lastKeyEventWasDeadKey;
- (id)_attributedStringFromEventPack:(id)arg1;
- (id)modes_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (id)modes:(id)arg1;
- (id)_keys;
- (void)clientProxy:(id)arg1;
- (unsigned long long)recognizedEvents_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (unsigned long long)recognizedEvents:(id)arg1;
- (void)doCommandBySelector_Common:(SEL)arg1 commandDictionary:(id)arg2 clientWrapper:(id)arg3 controller:(id)arg4;
- (void)doCommandBySelector:(SEL)arg1 commandDictionary:(id)arg2 client:(id)arg3;
- (id)_searchSubMenus:(id)arg1 forTitle:(id)arg2;
- (BOOL)didCommandBySelector_Common:(SEL)arg1 clientWrapper:(id)arg2 controller:(id)arg3;
- (BOOL)didCommandBySelector:(SEL)arg1 client:(id)arg2;
- (BOOL)didCommandBySelector:(SEL)arg1 withObject:(id)arg2;
- (id)menusDictionary_CommonWithController:(id)arg1;
- (id)menusDictionary:(id)arg1;
- (id)_copySynchronizedActions:(id)arg1 withMenuItems:(id)arg2;
- (id)_actionsFromMenu:(id)arg1;
- (BOOL)_isPalette;
- (id)_getModeDictionary;
- (void)setValue_Common:(id)arg1 forTag:(unsigned long long)arg2 clientWrapper:(id)arg3 controller:(id)arg4;
- (void)setValue:(id)arg1 forTag:(unsigned long long)arg2 client:(id)arg3;
- (id)valueForTag_Common:(unsigned long long)arg1 clientWrapper:(id)arg2 controller:(id)arg3;
- (id)valueForTag:(unsigned long long)arg1 client:(id)arg2;
- (void)sessionFinished_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (void)sessionFinished:(id)arg1;
- (void)activateServer_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (void)activateServer:(id)arg1;
- (void)deactivateServer_CommonWithClientWrapper:(id)arg1 controller:(id)arg2;
- (void)deactivateServer:(id)arg1;
- (void)releasePAHController:(id)arg1;
- (void)setFunctionRowItemViewServiceXPCEndpoint:(id)arg1;
- (id)functionRowItemViewServiceXPCEndpoint;
- (id)IMBundleIdentifier;
- (void)_forgetValidEventsInClient:(id)arg1;
- (void)_rememberValidEvent:(id)arg1 fromEventPack:(id)arg2 inClient:(id)arg3;
- (void)_rememberKeyboardType:(id)arg1 inClient:(id)arg2;
- (id)_IMKCandidates;
- (void)_setIMKCandidates:(id)arg1;
- (id)_currentPresentingController;
- (id)_currentController;
- (void)_setCurrentController:(id)arg1;
- (void)_setPresentingClientWrapper:(id)arg1;
- (id)_presentingClientWrapper;
- (void)_setCurrentClientWrapper:(id)arg1;
- (id)_currentClientWrapper;
- (id)_currentClient;
- (id)_menuActions:(id)arg1;
- (void)_setEvents:(id)arg1 forController:(id)arg2;
- (id)_eventsForController:(id)arg1;
- (void)_setMouseMovedState:(BOOL)arg1 forClient:(id)arg2 controller:(id)arg3;
- (id)_eventRefToNSEvent:(id)arg1 repeat:(BOOL)arg2;
- (id)_getStringForKeyCode:(unsigned int *)arg1 andModifiers:(unsigned long long *)arg2 unmodifiedString:(id *)arg3 fromEventPackage:(id)arg4;
- (struct CGPoint)_breakDownMouseEvent:(id)arg1 theModifiers:(unsigned long long *)arg2;
- (void)_handleText:(id)arg1;
- (void)_handleCommand:(SEL)arg1;
- (id)_keyBindings;
- (id)bundle;
- (id)higherRunLoopInvocation;
- (void)popRunLoopInvocation;
- (void)pushRunLoopInvocation:(id)arg1;
- (id)tailRunLoopInvocation;
- (id)_controllerForClientProxy:(id)arg1 withDictKey:(id)arg2;
- (id)_controllerForClientDOProxy:(id)arg1;
- (id)_controllerForClientXPCConn:(id)arg1;
- (id)_mapClientXPCConnToController:(id)arg1;
- (id)_mapClientDOProxyToController:(id)arg1;
- (void)_sendKey:(id)arg1;
- (void)_sendKeyToView:(unsigned short)arg1;
- (BOOL)_isValidKeyForCandidateView:(id)arg1;
- (unsigned short)_remapKeyEventForCandidateKeylayout:(unsigned short)arg1;
- (void)_hideWindow;
- (BOOL)_serverGetsFirstShotAtWindowEvents;
- (BOOL)_windowIsOpen;
- (BOOL)_isMenuKeyEquivalent:(id)arg1 modifierMask:(unsigned long long)arg2;
- (void)_setCachedMenu:(id)arg1;
- (id)keyboardService;
- (void)dealloc;
- (id)initWithName:(id)arg1 controllerClass:(Class)arg2 delegateClass:(Class)arg3;
- (BOOL)paletteWillTerminate;
- (id)initWithName:(id)arg1 bundleIdentifier:(id)arg2;
- (void)endpointCheckinRequestedFromLaunchAgent:(id)arg1;
- (void)registerConnectionAfterDidFinishLaunch:(id)arg1;
- (void)performDelayedEndpointCheckin:(id)arg1;
- (void)registerIMKXPCEndpointWithLaunchAgent;
- (BOOL)_createConnection;
- (oneway void)ironwoodPlaceholderWasInvalidated:(id)arg1;
- (oneway void)ironwoodTextWasCorrected:(id)arg1;
- (oneway void)sendInputSessionSessAction:(unsigned int)arg1 timestamp:(double)arg2 withInfo:(id)arg3;
- (oneway void)sendInputSessionSessAction:(unsigned int)arg1;
- (oneway void)invalidateClientGeometry;
//- (void)recognizedEventsWithReply:(CDUnknownBlockType)arg1;
//- (void)recognizedEventsWithClientAsync:(BOOL)arg1 reply:(CDUnknownBlockType)arg2;
//- (void)doCommandBySelector:(SEL)arg1 commandDictionary:(id)arg2 reply:(CDUnknownBlockType)arg3;
- (oneway void)doCommandBySelector:(SEL)arg1 commandDictionary:(id)arg2;
//- (void)didCommandBySelector:(SEL)arg1 reply:(CDUnknownBlockType)arg2;
- (oneway void)hidePalettes;
//- (void)commitCompositionWithReply:(CDUnknownBlockType)arg1;
- (oneway void)commitCompositionWithDiscardMarkedTextFlag:(BOOL)arg1;
- (oneway void)commitComposition;
//- (void)handleEvent:(bycopy id)arg1 characterIndex:(unsigned long long)arg2 edge:(unsigned long long)arg3 reply:(CDUnknownBlockType)arg4;
//- (void)handleEvent:(bycopy id)arg1 characterIndex:(unsigned long long)arg2 edge:(unsigned long long)arg3 asyncClient:(BOOL)arg4 reply:(CDUnknownBlockType)arg5;
/*- (void)menusDictionaryWithReply:(CDUnknownBlockType)arg1;
- (void)menusDictionaryWithClientAsync:(BOOL)arg1 reply:(CDUnknownBlockType)arg2;
- (void)modesWithReply:(CDUnknownBlockType)arg1;
- (void)modesWithClientAsync:(BOOL)arg1 reply:(CDUnknownBlockType)arg2;
- (void)setValue:(id)arg1 forTag:(unsigned long long)arg2 reply:(CDUnknownBlockType)arg3;*/
- (oneway void)setValue:(id)arg1 forTag:(unsigned long long)arg2;
/*- (void)valueForTag:(unsigned long long)arg1 reply:(CDUnknownBlockType)arg2;
- (void)valueForTag:(unsigned long long)arg1 asyncClient:(BOOL)arg2 reply:(CDUnknownBlockType)arg3;*/
- (oneway void)sessionFinished;
//- (void)deactivateServerWithReply:(CDUnknownBlockType)arg1;
- (oneway void)deactivateServer;
//- (void)activateServerWithReply:(CDUnknownBlockType)arg1;
- (oneway void)activateServer;
- (double)replyTimeout;
- (void)replyWaitCount_decrementWithLocking;
- (void)replyWaitCount_incrementWithLocking;
- (void)replyWaitCount_unlock;
- (void)replyWaitCount_lockDecrement;
- (void)replyWaitCount_lockIncrement;
- (int)replyWaitCount_testWithLocking;
- (BOOL)listener:(id)arg1 shouldAcceptNewConnection:(id)arg2;
- (void)_invalidateConnectionsAsNecessary:(id)arg1;

@end


#endif /* InputMethodKit_Private_h */
