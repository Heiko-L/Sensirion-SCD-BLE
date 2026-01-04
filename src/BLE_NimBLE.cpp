#include "BLEWrapper.hpp"
#include <NimBLEDevice.h>

class NimBLEAdapter : public BLEWrapper, public NimBLECharacteristicCallbacks {
    NimBLECharacteristic* pCharacteristic;

public:
    bool begin(std::string name) override {
        NimBLEDevice::init(name);
        auto* pServer = NimBLEDevice::createServer();
        auto* pService = pServer->createService("ABCD");
        
        pCharacteristic = pService->createCharacteristic(
            "1234", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::NOTIFY
        );
        pCharacteristic->setCallbacks(this); // Hier registrieren wir uns selbst
        
        pService->start();
        pServer->getAdvertising()->start();
        return true;
    }

    // NimBLE Callback
    void onWrite(NimBLECharacteristic* pChar, NimBLEConnInfo& connInfo) override {
        if (onDataReceived) onDataReceived(pChar->getValue());
    }

    void updateValue(const std::string& value) override {
        pCharacteristic->setValue(value);
        pCharacteristic->notify();
    }

    void poll() override {} 
};

BLEWrapper* createBLE() { return new NimBLEAdapter(); }