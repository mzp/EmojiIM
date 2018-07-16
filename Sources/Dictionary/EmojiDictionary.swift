//
//  EmojiDictionary.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/13.
//  Copyright © 2017 mzp. All rights reserved.
//
import AppKit

// TODO: introduce some protocol
internal class EmojiDictionary {
    private struct Entry: Codable {
        let name: String
        let emoji: String
    }
    private let entries: [Entry]
    private let limit: Int

    init(limit: Int = 6) {
        self.limit = limit
        guard let url = Bundle.main.url(forResource: "EmojiDefinition", withExtension: "json") else {
            fatalError("cannot find Emojidefinition.json")
        }
        do {
            let data = try Data(contentsOf: url)
            entries = try JSONDecoder().decode([Entry].self, from: data)
        } catch {
            fatalError("load error")
        }
    }

    func find(prefix: String) -> [String] {
        let xs = entries.compactMap { (entry: Entry) -> String? in
            if entry.name.starts(with: prefix) {
                return entry.emoji
            } else {
                return nil
            }
        }.prefix(self.limit)
        return Array(xs)
    }
}
