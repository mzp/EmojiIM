//
//  AutomatonTest.swift
//  UnitTest
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//

import XCTest

open class AutomatonTest: XCTestCase {
    // swiftlint:disable:next implicitly_unwrapped_optional
    private var automaton: EmojiAutomaton!

    override open func setUp() {
        super.setUp()
        self.automaton = EmojiAutomaton()
    }

    open func testDeinit() {
        weak var target = EmojiAutomaton()
        XCTAssertNil(target)
    }

    open func testTransition() {
        XCTAssertEqual(automaton.state.value, .normal)

        _ = automaton.handle(UserInput(eventType: .enter))
        XCTAssertEqual(automaton.state.value, .normal)

        _ = automaton.handle(UserInput(eventType: .input(text: "a")))
        XCTAssertEqual(automaton.state.value, .normal)

        _ = automaton.handle(UserInput(eventType: .colon))
        XCTAssertEqual(automaton.state.value, .composing)

        _ = automaton.handle(UserInput(eventType: .input(text: "b")))
        XCTAssertEqual(automaton.state.value, .composing)

        _ = automaton.handle(UserInput(eventType: .enter))
        XCTAssertEqual(automaton.state.value, .normal)
    }

    open func testComposing() {
        var text: String = ""
        automaton.text.observeValues { text.append($0) }

        _ = automaton.handle(UserInput(eventType: .colon))
        XCTAssertEqual(automaton.markedText.value, ":")

        _ = automaton.handle(UserInput(eventType: .input(text: "a")))
        XCTAssertEqual(automaton.markedText.value, ":a")

       _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertEqual(automaton.markedText.value, ":")

        _ = automaton.handle(UserInput(eventType: .enter))
        XCTAssertEqual(automaton.markedText.value, "")
        XCTAssertEqual(text, ":")
    }

    open func testCandidates() {
        _ = automaton.handle(UserInput(eventType: .colon))
        XCTAssertEqual(automaton.candidates.value, [])

        _ = automaton.handle(UserInput(eventType: .input(text: "s")))
        XCTAssertTrue(automaton.candidates.value.contains("🍣"), "\(automaton.candidates.value) doesn't contain 🍣")

        _ = automaton.handle(UserInput(eventType: .enter))
        XCTAssertEqual(automaton.candidates.value, [])
    }

    open func testBackspaceReturnNormal() {
        _ = automaton.handle(UserInput(eventType: .colon))
        _ = automaton.handle(UserInput(eventType: .input(text: "a")))
        _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertEqual(automaton.state.value, .composing)
        _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertEqual(automaton.state.value, .normal)
    }

    open func testHandled() {
        XCTAssertFalse(automaton.handle(UserInput(eventType: .input(text: "a"))))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .colon)))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .input(text: "a"))))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .enter)))
        XCTAssertFalse(automaton.handle(UserInput(eventType: .enter)))
    }
}
