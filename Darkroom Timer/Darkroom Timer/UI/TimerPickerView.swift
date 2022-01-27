//
//  TimerPickerView.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/26/22.
//

import SwiftUI

struct TimerPickerView: View {
    @Binding var timer: CustomTimer
    @State var minutes: Int = 0
    @State var seconds: Int = 0
    
    var body: some View {
        GeometryReader { geometry in
            HStack {
                Picker("", selection: $minutes) {
                    ForEach(0 ..< 60) { m in
                        Text("\(m)")
                    }
                }
                .onChange(of: minutes, perform: { _ in
                    timer = timer.update(minutes: UInt16(minutes), seconds: UInt16(seconds))
                })
                .frame(width: geometry.size.width/2, height: geometry.size.height).clipped()
                Picker("", selection: $seconds) {
                    ForEach(0 ..< 59) { s in
                        Text("\(s)")
                    }
                }
                .onChange(of: seconds, perform: { seconds in
                    timer = timer.update(minutes: UInt16(minutes), seconds: UInt16(seconds))
                })
                .frame(width: geometry.size.width/2, height: geometry.size.height).clipped()
            }
        }
            .frame(alignment: .center)
            .pickerStyle(WheelPickerStyle())
            .navigationBarTitle(Text("Set Time"))
            .onAppear {
                DispatchQueue.main.async {
                    minutes = Int(timer.minutes)
                    seconds = Int(timer.seconds)
                }
            }
    }
}
