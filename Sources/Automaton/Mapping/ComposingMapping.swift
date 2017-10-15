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
                    context.candidates.swap(context.dictionary.find(prefix: text))
                }
            },
            UserInput.typeof(.backspace) <|> {
                $0 == .composing && (context.markedText.value.utf8.count <= 1)
                } => .normal <|> { _ in
                    context.markedText.swap("")
                    context.candidates.swap([])
            },
            UserInput.typeof(.backspace) <|> .composing  => .composing <|>
                context.markedText.modify { $0.removeLast() },
            UserInput.typeof(.enter) <|> .composing => .normal <|> { _ in
                context.text.send(value: context.markedText.value)
                context.markedText.swap("")
                context.candidates.swap([])
            },
            UserInput.typeof(.navigation) <|> .composing => .selection  <|> {
                _ = $0.originalEvent.map {
                    context.candidateEvent.send(value: $0)
                }
            }
        ]
    }
}
