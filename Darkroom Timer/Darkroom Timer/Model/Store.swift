//
//  Store.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

class Store: ObservableObject {
    var films = [Film]()
    @Published var recents = [RecentSelection]()
    
    static let main = Store()
    
    func load() {
        do {
            try self.loadFilms()
            try self.loadRecents()
        } catch {
            print(error)
        }
    }
    
    private var recentsURL: URL {
        let documentDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        return documentDirectory.appendingPathComponent("favorites.json")
    }
    
    func loadFilms() throws {
        guard let url = Bundle.main.url(forResource: "data", withExtension: "json") else { return }
        let data = try Data(contentsOf: url)
        let decoder = JSONDecoder()
        self.films = try decoder.decode([Film].self, from: data)
    }
    
    func loadRecents() throws {
        guard let data = try? Data(contentsOf: self.recentsURL) else { return }
        let decoder = JSONDecoder()
        self.recents = try decoder.decode([RecentSelection].self, from: data)
    }
    
    func saveRecents() throws {
        let encoder = JSONEncoder()
        guard let data = try? encoder.encode(self.recents) else { return }
        try data.write(to: self.recentsURL)
    }
    
    func addRecent(selection: Selection) throws {
        recents.append(RecentSelection(timestamp: Date(), selection: selection))
        if recents.count > 20 {
            recents = recents.dropFirst().map({ r in
                return r
            })
        }
        try self.saveRecents()
    }
}
