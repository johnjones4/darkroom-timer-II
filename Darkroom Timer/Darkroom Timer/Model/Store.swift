//
//  Store.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/18/22.
//

import Foundation

class Store {
    var films = [Film]()
    var favorites = [Favorite]()
    
    static func load() -> Store {
        let s = Store()
        do {
            try s.loadFilms()
            try s.loadFavorites()
        } catch {
            print(error)
        }
        return s
    }
    
    private var favoritesURL: URL {
        let documentDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        return documentDirectory.appendingPathComponent("favorites.json")
    }
    
    func loadFilms() throws {
        guard let url = Bundle.main.url(forResource: "data", withExtension: "json") else { return }
        let data = try Data(contentsOf: url)
        let decoder = JSONDecoder()
        self.films = try decoder.decode([Film].self, from: data)
    }
    
    func loadFavorites() throws {
        guard let data = try? Data(contentsOf: self.favoritesURL) else { return }
        let decoder = JSONDecoder()
        self.favorites = try! decoder.decode([Favorite].self, from: data)
    }
    
    func saveFavorites() {
        let encoder = JSONEncoder()
        guard let data = try? encoder.encode(self.favorites) else { return }
        try? data.write(to: self.favoritesURL)
    }
}
