//
//  Temperature.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import Foundation

struct Temperature: Decodable, Encodable, Identifiable {
    let temperature: Double
    let time: UInt16
    
    var id: Double {
        return temperature
    }
    
    var formattedTime: String {
        let minutes = self.time / 60
        let seconds = self.time - (minutes * 60)
        if seconds < 9 {
            return "\(minutes):0\(seconds)"
        }
        return "\(minutes):\(seconds)"
    }
    
    var formattedTemperature: String {
        return "\(temperature) °C"
    }
}
