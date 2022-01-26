//
//  ControllerLog.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import Foundation
import CoreBluetooth

struct TimerControllerLogEventWrapper: Identifiable {
    let event: TimerControllerLogEvent
    var id: Date {
        return event.timestamp
    }
}

protocol TimerControllerLogEvent {
    var eventName: String { get }
    var description: String { get }
    var timestamp: Date { get }
}

enum TimerControllerConnectionType: String {
    case Discover = "Discovered"
    case Connect = "Connected"
    case Disconnect = "Disconnected"
}

struct TimerControllerConnectionEvent: TimerControllerLogEvent {
    let timestamp = Date()
    let eventType: TimerControllerConnectionType
    let device: CBPeripheral
    
    var eventName: String {
        return "\(eventType.rawValue) Device"
    }
    
    var description: String {
        return device.name ?? device.identifier.uuidString
    }
}

struct TimerControllerErrorEvent: TimerControllerLogEvent {
    let timestamp = Date()
    let error: Error
    
    var eventName: String {
        return "Error"
    }
    
    var description: String {
        return error.localizedDescription
    }
}

struct TimerControllerManagerStateChangeEvent: TimerControllerLogEvent {
    let timestamp = Date()
    let state: CBManagerState
    
    var eventName: String {
        return "Manager Changed State"
    }
    
    var description: String {
        switch state {
        case .unknown:
            return "Unknown"
        case .resetting:
            return "Resetting"
        case .unsupported:
            return "Unsupported"
        case .unauthorized:
            return "Unauthorized"
        case .poweredOff:
            return "Powered Off"
        case .poweredOn:
            return "Powered On"
        @unknown default:
            return "Unsupported Value"
        }
    }
}

struct TimerControllerServiceDiscoveredEvent: TimerControllerLogEvent {
    let timestamp = Date()
    let service: CBService
    
    var eventName: String {
        return "Discovered Service"
    }
    
    var description: String {
        return service.uuid.uuidString
    }
}

struct TimerControllerCharacteristicDiscoveredEvent: TimerControllerLogEvent {
    let timestamp = Date()
    let characteristic: CBCharacteristic
    
    var eventName: String {
        return "Discovered Characteristic"
    }
    
    var description: String {
        return characteristic.uuid.uuidString
    }
}
