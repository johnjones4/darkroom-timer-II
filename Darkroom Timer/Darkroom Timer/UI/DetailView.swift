//
//  DetailView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import SwiftUI

struct SelectionDetailElement: Identifiable {
    var id: String {
        return key
    }
    let key: String
    let value: String
}

let DefaultTimes : [UInt16] = [60, 60 * 5]

struct DetailView: View {
    var selection: Selection
    var rows: [SelectionDetailElement] {
        return [
            SelectionDetailElement(key: "Film Stock", value: selection.film.name),
            SelectionDetailElement(key: "Developer", value: selection.developer.name),
            SelectionDetailElement(key: "Dilution", value: selection.dilution.ratio),
            SelectionDetailElement(key: "Speed", value: selection.speed.value),
            SelectionDetailElement(key: "Format", value: selection.format
                                    .format),
            SelectionDetailElement(key: "Temperature", value: selection.temperature.formattedTemperature),
            SelectionDetailElement(key: "Time", value: selection.temperature.formattedTime)
        ]
    }
    
    var body: some View {
        List {
            Section(header: Text("Info")) {
                ForEach(rows) { row in
                    HStack(alignment: .bottom) {
                        Text(row.key).font(.subheadline)
                        Text(row.value)
                            .font(.body)
                            .frame(maxWidth: .infinity, alignment: .trailing)
                    }
                }
            }
            Section() {
                Button {
                    do {
                        TimerController.main.send(times: selection.temperature.times + DefaultTimes)
                        try Store.main.addRecentSelection(selection: selection)
                    } catch {
                        print(error)
                    }
                } label: {
                    Text("Send")
                }.frame(maxWidth: .infinity)
            }
        }
            .navigationBarTitle(Text("Film Detail"))
            .listStyle(GroupedListStyle())
    }
}

struct DetailView_Previews: PreviewProvider {
    static var previews: some View {
        DetailView(selection: Selection(
            film: Film(name: "Tri-x", developers: []),
            developer: Developer(name: "Tmax", dilutions: []),
            dilution: Dilution(ratio: "1+4", speeds: []
            ),
            speed: Speed(value: "400", formats: []),
            format: Format(format: "125", temperatures: []),
            temperature: Temperature(temperature: 20, times: [600, 300])
        ))
    }
}
