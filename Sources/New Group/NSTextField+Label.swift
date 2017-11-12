//
//  NSTextField+Label.swift
//  EmojiIM
//
//  Created by mzp on 2017/11/12.
//  Copyright © 2017 mzp. All rights reserved.
//
import Ikemen

extension NSTextField {
    class func label(text: String) -> NSTextField {
        return NSTextField() ※ {
            $0.stringValue = text
            $0.drawsBackground = false
            $0.isBordered = false
            $0.isEditable = false
            $0.isSelectable = false
        }
    }
}
