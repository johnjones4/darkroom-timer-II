//
//  CustomTimer.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/26/22.
//

import Foundation

struct CustomTimer: Encodable, Decodable, Identifiable {
    let time: UInt16
    let id: UUID
    
    var description: String {
        let minutes = time / 60
        let seconds = time - (minutes * 60)
        if seconds < 9 {
            return "\(minutes):0\(seconds)"
        }
        return "\(minutes):\(seconds)"
    }
    
    var minutes: UInt16 {
        return time / 60
    }
    
    var seconds: UInt16 {
        return time - (minutes * 60)
    }
    
    init(time: UInt16) {
        self.time = time
        self.id = UUID()
    }
    
    init(id: UUID, time: UInt16) {
        self.time = time
        self.id = id
    }
    
    func update(minutes: UInt16, seconds: UInt16) -> CustomTimer {
        return CustomTimer(
            id: self.id,
            time: (minutes * 60) + seconds
        )
    }
}

struct CustomTimerSet: Encodable, Decodable, Identifiable {
    let times: [CustomTimer]
    let id: UUID
    
    init(times: [UInt16]) {
        self.times = times.map({ t in
            return CustomTimer(time: t)
        })
        self.id = UUID()
    }
    
    init(id: UUID, times: [CustomTimer]) {
        self.times = times
        self.id = id
    }
    
    func addTimer(t: UInt16) -> CustomTimerSet {
        return CustomTimerSet(id: self.id, times: self.times + [CustomTimer(time: t)])
    }
    
    func removeTimer(id: UUID) -> CustomTimerSet {
        return CustomTimerSet(id: self.id, times: self.times.filter({ t in
            return t.id != id
        }))
    }
    
    func updateTimer(t: CustomTimer) -> CustomTimerSet {
        return CustomTimerSet(id: self.id, times: self.times.map({ t1 in
            return t1.id == t.id ? t : t1
        }))
    }
}
