//
//  Collection+Every.swift
//  EmojiIM
//
//  Created by mzp on 2017/10/15.
//  Copyright © 2017 mzp. All rights reserved.
//

extension Collection {
    func every(where predicate: @escaping (Element) -> Bool) -> Bool {
        return !contains { !predicate($0) }
    }
}
