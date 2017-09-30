//
//  EMIMMainThreadInit.swift
//  EmojiIM_Extension
//
//  Created by mzp on 2017/09/29.
//  Copyright © 2017 mzp. All rights reserved.
//

import Foundation
import InputMethodKit

@objc(EMIMMainThreadInit)
public class EMIMMainThreadInit: NSObject, IMKExtensionMainInit {
    private static var server: IMKServer?

    public static func mainThreadIMKInit() {
        NSLog("Launch \(#function)")
        self.server = IMKServer(name: "EmojiInputSession", bundleIdentifier: Bundle.main.bundleIdentifier)
    }
}
