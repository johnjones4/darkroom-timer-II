//
//  ContentView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import SwiftUI

struct MainView: View {
    var body: some View {
        TabView{
            NavigationView {
                FilmTableView()
            }.tabItem {
                Text("All Films")
                Image(systemName: "film")
            }
            NavigationView {
                RecentsTableView()
            }.tabItem {
                Text("Recents")
                Image(systemName: "clock")
            }
            NavigationView {
                DeviceLog()
            }.tabItem {
                Text("Device Log")
                Image(systemName: "iphone.radiowaves.left.and.right")
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        MainView()
    }
}
