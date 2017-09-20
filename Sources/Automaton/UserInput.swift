//
//  UserInput.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//

public enum UserInput {
    case input(text: String)
    case backspace
    case enter

    static func isInput(_ state: UserInput) -> Bool {
        switch state {
        case .input:
            return true
        default:
            return false
        }
    }

    func ifInput(action: (String) -> Void) {
        switch self {
        case .input(text: let text):
            action(text)
        default:
            ()
        }
    }
}

extension UserInput: Equatable {
    public static func == (lhs: UserInput, rhs: UserInput) -> Bool {
        switch (lhs, rhs) {
        case (.enter, .enter):
            return true
        case (.backspace, .backspace):
            return true
        case (.input(text: let text1), .input(text: let text2)):
            return text1 == text2
        default:
            return false
        }
    }
}
