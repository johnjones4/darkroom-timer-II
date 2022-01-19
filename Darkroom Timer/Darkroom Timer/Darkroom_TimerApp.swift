//
//  Darkroom_TimerApp.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

@main
struct Darkroom_TimerApp: App {
    var store = Store.load()
    
    var body: some Scene {
        WindowGroup {
            ContentView(store: store)
        }
    }
}
