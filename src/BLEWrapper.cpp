#include "BLEWrapper.hpp"

#include "ble_init.h"

void BLEWrapper::setupAdvertising() {
    advData_.clear();
    // AdvData Flags
    advData_.push_back(2);                  // AD length
    advData_.push_back(BLE_AD_TYPE_FLAGS);  // AD Type (flags)
    advData_.push_back(adFlags_.raw_);      // Flags
    // AdvData Shortened Local Name
    advData_.push_back(BLE_ADVERTISING_SHORTNAME.size() + 1);  // AD length
    advData_.push_back(
        BLE_AD_TYPE_SHORTENED_LOCAL_NAME);  // AD Type (shortened local name)
    advData_.insert(advData_.end(), BLE_ADVERTISING_SHORTNAME.begin(),
                    BLE_ADVERTISING_SHORTNAME.end());  // Short NAme
    // AdvData MSD
    advData_.push_back(BLE_MAGIC_BYTES.size() +
                       sizeof(MeasurementDataStructure) + 3);  // AD length
    advData_.push_back(BLE_AD_TYPE_MSD);                       // AD Type (MSD)
    advData_.push_back(static_cast<uint8_t>(BLE_COMPANY_IDENTIFIER & 0xFF));
    advData_.push_back(
        static_cast<uint8_t>((BLE_COMPANY_IDENTIFIER >> 8) & 0xFF));
    advData_.insert(advData_.end(), BLE_MAGIC_BYTES.begin(),
                    BLE_MAGIC_BYTES.end());
    advData_.insert(advData_.end(), measurements_.raw_.begin(),
                    measurements_.raw_.end());
}
