//
//  Automaton.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/19.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveAutomaton
import ReactiveSwift
import Result

internal class EmojiAutomaton {
    let candidateEvent: Signal<NSEvent, NoError>
    let candidates: Property<[String]>
    let markedText: Property<String>
    let text: Signal<String, NoError>

    private let automaton: Automaton<InputMethodState, UserInput>
    private let observer: Signal<UserInput, NoError>.Observer
    private var handled: Bool = false
    private let mappingDefinition: [MappingDefinition] = [
        ComposingMapping(),
        NormalMapping(),
        SelectionMapping()
    ]

    init() {
        let (candidateEvent, candidateEventObserver) = Signal<NSEvent, NoError>.pipe()
        self.candidateEvent = candidateEvent

        let candidatesProperty = MutableProperty<[String]>([])
        self.candidates = Property(candidatesProperty)

        let markedTextProperty = MutableProperty<String>("")
        self.markedText = Property(markedTextProperty)

        let (text, textObserver) = Signal<String, NoError>.pipe()
        self.text = text

        let dictionary: EmojiDictionary = EmojiDictionary()

        let context = MappingContext(candidateEvent: candidateEventObserver,
                                     candidates: candidatesProperty,
                                     dictionary: dictionary,
                                     markedText: markedTextProperty,
                                     text: textObserver)
        let mappings = mappingDefinition.flatMap { $0.mapping(context: context) }

        let (inputSignal, observer) = Signal<UserInput, NoError>.pipe()
        self.automaton = Automaton(state: .normal, input: inputSignal, mapping: reduce(mappings))
        self.observer = observer
        observeAction(automaton: automaton, mappings: mappings)
        automaton.replies.observeValues { [weak self] in
            switch $0 {
            case .success:
                self?.handled = true
            default:
                ()
            }
        }
    }

    func handle(_ input: UserInput) -> Bool {
        handled = false
        observer.send(value: input)
        return handled
    }

    var state: Property<InputMethodState> {
        return self.automaton.state
    }
}
