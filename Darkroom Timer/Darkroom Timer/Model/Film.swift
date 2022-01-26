//
//  Film.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Film: Decodable, Encodable, Identifiable {
    var id: String {
        return self.name
    }
    
    let name: String
    let developers: [Developer]
}
