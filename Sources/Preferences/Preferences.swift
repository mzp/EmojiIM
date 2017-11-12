//
//  Preferences.swift
//  EmojiIM
//
//  Created by mzp on 2017/11/04.
//  Copyright © 2017 mzp. All rights reserved.
//

import Ikemen
import NorthLayout
import PreferencePanes

@objc(Preferences)
public class Preferences: NSPreferencePane {
    override public func mainViewDidLoad() {
        let label = NSTextField() ※ {
            $0.stringValue = "🍣"
            $0.font = NSFont.systemFont(ofSize: 120)
            $0.drawsBackground = false
            $0.isBordered = false
            $0.isEditable = false
            $0.isSelectable = false
        }
        let autolayout = mainView.northLayoutFormat([:], ["label": label])
        autolayout("H:|[label]|")
        autolayout("V:|[label]|")
        NSLog("%@", "\(#function) [EmojiIM]")
    }
}
