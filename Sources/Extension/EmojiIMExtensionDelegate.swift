//
// EmojiIMExtensionDelegate.swift
//  EmojiIM_Extension
//
//  Created by mzp on 2017/09/29.
//  Copyright © 2017 mzp. All rights reserved.
//

import Foundation
import InputMethodKit

private var server: IMKServer?

@objc(EmojiIMExtensionDelegate)
public class EmojiIMExtensionDelegate: NSObject, IMKExtensionDelegate {
    public func extensionDidLaunch() {
        NSLog("%@", "Launch \(kBuiltDate) \(kRevision)")
//        let bundle = Bundle.main
//        let name = bundle.infoDictionary?["InputMethodConnectionName"] as? String
//        server = IMKServer(name: name, bundleIdentifier: bundle.bundleIdentifier)
    }

    public func extensionWillTerminate() {
    }
}
