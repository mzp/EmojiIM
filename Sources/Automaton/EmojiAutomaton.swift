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
    private var handled: Bool = false

    init() {
        let (text, textObserver) = Signal<String, NoError>.pipe()
        self.text = text
        let markedTextProperty = MutableProperty<String>("")
        self.markedText = Property(markedTextProperty)

        let mappings: [ActionMapping<InputMethodState, UserInput>] = [
            /*  Input |   fromState => toState <|> action   */
            /* --------------------------------------*/
            UserInput.isInput <|> .normal => .composing <|> {
                $0.ifInput { markedTextProperty.swap($0) }
            },
            UserInput.isInput <|> .composing => .composing <|> {
                $0.ifInput { text in
                    markedTextProperty.modify { $0.append(text) }
                }
            },
            .backspace <|> {
                    $0 == .composing && (markedTextProperty.value.utf8.count <= 1)
                } => .normal <|> { _ in
                    markedTextProperty.swap("")
                },
            .backspace <|> .composing  => .composing <|>
                markedTextProperty.modify { $0.removeLast() },
            .enter <|> .composing => .normal <|> { _ in
                textObserver.send(value: markedTextProperty.value)
                markedTextProperty.swap("")
            }
        ]
        let (inputSignal, observer) = Signal<UserInput, NoError>.pipe()

        self.automaton = Automaton(state: .normal, input: inputSignal, mapping: reduce(mappings))
        self.observer = observer
        observe(automaton: automaton, mappings: mappings)
        automaton.replies.observeValues {
            switch $0 {
            case .success:
                self.handled = true
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
