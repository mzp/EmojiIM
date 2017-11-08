//
//  Preferences.swift
//  EmojiIM
//
//  Created by mzp on 2017/11/04.
//  Copyright © 2017 mzp. All rights reserved.
//

import PreferencePanes

@objc(Preferences)
public class Preferences: NSPreferencePane {
    override public func mainViewDidLoad() {
        NSLog("%@", "\(#function) [EmojiIM]")
    }
}
