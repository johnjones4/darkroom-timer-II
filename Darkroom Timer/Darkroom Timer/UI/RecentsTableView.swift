//
//  RecentsTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import SwiftUI

struct RecentsTableView: View {
    @ObservedObject var store = Store.main
    
    var body: some View {
        List(store.recents.reversed()) { recent in
            NavigationLink(destination: DetailView(selection: recent.selection)) {
                VStack(alignment: .leading) {
                    Text(recent.selection.description)
                    Text(recent.selection.details)
                        .font(.subheadline)
                }
            }
        }
            .navigationBarTitle(Text("Recents"))
    }
}

struct RecentsTableView_Previews: PreviewProvider {
    static var previews: some View {
        RecentsTableView()
    }
}
