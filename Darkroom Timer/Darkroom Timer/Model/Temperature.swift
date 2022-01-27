//
//  Temperature.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import Foundation

struct Temperature: Decodable, Encodable, Identifiable {
    let temperature: Double
    let times: [UInt16]
    
    var id: Double {
        return temperature
    }
    
    var formattedTime: String {
        let timeStr: [String] = times.map { time in
            let minutes = time / 60
            let seconds = time - (minutes * 60)
            if seconds < 9 {
                return "\(minutes):0\(seconds)"
            }
            return "\(minutes):\(seconds)"
        }
        return timeStr.joined(separator: "+")
    }
    
    var formattedTemperature: String {
        return "\(temperature) °C"
    }
}
