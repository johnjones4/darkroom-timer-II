//
//  SpeedTableVIew.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import SwiftUI

struct SpeedTableVIew: View {
    var film: Film
    var developer: Developer
    var dilution: Dilution
    
    var body: some View {
        List(dilution.speeds) { speed in
            NavigationLink(destination: FormatTableView(film: film, developer: developer, dilution: dilution, speed: speed)) {
                VStack(alignment: .leading) {
                    Text(speed.value)
                }
            }
        }.navigationBarTitle(Text("\(film.name) / \(developer.name) / \(dilution.ratio)"))
    }
}

struct SpeedTableVIew_Previews: PreviewProvider {
    static var previews: some View {
        SpeedTableVIew(
            film: Film(name: "Tri-x", developers: []),
            developer: Developer(name: "Tmax", dilutions: []),
            dilution: Dilution(
                ratio: "1+4",
                speeds: [
                    Speed(value: "400", formats: [])
                ]
            )
        )
    }
}
