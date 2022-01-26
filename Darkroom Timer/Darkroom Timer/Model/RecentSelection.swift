//
//  RecentSelection.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import Foundation

struct RecentSelection: Decodable, Encodable, Identifiable {
    let timestamp: Date
    let selection: Selection
    
    var id: Date {
        return timestamp
    }
}
