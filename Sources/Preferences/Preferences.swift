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
        let label = NSTextField.label(text: "🍣") ※ {
            $0.font = NSFont.systemFont(ofSize: 120)
        }
        let autolayout = mainView.northLayoutFormat([:], ["label": label])
        autolayout("H:|[label]|")
        autolayout("V:|[label]|")
        NSLog("%@", "\(#function) [EmojiIM]")
    }
}
