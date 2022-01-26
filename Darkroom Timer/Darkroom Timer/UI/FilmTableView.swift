//
//  FilmTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

struct FilmTableView: View {
    var body: some View {
        List(Store.main.films) { film in
            NavigationLink(destination: DevelopersTableView(film: film)) {
                VStack(alignment: .leading) {
                    Text(film.name)
                }
            }
        }.navigationBarTitle(Text("Films"))
    }
}

struct FilmTableView_Previews: PreviewProvider {
    static var previews: some View {
        FilmTableView()
    }
}
