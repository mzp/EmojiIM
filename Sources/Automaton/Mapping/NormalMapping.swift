//
//  NormalMapping.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveAutomaton

internal class NormalMapping: MappingDefinition {
    func mapping(context: MappingContext) -> [ActionMapping<InputMethodState, UserInput>] {
        return [
            UserInput.typeof(.colon) <|> .normal => .composing <|> { _ in
                context.markedText.swap(":")
                context.candidates.swap([])
            }
        ]
    }
}
