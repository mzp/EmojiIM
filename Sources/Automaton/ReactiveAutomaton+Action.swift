//
//  ReactiveAutomaton+Action.swit
//  EmojiIM
//
//  Created by mzp on 2017/09/20.
//  Copyright © 2017 mzp. All rights reserved.
//

import ReactiveAutomaton

public struct ActionMapping<State, Input> {
    let input: (Input) -> Bool
    let transition: Transition<State>
    let action: (State, State, Input) -> Void
}

infix operator <|>: AdditionPrecedence // same as |

public func <|> <State, Input>(
    input: @escaping (Input) -> Bool,
    transition: Transition<State>
) -> ActionMapping<State, Input> {
    return ActionMapping(input: input, transition: transition, action: { (_, _, _) in })
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
    return ActionMapping(input: mapping.input, transition: mapping.transition) { (fromState, toState, input) in
            action(fromState, toState, input)
            mapping.action(fromState, toState, input)
    }
}

public func <|> <State, Input> (
    mapping: ActionMapping<State, Input>,
    action: @escaping (Input) -> Void
) -> ActionMapping<State, Input> {
    return mapping <|> { (_, _, input) in action(input) }
}

public func <|> <State, Input> (
    mapping: ActionMapping<State, Input>,
    action: @autoclosure @escaping () -> Void
    ) -> ActionMapping<State, Input> {
    return mapping <|> { (_, _, input) in action() }
}

public func reduce<State, Input, Mappings: Sequence>(_ mappings: Mappings) -> Automaton<State, Input>.Mapping
    where Mappings.Iterator.Element == ActionMapping<State, Input> {
    return { fromState, input in
        for mapping in mappings {
            if mapping.input(input) && mapping.transition.fromState(fromState) {
                return mapping.transition.toState
            }
        }
        return nil
    }
}

public func observeAction<State: Equatable, Input, Mappings: Sequence>(
    automaton: Automaton<State, Input>, mappings: Mappings
) where Mappings.Iterator.Element == ActionMapping<State, Input> {
        automaton.replies.observeValues { reply in
            guard let toState = reply.toState else {
                return
            }

            for mapping in mappings {
                if mapping.input(reply.input) &&
                    mapping.transition.fromState(reply.fromState) &&
                    mapping.transition.toState == toState {
                    mapping.action(reply.fromState, reply.fromState, reply.input)
                }
            }
        }
}
