//
//  TISInputSource+Property.swift
//  Preferences
//
//  Created by mzp on 2017/11/13.
//  Copyright © 2017 mzp. All rights reserved.
//

extension TISInputSource {
    var localizedName: String {
        return unsafeBitCast(
            TISGetInputSourceProperty(self, kTISPropertyLocalizedName),
            to: NSString.self) as String
    }

    var inputSourceID: String {
        return unsafeBitCast(
            TISGetInputSourceProperty(self, kTISPropertyInputSourceID),
            to: NSString.self) as String
    }

    var scriptCode: Int? {
        let r = TISGetInputSourceProperty(self, kTISPropertyScriptCode)
        let n = unsafeBitCast(r, to: NSString.self).integerValue
        return n
    }

    class func keyboardLayouts() -> [TISInputSource]? {
        let conditions = CFDictionaryCreateMutable(nil, 2, nil, nil)
        CFDictionaryAddValue(conditions,
                             unsafeBitCast(kTISPropertyInputSourceType, to: UnsafeRawPointer.self),
                             unsafeBitCast(kTISTypeKeyboardLayout, to: UnsafeRawPointer.self))
        CFDictionaryAddValue(conditions,
                             unsafeBitCast(kTISPropertyInputSourceIsASCIICapable, to: UnsafeRawPointer.self),
                             unsafeBitCast(kCFBooleanTrue, to: UnsafeRawPointer.self))

        guard let array = TISCreateInputSourceList(conditions, true) else {
            return nil
        }
        guard let keyboards = array.takeRetainedValue() as? [TISInputSource] else {
            return nil
        }
        return keyboards.sorted {
            $0.localizedName < $1.localizedName
        }
    }
}
