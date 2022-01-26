//
//  Favorite.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Selection: Decodable, Encodable {
    let film: Film
    let developer: Developer
    let dilution: Dilution
    let speed: Speed
    let format: Format
    let temperature: Temperature
    
    var description: String {
        let elements = [
            film.name,
            speed.value,
            developer.name,
            format.format
        ]
        return elements.joined(separator: "/")
    }
    
    var details: String {
        let elements = [
            dilution.ratio,
            temperature.formattedTemperature,
            temperature.formattedTime
        ]
        return elements.joined(separator: "/")
    }
}
