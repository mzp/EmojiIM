//
//  ComposingMapping.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//
import ReactiveAutomaton

internal class ComposingMapping: MappingDefinition {
    func mapping(context: MappingContext) -> [ActionMapping<InputMethodState, UserInput>] {
        return [
            UserInput.isInput <|> .composing => .composing <|> {
                $0.ifInput { text in
                    context.markedText.modify { $0.append(text) }
                    context.candidates.swap(context.dictionary.find(prefix: context.markedText.value))
                }
            },
            UserInput.typeof(.backspace) <|> {
                $0 == .composing && (context.markedText.value.utf8.count <= 1)
            } => .normal <|> context.clear(),
            UserInput.typeof(.backspace) <|> .composing  => .composing <|> { _ in
                context.markedText.modify { $0.removeLast() }
                context.candidates.swap(context.dictionary.find(prefix: context.markedText.value))
            },
            UserInput.typeof(.enter) <|> .composing => .normal <|> { _ in
                context.text.send(value: context.markedText.value)
                context.clear()
            },
            UserInput.typeof(.navigation) <|> .composing => .selection  <|> context.forward
        ]
    }
}
