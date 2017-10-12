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
    private let candidates: IMKCandidates

    // swiftlint:disable:next implicitly_unwrapped_optional
    public override init!(server: IMKServer!, delegate: Any!, client inputClient: Any!) {
        self.candidates = IMKCandidates(server: server, panelType: kIMKMain)
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
        automaton.candidates.signal.observeValues {
            if $0.isEmpty {
                self.candidates.hide()
            } else {
                self.candidates.update()
                self.candidates.show(kIMKLocateCandidatesBelowHint)
            }
        }
    }

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func handle(_ event: NSEvent!, client sender: Any!) -> Bool {
        NSLog("handle(\(event)")

        if event.keyCode == 36 {
            return automaton.handle(.enter)
        } else if event.keyCode == 51 {
            return automaton.handle(.backspace)
        } else if let text = event.characters {
            if text == ":" {
                return automaton.handle(.colon)
            } else {
                return automaton.handle(.input(text: text))
            }
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
        self.candidates.hide()
    }

    open override func setValue(_ value: Any?, forKey key: String) {
        NSLog("setValue(\(value ?? "nil"), forKey: \(key))")
    }
}

extension EmojiInputController {
    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func candidates(_ sender: Any!) -> [Any] {
        return automaton.candidates.value
    }

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func candidateSelected(_ candidateString: NSAttributedString!) {
        NSLog("%@", "\(#function)")
    }

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func candidateSelectionChanged(_ candidateString: NSAttributedString!) {
        NSLog("%@", "\(#function)")
    }
}
