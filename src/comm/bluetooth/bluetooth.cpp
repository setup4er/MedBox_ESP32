#include "comm/bluetooth.h"

// System includes
#include <Arduino.h>
#include <NimBLEDevice.h>

// Project includes
#include "drivers/dbg_led.h"
#include "config.h"

static NimBLEServer *pServer = nullptr;
static NimBLEService *pService = nullptr;

static NimBLECharacteristic *rxChar = nullptr; //Прием
static NimBLECharacteristic *txChar = nullptr; //Отправка

static NimBLEAdvertising *pAdv = nullptr;

static String _rxBuffer = "";
static bool _hasMessage = false;

class ServerCallback : public NimBLEServerCallbacks {
public:
    void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override {
        Serial.println("[BLE] Client connected");
    }
    
    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override {
        Serial.print("[BLE] Client disconnected, reason: ");
        Serial.println(reason);
        if (pAdv) {
            pAdv->start();
            Serial.println("[BLE] Advertising restarted");
        }
    }
};

class RxCallback : public NimBLECharacteristicCallbacks {
public:
    void onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo) override{
        std::string res = pCharacteristic->getValue();
        if(res.empty()){
            Serial.println("[BLE_RX] Error. Result of message is empty!");
            return;
        }
        _rxBuffer = String(res.c_str());

        Serial.print("[BLE_RX] Result of message: ");
        Serial.println(_rxBuffer);
        
        _hasMessage = true;
    }
};

void bluetooth_init(){
    NimBLEDevice::init(BLE_DEVICE_NAME);

    pServer = NimBLEDevice::createServer();
    pService = pServer->createService(BLE_UUID_SERVICE);
    rxChar = pService->createCharacteristic(BLE_UUID_RX_CHAR, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR);
    txChar = pService->createCharacteristic(BLE_UUID_TX_CHAR, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    
    // callback
    pServer->setCallbacks(new ServerCallback());
    rxChar->setCallbacks(new RxCallback());

    pAdv = NimBLEDevice::getAdvertising();
    pAdv->addServiceUUID(BLE_UUID_SERVICE);
    pAdv->setName(BLE_DEVICE_NAME);
    if(!pAdv->start()){
        Serial.printf("[BLE] ERROR ! Advertising start failed.");
        set_led_dbg_status(LED_ERR);
    }


    Serial.println("[BLE] Initialization successfully!");
    set_led_dbg_status(LED_OK);
}

void send_bluetooth_message(const String& msg) {
    if (!txChar) return;
    txChar->setValue(msg.c_str());
    txChar->notify();
}


bool has_bluetooth_message() {
    return _hasMessage;
}


String get_bluetooth_message(){
    String result = _rxBuffer;
    _rxBuffer = "";
    _hasMessage = false;
    return result;
}