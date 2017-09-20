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

    // swiftlint:disable:next implicitly_unwrapped_optional
    public override init!(server: IMKServer!, delegate: Any!, client inputClient: Any!) {
        super.init(server: server, delegate: delegate, client: inputClient)

        guard let client = inputClient as? IMKTextInput else {
            return
        }
        automaton.markedText.signal.observeValues { text in
            guard let text = text else {
                return
            }
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
        NSLog("handle(\(event)")

        if event.keyCode == 36 {
            return automaton.handle(.enter)
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
