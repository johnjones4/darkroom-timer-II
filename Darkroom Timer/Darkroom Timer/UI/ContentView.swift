//
//  ContentView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

struct ContentView: View {
    var store: Store
    
    var body: some View {
        NavigationView {
            FilmTableView(films: store.films)
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView(store: Store())
    }
}
