//
//  ReactiveAutomaton+Action.swit
//  EmojiIM
//
//  Created by mzp on 2017/09/20.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveAutomaton

/*precedencegroup ActionPrecedence {
    associativity: left
    lowerThan: AdditionPrecedence
}*/

infix operator <|>: AdditionPrecedence // same as |

public typealias ActionMapping<State, Input> = (
    ((Input) -> Bool),
    Transition<State>,
    ((State, State, Input) -> Void)
)

public func <|> <State, Input>(
    input: @escaping (Input) -> Bool,
    transition: Transition<State>
) -> ActionMapping<State, Input> {
    return (input, transition, { (_, _, _) in })
}

public func <|> <State, Input: Equatable>(
    input: Input,
    transition: Transition<State>
) -> ActionMapping<State, Input> {
    return { $0 == input } <|> transition
}

public func <|> <State, Input> (
    mapping: ActionMapping<State, Input>,
    action: @escaping (State, State, Input) -> Void
) -> ActionMapping<State, Input> {
    return (mapping.0, mapping.1, { (fromState, toState, input) in
        action(fromState, toState, input)
        mapping.2(fromState, toState, input)
    })
}

public func <|> <State, Input> (
    mapping: ActionMapping<State, Input>,
    action: @escaping (Input) -> Void
) -> ActionMapping<State, Input> {
    return mapping <|> { (_, _, input) in action(input) }
}

public func reduce<State, Input, Mappings: Sequence>(_ mappings: Mappings) -> Automaton<State, Input>.Mapping
    where Mappings.Iterator.Element == ActionMapping<State, Input> {
    return { fromState, input in
        for mapping in mappings {
            if mapping.0(input) && mapping.1.fromState(fromState) {
                return mapping.1.toState
            }
        }
        return nil
    }
}

public func observe<State: Equatable, Input, Mappings: Sequence>(automaton: Automaton<State, Input>, mappings: Mappings)
    where Mappings.Iterator.Element == ActionMapping<State, Input> {
        automaton.replies.observeValues { reply in
            guard let toState = reply.toState else {
                return
            }

            for mapping in mappings {
                if mapping.0(reply.input) &&
                    mapping.1.fromState(reply.fromState) &&
                    mapping.1.toState == toState {
                    mapping.2(reply.fromState, reply.fromState, reply.input)
                }
            }
        }
}
