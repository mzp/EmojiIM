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
        // Insert code here to initialize your application
        let identifier = Bundle.main.bundleIdentifier
        server = IMKServer(name: "EmojiInputSession", bundleIdentifier: identifier)
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }
}
