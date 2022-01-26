//
//  Darkroom_TimerApp.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

@main
struct Darkroom_TimerApp: App {
    init() {
        Store.main.load()
        TimerController.main.start()
    }
    
    var body: some Scene {
        WindowGroup {
            MainView()
        }
    }
}
