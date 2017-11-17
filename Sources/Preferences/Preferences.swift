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
        let revisionLabel = NSTextField.label(text: "Revision:") ※ {
            $0.alignment = .right
        }
        let revision = NSTextField.label(text: kRevision)
        let builtDateLabel = NSTextField.label(text: "Built date:") ※ {
            $0.alignment = .right
        }
        let builtDate = NSTextField.label(text: kBuiltDate)

        let autolayout = mainView.northLayoutFormat(
            [
                "p": 20,
                "m": 10,
                "w": 60,
                "h": 16
            ],
            [
                "revisionLabel": revisionLabel,
                "revision": revision,
                "builtDateLabel": builtDateLabel,
                "builtDate": builtDate
            ]
        )
        autolayout("H:|-p-[builtDateLabel(==w)]-m-[builtDate]-p-|")
        autolayout("H:|-p-[revisionLabel(==w)]-m-[revision]-p-|")
        autolayout("V:|-p-[builtDateLabel(==h)]-m-[revisionLabel(==h)]|")
        autolayout("V:|-p-[builtDate(==h)]-m-[revision(==h)]|")
    }
}
