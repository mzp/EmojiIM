//
//  SelectionMapping.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveAutomaton

internal class SelectionMapping: MappingDefinition {
    func mapping(context: MappingContext) -> [ActionMapping<InputMethodState, UserInput>] {
        return [
            UserInput.isSelected <|> .selection => .normal <|> {
                $0.ifSelected {
                    context.text.send(value: $0)
                }
                context.clear()
            },
            UserInput.any <|> .selection => .selection <|> context.forward
        ]
    }
}
