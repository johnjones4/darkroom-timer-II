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
}
