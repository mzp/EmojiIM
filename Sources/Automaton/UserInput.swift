//
//  UserInput.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//
import AppKit

internal class UserInput {
    enum EventType {
        case backspace
        case colon
        case enter
        case input(text: String)
        case navigation
        case select(candidate: String)
        case selected(candidate: String)
    }
    let eventType: EventType
    let originalEvent: NSEvent?

    // MARK: - predicate
    static func typeof(_ eventType: EventType) -> (UserInput) -> Bool {
        return { $0.eventType == eventType }
    }

    static func any(_ state: UserInput) -> Bool {
        return true
    }

    static func isInput(_ state: UserInput) -> Bool {
        switch state.eventType {
        case .input:
            return true
        default:
            return false
        }
    }

    static func isSelect(_ state: UserInput) -> Bool {
        switch state.eventType {
        case .select:
            return true
        default:
            return false
        }
    }

    static func isSelected(_ state: UserInput) -> Bool {
        switch state.eventType {
        case .selected:
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

    func ifSelect(action: (String) -> Void) {
        switch self.eventType {
        case .select(candidate: let candidate):
            action(candidate)
        default:
            ()
        }
    }

    func ifSelected(action: (String) -> Void) {
        switch self.eventType {
        case .selected(candidate: let candidate):
            action(candidate)
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
    static func == (lhs: UserInput.EventType, rhs: UserInput.EventType) -> Bool {
        switch (lhs, rhs) {
        case (.backspace, .backspace):
            return true
        case (.colon, .colon):
            return true
        case (.enter, .enter):
            return true
        case (.input(text: let text1), .input(text: let text2)):
            return text1 == text2
        case (.navigation, .navigation):
            return true
        case (.selected(candidate: let candidate1), .selected(candidate: let candidate2)):
            return candidate1 == candidate2
        default:
            return false
        }
    }
}
