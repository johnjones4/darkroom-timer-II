//
//  CustomTImer.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/26/22.
//

import SwiftUI

struct CustomTimerView: View {
    @State var timerSet = CustomTimerSet(times: [UInt16(60 * 2), UInt16(30), UInt16(60 * 5)])
    
    var body: some View {
        List {
            Section(header: Text("Timers")) {
                ForEach(timerSet.times) { timer in
                    NavigationLink(destination: TimerPickerView(timer: Binding<CustomTimer>(
                        get: {
                            return timer
                        }, set: { timer in
                            timerSet = timerSet.updateTimer(t: timer)
                        }
                    ))) {
                        Text(timer.description)
                    }
                }.onDelete { idx in
                    var ts = timerSet
                    idx
                        .map { row in
                            return timerSet.times[row].id
                        }
                        .forEach { id in
                            ts = ts.removeTimer(id: id)
                        }
                    timerSet = ts
                }
                Button {
                    timerSet = timerSet.addTimer(t: 0)
                } label: {
                    Text("+ Timer")
                }.frame(maxWidth: .infinity, alignment: .leading)
            }
            Section {
                Button {
                    do {
                        TimerController.main.send(times: timerSet.times.map({ t in
                            return t.time
                        }))
                        try Store.main.addRecentTimer(timerSet: timerSet)
                    } catch {
                        print(error)
                    }
                } label: {
                    Text("Send")
                }.frame(maxWidth: .infinity)
            }
        }
            .navigationBarTitle(Text("Custom Timer"))
            .listStyle(GroupedListStyle())
    }
}

struct CustomTImer_Previews: PreviewProvider {
    static var previews: some View {
        CustomTimerView()
    }
}
