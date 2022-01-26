//
//  Developer.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Developer: Decodable, Encodable, Identifiable {
    var id: String {
        return self.name
    }
    
    let name: String
    let dilutions: [Dilution]
}
