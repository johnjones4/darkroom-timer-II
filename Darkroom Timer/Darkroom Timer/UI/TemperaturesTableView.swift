//
//  TimesTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import SwiftUI

struct TemperaturesTableView: View {
    var film: Film
    var developer: Developer
    var dilution: Dilution
    var speed: Speed
    var format: Format
    
    var body: some View {
        List(format.temperatures) { temperature in
            NavigationLink(destination: DetailView(selection: Selection(film: film, developer: developer, dilution: dilution, speed: speed, format: format, temperature: temperature))) {
                VStack(alignment: .leading) {
                    Text(temperature.formattedTemperature)
                }
            }
        }.navigationBarTitle(Text("\(film.name) / \(developer.name) / \(dilution.ratio) / \(speed.value) \(format.format)"))
    }
}

struct TimesTableView_Previews: PreviewProvider {
    static var previews: some View {
        TemperaturesTableView(
            film: Film(name: "Tri-x", developers: []),
            developer: Developer(name: "Tmax", dilutions: []),
            dilution: Dilution(ratio: "1+4", speeds: []
            ),
            speed: Speed(value: "400", formats: []),
            format: Format(format: "125", temperatures: [
                Temperature(temperature: 30, time: 10),
                Temperature(temperature: 40, time: 20),
            ])
        )
    }
}
