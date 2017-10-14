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

public class EmojiAutomaton {
    private let automaton: Automaton<InputMethodState, UserInput>
    private let observer: Signal<UserInput, NoError>.Observer
    let text: Signal<String, NoError>
    let markedText: Property<String>
    let candidates: Property<[String]>
    let candidateEvent: Signal<NSEvent, NoError>

    private var handled: Bool = false

    init() {
        let (text, textObserver) = Signal<String, NoError>.pipe()
        self.text = text
        let (candidateEvent, candidateEventObserver) = Signal<NSEvent, NoError>.pipe()
        self.candidateEvent = candidateEvent
        let markedTextProperty = MutableProperty<String>("")
        self.markedText = Property(markedTextProperty)

        let candidatesProperty = MutableProperty<[String]>([])
        self.candidates = Property(candidatesProperty)

         let dictionary: EmojiDictionary = EmojiDictionary()

        let mappings: [ActionMapping<InputMethodState, UserInput>] = [
            /*  Input <|> fromState => toState <|> action */
            /* -------------------------------------------*/
            UserInput.typeof(.colon) <|> .normal => .composing <|> { _ in
                markedTextProperty.swap(":")
                candidatesProperty.swap([])
            },
            UserInput.isInput <|> .composing => .composing <|> {
                $0.ifInput { text in
                    markedTextProperty.modify { $0.append(text) }
                    candidatesProperty.swap(dictionary.find(prefix: text))
                }
            },
            UserInput.typeof(.backspace) <|> {
                    $0 == .composing && (markedTextProperty.value.utf8.count <= 1)
                } => .normal <|> { _ in
                    markedTextProperty.swap("")
                    candidatesProperty.swap([])
                },
            UserInput.typeof(.backspace) <|> .composing  => .composing <|>
                markedTextProperty.modify { $0.removeLast() },
            UserInput.typeof(.enter) <|> .composing => .normal <|> { _ in
                textObserver.send(value: markedTextProperty.value)
                markedTextProperty.swap("")
                candidatesProperty.swap([])
            },
            UserInput.typeof(.other) <|> .composing => .selection  <|> {
                _ = $0.originalEvent.map {
                    candidateEventObserver.send(value: $0)
                }
            },
            UserInput.isSelected <|> .selection => .normal <|> {
                $0.ifSelected {
                    textObserver.send(value: $0)
                    markedTextProperty.swap("")
                    candidatesProperty.swap([])
                }
            }, { _ in true } <|> .selection => .selection <|> {
                _ = $0.originalEvent.map {
                    candidateEventObserver.send(value: $0)
                }
            }
        ]
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
