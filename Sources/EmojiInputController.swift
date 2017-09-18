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
        client.insertText("🍣", replacementRange: NSRange(location: NSNotFound, length: NSNotFound))
        return true
    }

    open override func menu() -> NSMenu! {
        return NSMenu(title: "EmojiIM") ※ { menu in
            menu.addItem(NSMenuItem(title: kBuiltDate, action: nil, keyEquivalent: ""))
            menu.addItem(NSMenuItem(title: kRevision, action: nil, keyEquivalent: ""))
        }
    }
}
