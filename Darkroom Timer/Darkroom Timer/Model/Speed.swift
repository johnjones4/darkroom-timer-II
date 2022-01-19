//
//  Speed.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Speed: Decodable, Encodable, Identifiable {
    var id: String {
        return self.value
    }
    
    let value: String
    let formats: [Format]
    
    init(value: String, formats: [Format]) {
        self.value = value
        self.formats = formats
    }
}
