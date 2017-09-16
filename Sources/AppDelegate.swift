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
        server = IMKServer(name: "EmojiInputSession", bundleIdentifier: Bundle.main.bundleIdentifier)
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }
}
