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
    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func inputText(_ string: String!, client sender: Any!) -> Bool {
        NSLog("EmojiIM: \(string): \(sender)")

        guard let client = sender as? IMKTextInput else {
            return false
        }

        switch string {
        case "m":
            client.insertText("💸", replacementRange: NSRange(location: NSNotFound, length: NSNotFound))
        case "s":
            client.insertText("🍣", replacementRange: NSRange(location: NSNotFound, length: NSNotFound))
        default:
            client.insertText(string, replacementRange: NSRange(location: NSNotFound, length: NSNotFound))
        }

        return true
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

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func setValue(_ value: Any?, forKey key: String) {
        NSLog("setValue(\(value ?? "nil"), forKey: \(key))")
    }
}
