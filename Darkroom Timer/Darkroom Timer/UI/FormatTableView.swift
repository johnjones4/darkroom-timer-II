//
//  FormatTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/19/22.
//

import SwiftUI

struct FormatTableView: View {
    var film: Film
    var developer: Developer
    var dilution: Dilution
    var speed: Speed
    
    var body: some View {
        List(speed.formats) { format in
            NavigationLink(destination: Text(format.format)) {
                VStack(alignment: .leading) {
                    Text(format.format)
                }
            }
        }.navigationBarTitle(Text("\(film.name) / \(developer.name) / \(dilution.ratio) / \(speed.value)"))
    }
}

struct FormatTableView_Previews: PreviewProvider {
    static var previews: some View {
        FormatTableView(
            film: Film(name: "Tri-x", developers: []),
            developer: Developer(name: "Tmax", dilutions: []),
            dilution: Dilution(ratio: "1+4", speeds: []
            ),
            speed: Speed(value: "400", formats: [
                Format(format: "125", devTime: 0)
            ])
        )
    }
}
