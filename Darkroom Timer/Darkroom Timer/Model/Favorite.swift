//
//  Favorite.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

struct Favorite: Decodable, Encodable {
    let film: Film
    let developer: Developer
    let dilution: Dilution
    let speed: Speed
    let format: Format
}
