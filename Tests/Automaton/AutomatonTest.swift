//
//  AutomatonTest.swift
//  UnitTest
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//

import XCTest

internal class AutomatonTest: XCTestCase {
    // swiftlint:disable:next implicitly_unwrapped_optional
    private var automaton: EmojiAutomaton!

    override func setUp() {
        super.setUp()
        self.automaton = EmojiAutomaton()
    }

    func testDeinit() {
        weak var target = EmojiAutomaton()
        XCTAssertNil(target)
    }

    func testTransition() {
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

    func testTransitionSelection() {
        _ = automaton.handle(UserInput(eventType: .colon))
        XCTAssertEqual(automaton.state.value, .composing)

        _ = automaton.handle(UserInput(eventType: .input(text: "a")))
        XCTAssertEqual(automaton.state.value, .composing)

        _ = automaton.handle(UserInput(eventType: .navigation))
        XCTAssertEqual(automaton.state.value, .selection)

        _ = automaton.handle(UserInput(eventType: .navigation))
        XCTAssertEqual(automaton.state.value, .selection)

        _ = automaton.handle(UserInput(eventType: .enter))
        XCTAssertEqual(automaton.state.value, .selection)

        _ = automaton.handle(UserInput(eventType: .selected(candidate: "a")))
        XCTAssertEqual(automaton.state.value, .normal)
    }

    func testComposing() {
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

    func testCandidates() {
        var text: String = ""
        automaton.text.observeValues { text.append($0) }

        _ = automaton.handle(UserInput(eventType: .colon))
        XCTAssertEqual(automaton.candidates.value, [])

        _ = automaton.handle(UserInput(eventType: .input(text: "s")))
        XCTAssertTrue(automaton.candidates.value.contains("🍣"), "\(automaton.candidates.value) doesn't contain 🍣")

        _ = automaton.handle(UserInput(eventType: .input(text: "e")))
        XCTAssertFalse(automaton.candidates.value.contains("🍣"), "\(automaton.candidates.value) contains 🍣")

        _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertTrue(automaton.candidates.value.contains("🍣"), "\(automaton.candidates.value) doesn't contain 🍣")

        _ = automaton.handle(UserInput(eventType: .navigation))
        XCTAssertTrue(automaton.candidates.value.contains("🍣"), "\(automaton.candidates.value) doesn't contain 🍣")

        _ = automaton.handle(UserInput(eventType: .selected(candidate: "🍣")))
        XCTAssertEqual(automaton.candidates.value, [])
        XCTAssertEqual(text, "🍣")
    }

    func testBackspaceReturnNormal() {
        _ = automaton.handle(UserInput(eventType: .colon))
        _ = automaton.handle(UserInput(eventType: .input(text: "a")))
        _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertEqual(automaton.state.value, .composing)
        _ = automaton.handle(UserInput(eventType: .backspace))
        XCTAssertEqual(automaton.state.value, .normal)
    }

    func testHandled() {
        XCTAssertFalse(automaton.handle(UserInput(eventType: .input(text: "a"))))
        XCTAssertFalse(automaton.handle(UserInput(eventType: .navigation)))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .colon)))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .input(text: "a"))))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .navigation)))
        XCTAssertTrue(automaton.handle(UserInput(eventType: .selected(candidate: "a"))))
        XCTAssertFalse(automaton.handle(UserInput(eventType: .enter)))
    }
}
