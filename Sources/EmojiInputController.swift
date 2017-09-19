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
    private var marked: String = ""

    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func handle(_ event: NSEvent!, client sender: Any!) -> Bool {
        NSLog("handle(\(event)")

        guard let client = sender as? IMKTextInput else {
            return false
        }
        guard let str = event.characters else {
            return false
        }

        let notFound = NSRange(location: NSNotFound, length: NSNotFound)

        if event.keyCode == 36 {
            client.setMarkedText("", selectionRange: notFound, replacementRange: notFound)
            client.insertText(marked, replacementRange: notFound)
            marked = ""
        } else {
            marked += str
            client.setMarkedText(marked, selectionRange: notFound, replacementRange: notFound)
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
