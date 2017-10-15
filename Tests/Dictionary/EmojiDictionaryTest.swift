//
//  EmojiDictionaryTest.swift
//  Tests
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//

import XCTest

internal class EmojiDictionaryTest: XCTestCase {
    private let dictionary: EmojiDictionary = EmojiDictionary()

    func testFind() {
        let sushi = dictionary.find(prefix: ":sus")
        XCTAssertTrue(sushi.contains("🍣"), "\(sushi) doesn't contain 🍣")

        let beer = dictionary.find(prefix: ":beer")
        XCTAssertTrue(beer.contains("🍺"), "\(beer) doesn't contain 🍺")
        XCTAssertTrue(beer.contains("🍻"), "\(beer) doesn't contain 🍻")
    }
}
