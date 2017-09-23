//
//  EmojiInputController.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/14.
//  Copyright © 2017 mzp. All rights reserved.
//

import Ikemen
import InputMethodKit

@objc(EmojiInputController)
open class EmojiInputController: IMKInputController, IMKCandidateControllerDelegate {
    public func textClient() -> Any! {
        NSLog("event textClient")
        return self.client()
    }

    public func windowType() -> Int64 {
        NSLog("event widowType")
        return 0
    }

    public func displayMethod() -> String! {
        NSLog("event displayMethod")
        return "Frequency"
    }

    public func sortingMethods() -> [Any]! {
        NSLog("event sortingMethods")
        return ["Frequency"]
    }

    public func candidates(forSortingMethod arg1: String!) -> [Any]! {
        NSLog("event candidates")
        return ["a", "b"]
    }

    private let automaton: EmojiAutomaton = EmojiAutomaton()
    private let touchbar = IMKUICandidateTouchBarController()
    private let screen = IMKUIWindowBasedCandidateController()

    // swiftlint:disable:next implicitly_unwrapped_optional
    public override init!(server: IMKServer!, delegate: Any!, client inputClient: Any!) {
        super.init(server: server, delegate: delegate, client: inputClient)
        guard let client = inputClient as? IMKTextInput else {
            return
        }

        let info = IMKUIInformation.shared()
        info?.touchBarController = touchbar
        touchbar?.delegate = IMKUICandidateTouchBarOnScreenBridge.shared()
        info?.visibleOnscreenController = screen
        screen?.delegate = self

        automaton.markedText.signal.observeValues { [weak self] text in
            self?.screen?.reload(withUpdatingFirstCandidate: true)
            let notFound = NSRange(location: NSNotFound, length: NSNotFound)
            client.setMarkedText(text, selectionRange: notFound, replacementRange: notFound)
        }
        automaton.text.observeValues {
            let notFound = NSRange(location: NSNotFound, length: NSNotFound)
            client.insertText($0, replacementRange: notFound)
        }
    }

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func handle(_ event: NSEvent!, client sender: Any!) -> Bool {
        NSLog("------")
        let info = IMKUIInformation.shared()
        NSLog("%@", "TouchBar \(info?.touchBarController)")
        NSLog("%@", "TouchBar.delegate \(info?.touchBarController?.delegate)")
        NSLog("%@", "VisibleScreen \(info?.visibleOnscreenController)")
        NSLog("%@", "VisibleScreen.delegate \(info?.visibleOnscreenController?.delegate)")
        NSLog("------")

        if event.keyCode == 36 {
            return automaton.handle(.enter)
        } else if event.keyCode == 51 {
            return automaton.handle(.backspace)
        } else if let text = event.characters {
            return automaton.handle(.input(text: text))
        } else {
            return false
        }
    }

    open override func menu() -> NSMenu! {
        return NSMenu(title: "EmojiIM") ※ { menu in
            menu.addItem(NSMenuItem(title: kBuiltDate, action: nil, keyEquivalent: ""))
            menu.addItem(NSMenuItem(title: kRevision, action: nil, keyEquivalent: ""))
        }
    }

    open override func candidates(_ sender: Any!) -> [Any]! {
        NSLog("event candidates:")
        return ["d", "e"]
    }
}

extension EmojiInputController /* IMKStateSetting*/ {
    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func activateServer(_ sender: Any!) {
        NSLog("activateServer\(sender)")
        guard let client = sender as? IMKTextInput else {
            return
        }
        client.overrideKeyboard(withKeyboardNamed: "com.apple.keylayout.US")
    }

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func deactivateServer(_ sender: Any!) {
        NSLog("deactivateServer\(sender)")
    }

    open override func setValue(_ value: Any?, forKey key: String) {
        NSLog("setValue(\(value ?? "nil"), forKey: \(key))")
    }
}
