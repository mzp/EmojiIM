//
//  EmojiInputController.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/14.
//  Copyright © 2017 mzp. All rights reserved.
//

import Ikemen
import InputMethodKit

@objc(EmojiInputController)
internal class EmojiInputController: IMKInputController {
    private let automaton: EmojiAutomaton = EmojiAutomaton()
    private let candidates: IMKCandidates
    private var directMode: Bool = false
    private let printable: CharacterSet = [
        CharacterSet.alphanumerics,
        CharacterSet.symbols,
        CharacterSet.punctuationCharacters
    ].reduce(CharacterSet()) { $0.union($1) }

    override init!(server: IMKServer, delegate: Any, client inputClient: Any) {
        self.candidates = IMKCandidates(server: server, panelType: kIMKSingleColumnScrollingCandidatePanel)
        super.init(server: server, delegate: delegate, client: inputClient)

        guard let client = inputClient as? IMKTextInput else {
            return
        }
        automaton.markedText.signal.observeValues {
            let notFound = NSRange(location: NSNotFound, length: NSNotFound)
            client.setMarkedText($0, selectionRange: notFound, replacementRange: notFound)
        }
        automaton.text.observeValues {
            let notFound = NSRange(location: NSNotFound, length: NSNotFound)
            client.insertText($0, replacementRange: notFound)
        }
        automaton.candidates.signal.observeValues {
            if $0.isEmpty {
                self.candidates.hide()
            } else {
                self.candidates.update()
                self.candidates.show()
            }
        }
        automaton.candidateEvent.observeValues {
            self.candidates.interpretKeyEvents([$0])
        }
    }

    override func handle(_ event: NSEvent, client sender: Any) -> Bool {
        NSLog("%@", "\(#function)((\(event), client: \(sender))")
        if directMode {
            return false
        }

        return automaton.handle(UserInput(eventType: convert(event: event), originalEvent: event))
    }

    override func menu() -> NSMenu! {
        return NSMenu(title: "EmojiIM") ※ { menu in
            menu.addItem(NSMenuItem(title: kBuiltDate, action: nil, keyEquivalent: ""))
            menu.addItem(NSMenuItem(title: kRevision, action: nil, keyEquivalent: ""))
        }
    }

    private func convert(event: NSEvent) -> UserInput.EventType {
        if event.keyCode == 36 {
            return .enter
        } else if event.keyCode == 51 {
            return .backspace
        } else if let text = event.characters {
            switch text {
            case ":":
                return .colon
            default:
                if text.unicodeScalars.every(where: printable.contains) {
                    return .input(text: text)
                } else {
                    return .navigation
                }
            }
        } else {
            return .navigation
        }
    }
}

extension EmojiInputController /* IMKStateSetting*/ {
    override func activateServer(_ sender: Any) {
        NSLog("%@", "\(#function)((\(sender))")

        guard let client = sender as? IMKTextInput else {
            return
        }
        client.overrideKeyboard(withKeyboardNamed: SettingStore().keyboardLayout())
    }

    override func deactivateServer(_ sender: Any) {
        NSLog("%@", "\(#function)((\(sender))")
        self.candidates.hide()
    }

    override func setValue(_ value: Any, forTag tag: Int, client sender: Any) {
        NSLog("%@", "\(#function)(\(value), forTag: \(tag))")
        guard let value = value as? NSString else {
            return
        }
        guard let sender = sender as? IMKTextInput else {
            return
        }
        directMode = value == "com.apple.inputmethod.Roman"
        sender.overrideKeyboard(withKeyboardNamed: SettingStore().keyboardLayout())
    }
}

extension EmojiInputController {
    override func candidates(_ sender: Any) -> [Any] {
        return automaton.candidates.value
    }

    override func candidateSelected(_ candidateString: NSAttributedString) {
        NSLog("%@", "\(#function)")
        DispatchQueue.main.async {
            _ = self.automaton.handle(UserInput(eventType: .selected(candidate: candidateString.string)))
        }
    }

    override func candidateSelectionChanged(_ candidateString: NSAttributedString) {
        NSLog("%@", "\(#function)")
    }
}
