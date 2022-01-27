//
//  RecentSelection.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import Foundation

protocol Recent {
    var timestamp: Date { get }
    var description: String { get }
    var details: String { get }
}

struct RecentSelection: Recent, Decodable, Encodable {
    let timestamp: Date
    let selection: Selection
    
    init(selection: Selection) {
        self.timestamp = Date()
        self.selection = selection
    }
    
    var description: String {
        return selection.description
    }
    
    var details: String {
        return selection.details
    }
}

struct RecentTimer: Recent, Decodable, Encodable {
    let timestamp: Date
    let timerSet: CustomTimerSet
    
    init(timerSet: CustomTimerSet) {
        self.timestamp = Date()
        self.timerSet = timerSet
    }
    
    var description: String {
        return "Custom"
    }
    
    var details: String {
        return timerSet.times.map { timer in
            return timer.description
        }.joined(separator: ", ")
    }
}
