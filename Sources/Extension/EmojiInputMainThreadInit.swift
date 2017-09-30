//
//  EmojiInputMainThreadInit.swift
//  EmojiIM_Extension
//
//  Created by mzp on 2017/09/29.
//  Copyright © 2017 mzp. All rights reserved.
//

import Foundation
import InputMethodKit

private var server: IMKServer?

@objc(EmojiInputMainThreadInit)
public class EmojiInputMainThreadInit: NSObject, IMKExtensionMainInit {
    public static func mainThreadIMKInit() {
        NSLog("%@", "Launch \(kBuiltDate) \(kRevision)")
        let bundle = Bundle.main
        let name = bundle.infoDictionary?["InputMethodConnectionName"] as? String
        server = IMKServer(name: name, bundleIdentifier: bundle.bundleIdentifier)
    }
}
