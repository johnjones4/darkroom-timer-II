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
                Text("Films")
                Image(systemName: "film")
            }
            NavigationView {
                CustomTimerView()
            }.tabItem {
                Text("Custom")
                Image(systemName: "timer")
            }
            NavigationView {
                RecentsTableView()
            }.tabItem {
                Text("Recent")
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
