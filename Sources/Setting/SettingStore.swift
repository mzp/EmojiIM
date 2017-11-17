//
//  SettingStore.swift
//  EmojiIM
//
//  Created by mzp on 2017/11/13.
//  Copyright © 2017 mzp. All rights reserved.
//
import Cocoa

internal class SettingStore {
    private let kSuiteName: String = "jp.mzp.inputmethod.EmojiIM"

    func setKeyboardLayout(inputSourceID: String) {
        userDefaults?.set(inputSourceID, forKey: "keyboardLayout")
        userDefaults?.synchronize()
    }

    func keyboardLayout() -> String {
        return (userDefaults?.value(forKey: "keyboardLayout") as? String) ?? "com.apple.keylayout.US"
    }

    private var inSandbox: Bool {
        return Bundle.main.bundleIdentifier == kSuiteName
    }

    private lazy var userDefaults: UserDefaults? = {
        if inSandbox {
            return UserDefaults.standard
        } else {
            return UserDefaults(suiteName: suiteName)
        }
    }()

    private var suiteName: String {
        return "\(NSHomeDirectory())/Library/Containers/\(kSuiteName)/Data/Library/Preferences/\(kSuiteName)"
    }
}
