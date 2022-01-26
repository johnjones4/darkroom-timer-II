//
//  TimerController.swift
//  Darkroom Timer
//
//  Created by John Jones on 1/25/22.
//

import Foundation
import CoreBluetooth

let MessageStart : UInt8 = 0x02
let MessageEnd : UInt8 = 0x03
let MessageResponse : UInt8 = 0x06

let PeripheralName = "Darkroom Timer"
let ServiceUUID = CBUUID(string: "9759fea6-c846-4719-9d5c-c959efd61aeb")
let CharacteristicUUID = CBUUID(string: "0be3132d-5d94-414c-b542-2f0da985ea82")

class TimerController: NSObject, ObservableObject {
    static let main = TimerController()
    
    var manager: CBCentralManager!
    var clockDevice: CBPeripheral?
    @Published var clockCharacteristic: CBCharacteristic?
    @Published var log = [TimerControllerLogEventWrapper]()
    
    override init() {
        super.init()
        manager = CBCentralManager(delegate: self, queue: nil)
    }

    func start() {
        if manager.isScanning {
            manager.stopScan()
        }
        manager.scanForPeripherals(withServices: [ServiceUUID], options: nil)
    }

    func send(seconds: UInt16) {
        let times : [UInt16] = [seconds, 60, 5 * 60]

        var message = Data()

        message.append(MessageStart)

        times.forEach { time in
            let parts : [UInt8] = [
                UInt8(time & 0x00FF),
                UInt8(time >> 8)
            ]
            parts.forEach { part in
                message.append(part)
            }
        }

        message.append(MessageEnd)

        if let clockDevice = self.clockDevice, let clockCharacteristic = self.clockCharacteristic {
            clockDevice.writeValue(message, for: clockCharacteristic, type: CBCharacteristicWriteType.withResponse)
        }
    }
}

extension TimerController: CBCentralManagerDelegate {
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        self.log.append(TimerControllerLogEventWrapper(event: TimerControllerManagerStateChangeEvent(state: central.state)))
    }

    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        self.log.append(TimerControllerLogEventWrapper(event: TimerControllerConnectionEvent(eventType: .Discover, device: peripheral)))
        if peripheral.name == PeripheralName {
            self.clockDevice = peripheral
            peripheral.delegate = self
            manager.connect(peripheral, options: nil)
            manager.stopScan()
        }
    }

    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        self.log.append(TimerControllerLogEventWrapper(event: TimerControllerConnectionEvent(eventType: .Connect, device: peripheral)))
        peripheral.discoverServices(nil)
    }

    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        self.log.append(TimerControllerLogEventWrapper(event: TimerControllerConnectionEvent(eventType: .Disconnect, device: peripheral)))
        if let _error = error {
            self.log.append(TimerControllerLogEventWrapper(event: TimerControllerErrorEvent(error: _error)))
        }
        self.start()
    }

    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        if let _error = error {
            self.log.append(TimerControllerLogEventWrapper(event: TimerControllerErrorEvent(error: _error)))
        }
        self.start()
    }
}

extension TimerController: CBPeripheralDelegate {
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else { return }

        for service in services {
            log.append(TimerControllerLogEventWrapper(event: TimerControllerServiceDiscoveredEvent(service: service)))
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }

    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else { return }
        for characteristic in characteristics {
            self.log.append(TimerControllerLogEventWrapper(event: TimerControllerCharacteristicDiscoveredEvent(characteristic: characteristic)))
            if characteristic.uuid.uuidString == CharacteristicUUID.uuidString {
                self.clockCharacteristic = characteristic
            }
        }
    }
}
