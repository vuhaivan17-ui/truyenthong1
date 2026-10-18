#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// ===============================
// Khai bao chan LED
// ===============================
#define LED_PIN 1

// ===============================
// UUID BLE
// ===============================
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Bien Characteristic
BLECharacteristic *pCharacteristic;


// ===============================
// Xu ly khi dien thoai ket noi
// ===============================
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("iPhone da ket noi!");
  }

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("iPhone da ngat ket noi!");

    // Cho phep ket noi lai
    BLEDevice::startAdvertising();
  }
};


// ===============================
// Xu ly khi iPhone gui du lieu
// ===============================
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    String value = pCharacteristic->getValue();

    Serial.print("Nhan duoc: ");
    Serial.println(value);

    // Neu iPhone gui 1
    if (value == "1")
    {
      digitalWrite(LED_PIN, HIGH);

      Serial.println("LED BAT");

      // Gui trang thai ve iPhone
      pCharacteristic->setValue("LED ON");
    }

    // Neu iPhone gui 0
    else if (value == "0")
    {
      digitalWrite(LED_PIN, LOW);

      Serial.println("LED TAT");

      // Gui trang thai ve iPhone
      pCharacteristic->setValue("LED OFF");
    }

    // Neu gui ky tu khac
    else
    {
      Serial.println("Lenh khong hop le!");

      pCharacteristic->setValue("Chi nhan 1 hoac 0");
    }
  }
};


// ===============================
// SETUP
// ===============================
void setup()
{
  // Khoi dong Serial
  Serial.begin(115200);

  delay(1000);

  // Cau hinh GPIO1 lam OUTPUT
  pinMode(LED_PIN, OUTPUT);

  // Ban dau tat LED
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32-S3 BLE LED");
  Serial.println("==============================");

  // Khoi tao BLE
  BLEDevice::init("VÂN");

  // Tao BLE Server
  BLEServer *pServer = BLEDevice::createServer();

  // Gan su kien ket noi
  pServer->setCallbacks(new MyServerCallbacks());

  // Tao Service
  BLEService *pService =
      pServer->createService(SERVICE_UUID);

  // Tao Characteristic
  pCharacteristic =
      pService->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE
      );

  // Gan ham xu ly khi iPhone gui du lieu
  pCharacteristic->setCallbacks(
      new MyCharacteristicCallbacks()
  );

  // Du lieu ban dau
  pCharacteristic->setValue("LED OFF");

  // Bat dau Service
  pService->start();

  // Cau hinh quang ba BLE
  BLEAdvertising *pAdvertising =
      BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);

  // Bat dau quang ba
  BLEDevice::startAdvertising();

  Serial.println("BLE da khoi dong!");
  Serial.println("Ten: ESP 32 11");
  Serial.println("GPIO LED: GPIO1");
  Serial.println("Gui 1 = BAT LED");
  Serial.println("Gui 0 = TAT LED");
  Serial.println("==============================");
}


// ===============================
// LOOP
// ===============================
void loop()
{
  delay(1000);
}