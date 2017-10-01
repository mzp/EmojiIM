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
open class EmojiInputController: IMKInputController {
    private let automaton: EmojiAutomaton = EmojiAutomaton()
    private let touchBarController: IMKUICandidateTouchBarController = IMKUICandidateTouchBarController()

    // swiftlint:disable:next implicitly_unwrapped_optional
    public override init!(server: IMKServer!, delegate: Any!, client inputClient: Any!) {
        NSLog("%@", "\(#function)")
        super.init(server: server, delegate: delegate, client: inputClient)

        guard let client = inputClient as? IMKTextInput else {
            return
        }
        automaton.markedText.signal.observeValues { text in
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
        NSLog("%@", "\(#function) \(event)")

        guard let c = sender as? IPMDServerClientWrapper else {
            return true
        }
        touchBarController.numberOfSimilarWidthCandidates = 4
        touchBarController.reload(withUpdatingFirstCandidate: true)
        c.dismissFunctionRowItemTextInputView()
        c.presentFunctionRowItemTextInputView()

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

    @objc
    open func functionRowItemTextInputViewController() -> NSViewController! {
        NSLog("%@", "\(#function) => \(touchBarController.viewController)")
        return touchBarController.viewController
    }
}

extension EmojiInputController /* IMKStateSetting*/ {
    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func activateServer(_ sender: Any!) {
        touchBarController.delegate = self
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

extension EmojiInputController: IMKUIDelegate {
    public func candidateData(for controller: IMKUICandidateController) -> IMKCandidateData {
        NSLog("%@", "\(#function)")

        return IMKCandidateData(array: [
            make(text: "🍣", annotation: "すし"),
            make(text: "🦐", annotation: "えび"),
            make(text: "🦀", annotation: "かに"),
            make(text: "🍻", annotation: "びーる")
        ])
    }

    private func make(text: String, annotation: String) -> IMKCandidateDefinitionUnit {
        return IMKCandidateDefinitionUnit() ※ {
            $0.text = text
            $0.annotation = annotation
        }
    }
}
