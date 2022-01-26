//
//  RichTime.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import Foundation

struct RichTime: Decodable, Encodable, Identifiable {
    var id: UInt16 {
        return self.time
    }
    var formattedTime: String {
        let minutes = self.time / 60
        let seconds = self.time - (minutes * 60)
        if seconds < 9 {
            return "\(minutes):0\(seconds)"
        }
        return "\(minutes):\(seconds)"
    }
    let time: UInt16
}
