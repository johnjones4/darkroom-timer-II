//
//  Dilution.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Dilution: Decodable, Encodable, Identifiable {
    var id: String {
        return self.ratio
    }
    
    let ratio: String
    let speeds: [Speed]
    
    init(ratio: String, speeds: [Speed]) {
        self.ratio = ratio
        self.speeds = speeds
    }
}
