//
//  DevelopersTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

struct DevelopersTableView: View {
    var film: Film
    
    var body: some View {
        List(film.developers) { developer in
            NavigationLink(destination: DilutionTableView(film: film, developer: developer)) {
                VStack(alignment: .leading) {
                    Text(developer.name)
                }
            }
        }.navigationBarTitle(Text(film.name))
    }
}

struct DevelopersTableView_Previews: PreviewProvider {
    static var previews: some View {
        DevelopersTableView(film:
            Film(name: "tmax", developers: [
                Developer(name: "Tmax Dev", dilutions: [])
            ])
        )
    }
}
