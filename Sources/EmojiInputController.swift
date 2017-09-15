//
//  EmojiInputController.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/14.
//  Copyright © 2017 mzp. All rights reserved.
//

import InputMethodKit

@objc(EmojiInputController)
open class EmojiInputController: IMKInputController {
    // swiftlint:disable:next implicitly_unwrapped_optional
    open override func inputText(_ string: String!, client sender: Any!) -> Bool {
        NSLog("EmojiIM: \(string)")
        return false
    }
}
