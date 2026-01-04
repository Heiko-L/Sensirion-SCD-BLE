#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

const uint8_t BLE_AD_TYPE_FLAGS = 0x01;
const uint8_t BLE_AD_TYPE_MSD = 0xFF;
const uint8_t BLE_FLAGS_GENERAL_DISCOVERABLE_BLE_ONLY = 0x06;
const uint8_t BLE_AD_TYPE_SHORTENED_LOCAL_NAME = 0x08;

union BleAdvertisingDataFlagRegister {
    uint8_t raw_;  // Der gesamte Wert als Integer

    struct {  // Die einzelnen Bits
        uint8_t leLimitedDiscMode_ : 1;
        uint8_t leGeneralDiscMode_ : 1;
        uint8_t brEdrNotSupported_ : 1;
        uint8_t leBrEdrController_ : 1;
        uint8_t reserved_ : 4;
    } flags_;
};

#pragma pack(push, 1)  // Verhindert Padding (Füllbits)
struct MeasurementDataStructure {
    uint16_t temperature_;
    uint8_t humidity_;
    uint16_t co2_;
    uint8_t battery_;
};
#pragma pack(pop)

union MeasurementData {
    std::array<uint8_t, sizeof(MeasurementDataStructure)> raw_;
    MeasurementDataStructure item_{};
};

class BLEWrapper {
public:
    static auto create() -> BLEWrapper*;
    void setupAdvertising();

    // virtual bool begin(std::string name) = 0;
    virtual void poll() = 0;

    // Eine einfache Methode, um einen String-Wert zu senden
    // virtual void updateValue(const std::string& value) = 0;

    // Callback, wenn Daten empfangen werden
    // std::function<void(std::string)> onDataReceived;

    virtual ~BLEWrapper() = default;

private:
    std::vector<uint8_t> advData_{};
    BleAdvertisingDataFlagRegister adFlags_{.raw_ = 0x06};
    MeasurementData measurements_{.raw_ = 0x00};
};
