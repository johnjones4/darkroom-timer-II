//
//  RecentsTableView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import SwiftUI

struct RecentWrapper: Identifiable {
    let recent: Recent
    
    init(recent: Recent) {
        self.recent = recent
    }
    
    var id: Date {
        return recent.timestamp
    }
    
    var destination: some View {
        VStack {
            if recent is RecentTimer {
                CustomTimerView(timerSet: (recent as! RecentTimer).timerSet)
            } else if recent is RecentSelection {
                DetailView(selection: (recent as! RecentSelection).selection)
            }
        }
    }
}

struct RecentsTableView: View {
    @ObservedObject var store = Store.main
    
    var body: some View {
        var recents = [RecentWrapper]()
        recents.append(contentsOf: store.recentTimers.map {r in RecentWrapper(recent: r)})
        recents.append(contentsOf: store.recentSelections.map {r in RecentWrapper(recent: r)})
        recents = recents.sorted(by: { a, b in
            return a.recent.timestamp > b.recent.timestamp
        })
        return List(recents) { recent in
            NavigationLink(destination: recent.destination) {
                VStack(alignment: .leading) {
                    Text(recent.recent.description)
                    Text(recent.recent.details)
                        .font(.subheadline)
                }
            }
        }.navigationBarTitle(Text("Recents"))
    }
}

struct RecentsTableView_Previews: PreviewProvider {
    static var previews: some View {
        RecentsTableView()
    }
}
