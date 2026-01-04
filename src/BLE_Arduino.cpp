#include "BLEWrapper.hpp"
#include <BTstackLib.h>

class ArduinoBLEAdapter : public BLEWrapper {
    BLECharacteristic myChar{"1234", BLERead | BLEWrite | BLENotify, 20};

public:
    bool begin(std::string name) override {
        if (!BLE.begin()) return false;
        BLE.setLocalName(name.c_str());
        
        BLEService myService("ABCD");
        BLE.setAdvertisedService(myService);
        myService.addCharacteristic(myChar);
        BLE.addService(myService);
        
        BLE.advertise();
        return true;
    }

    void updateValue(const std::string& value) override {
        myChar.writeValue(value.c_str());
    }

    void poll() override {
        BLE.poll();
        if (myChar.written()) {
            if (onDataReceived) {
                // Wert auslesen und Callback feuern
                uint8_t buffer[20];
                int len = myChar.readValue(buffer, 20);
                onDataReceived(std::string((char*)buffer, len));
            }
        }
    }
};

BLEWrapper* createBLE() { return new ArduinoBLEAdapter(); }
