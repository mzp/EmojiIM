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
public class EMIMMainThreadInit: NSObject {
    private static var server: IMKServer?

    static func mainThreadIMKInit() {
        NSLog("\(#function)")
        self.server = IMKServer(name: "EmojiInputSession", bundleIdentifier: Bundle.main.bundleIdentifier)
    }
}
