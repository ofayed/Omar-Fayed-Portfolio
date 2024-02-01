#include "BLEDevice.h"
#include <Wire.h>
#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h"

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;


unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;


//-------------------------------------------------------------------------

//BLE Server name (the other ESP32 name running the server sketch)
#define bleServerName "BLE_IoT_Project"

/* UUID's of the service, characteristic that we want to read*/
// BLE Service
static BLEUUID bmeServiceUUID("03616e2f-1b26-4944-acca-cc3e43508468");

// BLE Characteristics
// Temperature Characteristic
static BLEUUID temperatureCharacteristicUUID("cba1d466-344c-4be3-ab3f-189f80dd7518");

// Humidity Characteristic
static BLEUUID humidityCharacteristicUUID("1fc52300-e1ef-11ed-b5ea-0242ac120002");

// Humidity Characteristic
static BLEUUID MQ135CharacteristicUUID("ca73b3ba-39f6-4ab3-91ae-186dc9577d99");

// Humidity Characteristic
static BLEUUID LDRCharacteristicUUID("f932c922-e1ee-11ed-b5ea-0242ac120002");

//Flags stating if should begin connecting and if the connection is up
static boolean doConnect = false;
static boolean connected = false;

//Address of the peripheral device. Address will be found during scanning...
static BLEAddress *pServerAddress;
 
//Characteristicd that we want to read
static BLERemoteCharacteristic* temperatureCharacteristic;
static BLERemoteCharacteristic* humidityCharacteristic;
static BLERemoteCharacteristic* MQ135Characteristic;
static BLERemoteCharacteristic* LDRCharacteristic;

//Activate notify
const uint8_t notificationOn[] = {0x1, 0x0};
const uint8_t notificationOff[] = {0x0, 0x0};


//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)


//Variables to store temperature and humidity
char* temperatureChar;
char* humidityChar;
char* MQ135Char;
char* LDRChar;

//Flags to check whether new temperature and humidity readings are available
boolean newTemperature = false;
boolean newHumidity = false;
boolean newMQ135 = false;
boolean newLDR = false;

//Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) {
   BLEClient* pClient = BLEDevice::createClient();
 
  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");
 
  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(bmeServiceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(bmeServiceUUID.toString().c_str());
    return (false);
  }
 
  // Obtain a reference to the characteristics in the service of the remote BLE server.
  temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
  humidityCharacteristic = pRemoteService->getCharacteristic(humidityCharacteristicUUID);
  MQ135Characteristic = pRemoteService->getCharacteristic(MQ135CharacteristicUUID);
  LDRCharacteristic = pRemoteService->getCharacteristic(LDRCharacteristicUUID);

  if (temperatureCharacteristic == nullptr || humidityCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID");
    return false;
  }
  Serial.println(" - Found our characteristics");
 
  //Assign callback functions for the Characteristics
  temperatureCharacteristic->registerForNotify(temperatureNotifyCallback);
  humidityCharacteristic->registerForNotify(humidityNotifyCallback);
  MQ135Characteristic->registerForNotify(MQ135NotifyCallback);
  LDRCharacteristic->registerForNotify(LDRNotifyCallback);
  return true;
}

//Callback function that gets called, when another device's advertisement has been received
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == bleServerName) { //Check if the name of the advertiser matches
      advertisedDevice.getScan()->stop(); //Scan can be stopped, we found what we are looking for
      pServerAddress = new BLEAddress(advertisedDevice.getAddress()); //Address of advertiser is the one we need
      doConnect = true; //Set indicator, stating that we are ready to connect
      Serial.println("Device found. Connecting!");
    }
  }
};
 
//When the BLE Server sends a new temperature reading with the notify property
static void temperatureNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                                        uint8_t* pData, size_t length, bool isNotify) {
  //store temperature value
  temperatureChar = (char*)pData;
  newTemperature = true;
}

//When the BLE Server sends a new humidity reading with the notify property
static void humidityNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                                    uint8_t* pData, size_t length, bool isNotify) {
  //store humidity value
  humidityChar = (char*)pData;
  newHumidity = true;
  // Serial.print(newHumidity);
}

static void MQ135NotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                                    uint8_t* pData, size_t length, bool isNotify) {
  //store MQ135 value
  MQ135Char = (char*)pData;
  newMQ135 = true;
  // Serial.print(newMQ135);
}

static void LDRNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                                    uint8_t* pData, size_t length, bool isNotify) {
  //store LDR value
  LDRChar = (char*)pData;
  newLDR = true;
  // Serial.print(newLDR);
}

void printReadings(){
 
  // display temperature
  Serial.print("Temperature:");
  Serial.print(temperatureChar);
  Serial.print("C, ");

  //display humidity
  Serial.print(" Humidity:");
  Serial.print(humidityChar);
  Serial.print("%, ");

  //display MQ135
  Serial.print(" MQ135:");
  Serial.print(MQ135Char);
  Serial.print("PPM, ");

  //display LDR
  Serial.print(" LDR:");
  Serial.print(LDRChar);
  Serial.println(" ");

}

void setup() {
  
  //Start serial communication
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");

  //Init BLE device
  BLEDevice::init("");
 
  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);

  // Cloud
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      //Activate the Notify property of each Characteristic
      temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      humidityCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      MQ135Characteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      LDRCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      connected = true;
    } else {
      Serial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
  }

  //----------------------------------------------------------------------------------
  //  Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected to Cloud.");
  }

  int tempCloud = ThingSpeak.setField(1, temperatureChar);
  int humidityCloud = ThingSpeak.setField(2, humidityChar);
  int MQ135Cloud = ThingSpeak.setField(3, MQ135Char);
  int LDRCloud = ThingSpeak.setField(4, LDRChar);
  // int tempCloud = ThingSpeak.writeField(myChannelNumber, 1, temperatureChar, myWriteAPIKey);
  // int humidityCloud = ThingSpeak.writeField(myChannelNumber, 2, humidityChar, myWriteAPIKey);
  // int MQ135Cloud = ThingSpeak.writeField(myChannelNumber, 3, MQ135Char, myWriteAPIKey);
  // int LDRCloud = ThingSpeak.writeField(myChannelNumber, 4, LDRChar, myWriteAPIKey);
  
  if(tempCloud == 200 && humidityCloud == 200 && MQ135Cloud == 200 && LDRCloud == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(tempCloud));
  }
  //----------------------------------------------------------------------------------

 
  //if new temperature readings are available, print in the OLED
  if (newTemperature && newHumidity && newMQ135 && newLDR){
    newTemperature = false;
    newHumidity = false;
    newMQ135 = false;
    newLDR = false;
    printReadings();
  }
  delay(10000); // Delay a second between loops.
}