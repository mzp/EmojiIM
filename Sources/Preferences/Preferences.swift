//
//  Preferences.swift
//  EmojiIM
//
//  Created by mzp on 2017/11/04.
//  Copyright © 2017 mzp. All rights reserved.
//

import CoreFoundation
import Ikemen
import NorthLayout
import PreferencePanes
import ReactiveCocoa

@objc(Preferences)
public class Preferences: NSPreferencePane {
    private let store: SettingStore = SettingStore()
    private lazy var keyboardLayouts: [TISInputSource]? = TISInputSource.keyboardLayouts()

    override public func mainViewDidLoad() {
        let keyboardLabel = NSTextField.label(text: "Keybaord:") ※ {
            $0.alignment = .right
        }
        let keyboard = NSPopUpButton() ※ {
            for layout in keyboardLayouts ?? [] {
                $0.addItem(withTitle: layout.localizedName)
            }
            $0.reactive.selectedIndexes.observeValues {
                if let layout = self.keyboardLayouts?[$0] {
                    self.store.setKeyboardLayout(inputSourceID: layout.inputSourceID)
                }
            }
            if let index = keyboardLayouts?.index(where: { $0.inputSourceID == store.keyboardLayout() }) {
                $0.selectItem(at: index)
            }
        }
        let revisionLabel = NSTextField.label(text: "Revision:")  ※ {
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
                "keyboardLabel": keyboardLabel,
                "keyboard": keyboard,
                "revisionLabel": revisionLabel,
                "revision": revision,
                "builtDateLabel": builtDateLabel,
                "builtDate": builtDate
            ]
        )
        autolayout("H:|-p-[keyboardLabel(==w)]-m-[keyboard]-p-|")
        autolayout("H:|-p-[builtDateLabel(==w)]-m-[builtDate]-p-|")
        autolayout("H:|-p-[revisionLabel(==w)]-m-[revision]-p-|")
        autolayout("V:|-p-[keyboardLabel(==h)]-m-[builtDateLabel(==h)]-m-[revisionLabel(==h)]|")
        autolayout("V:|-p-[keyboard(==h)]-m-[builtDate(==h)]-m-[revision(==h)]|")
    }
}
