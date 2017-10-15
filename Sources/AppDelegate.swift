//
//  AppDelegate.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/11.
//  Copyright © 2017 mzp. All rights reserved.
//

import Cocoa
import InputMethodKit

private var server: IMKServer?

@NSApplicationMain
internal class AppDelegate: NSObject, NSApplicationDelegate {

    @IBOutlet private weak var window: NSWindow!

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        NSLog("EmojiIM launching: \(kBuiltDate)(\(kRevision))")
        let bundle = Bundle.main
        server = IMKServer(name: bundle.infoDictionary?["InputMethodConnectionName"] as? String,
                           bundleIdentifier: bundle.bundleIdentifier)
    }

    func applicationWillTerminate(_ aNotification: Notification) {
    }
}
