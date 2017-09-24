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
internal class AppDelegate: NSObject, NSApplicationDelegate,  NSXPCListenerDelegate {
    @IBOutlet private weak var window: NSWindow!
    func applicationDidFinishLaunching(_ aNotification: Notification) {
        NSLog("EmojiIM launching: \(kBuiltDate)(\(kRevision))")

        server = IMKServer(name: "EmojiInputSession", bundleIdentifier: Bundle.main.bundleIdentifier)
/*        _connectionToService = [[NSXPCConnection alloc] initWithServiceName:@
        _connectionToService.remoteObjectInterface = [NSXPCInterface interfaceWithProtocol:@protocol(emojirowProtocol)];
        [_connectionToService resume];*/
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }

    func listener(_ listener: NSXPCListener, shouldAcceptNewConnection newConnection: NSXPCConnection) -> Bool {
        NSLog("%@", "\(#function)")
        return true
    }
}
