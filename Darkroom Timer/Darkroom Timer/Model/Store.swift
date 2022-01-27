//
//  Store.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

class Store: ObservableObject {
    var films = [Film]()
    @Published var recentSelections = [RecentSelection]()
    @Published var recentTimers = [RecentTimer]()
    
    static let main = Store()
    
    func load() {
        do {
            try self.loadFilms()
            try self.loadRecentSelections()
            try self.loadRecentTimers()
        } catch {
            print(error)
        }
    }
    
    private var recentSelectionsURL: URL {
        let documentDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        return documentDirectory.appendingPathComponent("recentSelections.json")
    }
    
    private var recentTimersURL: URL {
        let documentDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        return documentDirectory.appendingPathComponent("recentTimers.json")
    }
    
    func loadFilms() throws {
        guard let url = Bundle.main.url(forResource: "data", withExtension: "json") else { return }
        let data = try Data(contentsOf: url)
        let decoder = JSONDecoder()
        self.films = try decoder.decode([Film].self, from: data)
    }
    
    func loadRecentSelections() throws {
        guard let data = try? Data(contentsOf: self.recentSelectionsURL) else { return }
        let decoder = JSONDecoder()
        self.recentSelections = try decoder.decode([RecentSelection].self, from: data)
    }
    
    func saveRecentSelections() throws {
        let encoder = JSONEncoder()
        guard let data = try? encoder.encode(self.recentSelections) else { return }
        try data.write(to: self.recentSelectionsURL)
    }
    
    func loadRecentTimers() throws {
        guard let data = try? Data(contentsOf: self.recentTimersURL) else { return }
        let decoder = JSONDecoder()
        self.recentTimers = try decoder.decode([RecentTimer].self, from: data)
    }

    func saveRecentTimers() throws {
        let encoder = JSONEncoder()
        guard let data = try? encoder.encode(self.recentTimers) else { return }
        try data.write(to: self.recentTimersURL)
    }
    
    func addRecentSelection(selection: Selection) throws {
        recentSelections.append(RecentSelection(selection: selection))
        if recentSelections.count > 20 {
            recentSelections = recentSelections.dropFirst().map({ r in
                return r
            })
        }
        try self.saveRecentSelections()
    }
    
    func addRecentTimer(timerSet: CustomTimerSet) throws {
        recentTimers.append(RecentTimer(timerSet: timerSet))
        if recentTimers.count > 20 {
            recentTimers = recentTimers.dropFirst().map({ r in
                return r
            })
        }
        try self.saveRecentTimers()
    }
}
