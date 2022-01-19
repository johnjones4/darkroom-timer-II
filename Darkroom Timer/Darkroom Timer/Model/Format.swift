//
//  Format.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Format: Decodable, Encodable, Identifiable {
    var id: String {
        return self.format
    }
    
    let format: String
    let devTime: Int
    
    init(format: String, devTime: Int) {
        self.format = format
        self.devTime = devTime
    }
}
