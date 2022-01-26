//
//  DeviceLog.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import SwiftUI

struct DeviceLog: View {
    @ObservedObject var controller = TimerController.main
    
    var body: some View {
        List(controller.log.reversed()) { logItem in
            VStack(alignment: .leading) {
                Text(logItem.event.eventName)
                Text(logItem.event.description)
                    .font(.subheadline)
            }
        }
            .navigationBarTitle(Text("Device Log"))
            .onAppear {
                controller.start()
            }
    }
}

struct DeviceLog_Previews: PreviewProvider {
    static var previews: some View {
        DeviceLog()
    }
}
