//
//  DilutionTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

struct DilutionTableView: View {
    var film: Film
    var developer: Developer
    
    var body: some View {
        List(developer.dilutions) { dilution in
            NavigationLink(destination: SpeedTableVIew(film: film, developer: developer, dilution: dilution)) {
                VStack(alignment: .leading) {
                    Text(dilution.ratio)
                }
            }
        }.navigationBarTitle(Text("\(film.name) / \(developer.name)"))
    }
}

struct DilutionTableView_Previews: PreviewProvider {
    static var previews: some View {
        DilutionTableView(
            film: Film(name: "Tri-x", developers: []),
            developer: Developer(
                name: "test",
                dilutions: [
                    Dilution(ratio: "1+4", speeds: [])
                ]
            )
        )
    }
}
