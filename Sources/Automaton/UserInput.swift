//
//  UserInput.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//
import AppKit

public class UserInput {
    enum EventType {
        case input(text: String)
        case backspace
        case enter
        case colon
        case other
    }
    let eventType: EventType
    let originalEvent: NSEvent?

    // MARK: - predicate
    static func typeof(_ eventType: EventType) -> (UserInput) -> Bool {
        return { $0.eventType == eventType }
    }

    static func isInput(_ state: UserInput) -> Bool {
        switch state.eventType {
        case .input:
            return true
        default:
            return false
        }
    }

    func ifInput(action: (String) -> Void) {
        switch self.eventType {
        case .input(text: let text):
            action(text)
        default:
            ()
        }
    }

    // MARK: - initialize
    init(eventType: EventType, originalEvent: NSEvent? = nil) {
        self.eventType = eventType
        self.originalEvent = originalEvent
    }
}

extension UserInput.EventType: Equatable {
    public static func == (lhs: UserInput.EventType, rhs: UserInput.EventType) -> Bool {
        switch (lhs, rhs) {
        case (.enter, .enter):
            return true
        case (.backspace, .backspace):
            return true
        case (.colon, .colon):
            return true
        case (.input(text: let text1), .input(text: let text2)):
            return text1 == text2
        case (.other, .other):
            return true
        default:
            return false
        }
    }
}
