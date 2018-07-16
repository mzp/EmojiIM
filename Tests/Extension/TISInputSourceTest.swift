//
//  TISInputSourceTest.swift
//  Tests
//
//  Created by mzp on 2018/07/16.
//  Copyright © 2018 mzp. All rights reserved.
//

import XCTest

internal class TISInputSourceTest: XCTestCase {
    func testKeyboardLayouts() {
        let xs = TISInputSource.keyboardLayouts()
        XCTAssertNotNil(xs)
        XCTAssertFalse(xs?.isEmpty ?? false)
    }

    func testScriptCode() {
        let xs = TISInputSource.keyboardLayouts()?
            .filter { $0.scriptCode == 0 }
            .map { $0.localizedName }
        XCTAssertNotNil(xs)
        XCTAssertTrue(xs?.contains("ABC") ?? false)
        XCTAssertFalse(xs?.contains("Azeri") ?? false)
    }
}
