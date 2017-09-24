//
//  EmojiInputController.swift
//  EmojiIM
//
//  Created by mzp on 2017/09/14.
//  Copyright © 2017 mzp. All rights reserved.
//

import Ikemen
import Foundation
import InputMethodKit

@objc(EmojiInputController)
open class EmojiInputController : IMKCandidateBasedInputController {
    public override init!(server: IMKServer!, delegate: Any!, client inputClient: Any!) {
        NSLog("%@", "\(#function)")

        super.init(server: server, delegate: delegate, client: inputClient)

        let info = IMKUIInformation.shared()
        info?.touchBarController = self.secondaryCandidateController
        info?.visibleOnscreenController = self.candidateController
    }

/*    open override var automaticallyShowPrimaryCandidatesInSecondaryController : Bool {
        NSLog("%@", "\(#function)")
        return true
    }*/

    open override func activateServer(_ sender: Any!) {
        NSLog("%@", "\(#function) \(sender)")
        let info = IMKUIInformation.shared()
        NSLog("%@", "\(self.candidateController)")
        NSLog("%@", "endpoint \(server()?.functionRowItemViewServiceXPCEndpoint())")
        info?.touchBarController = self.secondaryCandidateController
        info?.visibleOnscreenController = self.candidateController
        IMKServer.presentFunctionRowItemTextInputView()
    }

    open override func touchBarControllerClass() -> AnyClass! {
        let c = super.touchBarControllerClass()
        NSLog("%@", "\(#function) \(c)")
        return c
    }

    open override var secondaryCandidateController: IMKUICandidateTouchBarController! {
        let controller = super.secondaryCandidateController
        NSLog("%@", "\(#function) => \(controller)")
        return controller
    }

    open override func selectionShouldBeReflectedInTouchBar() -> Bool {
        NSLog("%@", "\(#function)")
        return true
    }

     open override func defaultDisplayMethod() -> Any! {
        NSLog("%@", "\(#function)")
        return super.defaultDisplayMethod()
    }

    open override func displayMethod() -> Any! {
        NSLog("%@", "\(#function) => \(super.displayMethod())")
        return "Frequency"
    }
/*    open override var secondaryCandidates: [Any]! {
        get {
            NSLog("%@", "\(#function)")
            return ["abc']
        }
        set {
            NSLog("%@", "\(#function)")
        }
    }*/

    open override func informationView() -> Any! {
        NSLog("%@", "\(#function) \(super.informationView())")
        return super.informationView()
    }

    open override func handle(_ event: NSEvent!, client sender: Any!) -> Bool {
        NSLog("--------------------------------------------")
        let info = IMKUIInformation.shared()


        secondaryCandidateController?.secondaryCandidatesShowChevron = true

        info?.touchBarController?.numberOfSimilarWidthCandidates = 4
        NSLog("[reload candidate]")
        reloadCandidates()
        presentSecondaryCandidates()
        if let v =  info?.touchBarController?.viewController?.view  {
            makePNGFromView(view: v)
        }
        NSLog("%@", "\(info?.touchBarController?.currentlyShownCandidates?.candidates)")

        guard let c = sender as? IPMDServerClientWrapper else {
            return true
        }
        c.dismissFunctionRowItemTextInputView()
        c.presentFunctionRowItemTextInputView()


/*        NSLog("[reloadSecondaryCandidatesOnly]")
        reloadSecondaryCandidatesOnly()
        NSLog("%@", "\(info?.touchBarController?.currentlyShownCandidates?.candidates)")
        NSLog("[presentSecondaryCandidates]")
        self.presentSecondaryCandidates()
        NSLog("%@", "\(info?.touchBarController?.currentlyShownCandidates?.candidates)")

        NSLog("[reload withUpdatingFirstCandidate:]")
        info?.touchBarController?.reload(withUpdatingFirstCandidate: true)
        NSLog("%@", "\(info?.touchBarController?.currentlyShownCandidates?.candidates)")
*/
        return true
    }

    open override func candidates(_ sender: Any!) -> [Any]! {
        NSLog("%@", "\(#function)")
        return []
    }

    open override func candidateData(forSortingMethod arg1: String!) -> IMKCandidateData! {
        NSLog("%@", "\(#function)")
        return IMKCandidateData(array: [])
    }

    open override func secondaryCandidateControllerAuxiliaryViews() -> Any! {
        let r = super.secondaryCandidateControllerAuxiliaryViews()
        NSLog("%@", "\(#function) \(r)")
        return r
    }

    open override func functionRowItemTextInputViewController() -> NSViewController! {
        let r = super.functionRowItemTextInputViewController()
        let info = IMKUIInformation.shared()
        NSLog("%@", "\(#function) => \(r) // \(info?.touchBarController?.viewController)")

        return r
    }

    open override func candidateData(forDisplayMethod arg1: Any!, candidateController arg2: Any!) -> Any! {
        NSLog("%@", "\(#function) \(arg1) \(arg2)")
        let candidate1 = IMKCandidateDefinitionUnit()
        candidate1.text = "🍣"
        candidate1.annotation = "すし"

        let candidate2 = IMKCandidateDefinitionUnit()
        candidate2.text = "sushi"
        candidate2.annotation = "すし"

        self.secondaryCandidates = [candidate2]

        return IMKCandidateData(array: [
            candidate1,
            candidate2
//            IMKCandidate(text: "🍣"),
//            IMKCandidate(text: "🍣"),
//            IMKCandidate(text: "🍣")
        ])
    }

    func makePNGFromView(view: NSView) {
        var rep = view.bitmapImageRepForCachingDisplay(in: view.bounds)!
        view.cacheDisplay(in: view.bounds, to: rep)
        if let data = rep.representation(using: .png, properties: [:]) {
            try? data.write(to: URL(fileURLWithPath: "/tmp/foo.png"))
        }
    }
}
