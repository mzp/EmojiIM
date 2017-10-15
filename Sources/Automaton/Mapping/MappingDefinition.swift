//
//  MappingDefinition.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveSwift
import Result

internal struct MappingContext {
    let candidateEvent: Signal<NSEvent, NoError>.Observer
    let candidates: MutableProperty<[String]>
    let dictionary: EmojiDictionary
    let markedText: MutableProperty<String>
    let text: Signal<String, NoError>.Observer

    func clear() {
        markedText.swap("")
        candidates.swap([])
    }

    func forward(userInput: UserInput) {
        _ = userInput.originalEvent.map {
            candidateEvent.send(value: $0)
        }
    }
}

internal protocol MappingDefinition {
    func mapping(context: MappingContext) -> [ActionMapping<InputMethodState, UserInput>]
}
