
#include "BLEDevice.h"
#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

// Define UUIDs:
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID    charUUID_1("beb5483e-36e1-4688-b7f5-ea07361b26a8");
static BLEUUID    charUUID_2("1c95d5e3-d8f7-413a-bf3d-7a2e5d7be87e");
static BLEUUID    charUUID_3("67749b31-c23c-412b-bb36-843c1cc81005");
static BLEUUID    charUUID_4("a90f1306-a062-402c-b3d4-eceea8f9a0c7");
//static BLEUUID    charUUID_5("6c42a52f-7f4b-40c6-95fb-c6a7c023ec76");
//static BLEUUID    charUUID_6("687db66a-749d-4b2d-b75f-6a199273ecae");
//static BLEUUID    charUUID_7("bd17b66c-9159-494d-841d-b377a9dabe09");

// Some variables to keep track on device connected
static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;

// Define pointer for the BLE connection
static BLEAdvertisedDevice* myDevice;
BLERemoteCharacteristic* pRemoteChar_1;
BLERemoteCharacteristic* pRemoteChar_2;
BLERemoteCharacteristic* pRemoteChar_3;
BLERemoteCharacteristic* pRemoteChar_4;
//BLERemoteCharacteristic* pRemoteChar_5;
//BLERemoteCharacteristic* pRemoteChar_6;
//BLERemoteCharacteristic* pRemoteChar_7;

// Callback function for Notify function
static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                            uint8_t* pData,
                            size_t length,
                            bool isNotify) {
  if(pBLERemoteCharacteristic->getUUID().toString() == charUUID_1.toString()) {

    // convert received bytes to integer
    uint32_t counter = pData[0];
    for(int i = 1; i<length; i++) {
      counter = counter | (pData[i] << i*8);
    }

    // print to Serial
    Serial.print("Characteristic 1 (Notify) from server: ");
    Serial.println(counter );  
  }
}

// Callback function that is called whenever a client is connected or disconnected
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

// Function that is run whenever the server is connected
bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());
  
  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  connected = true;
  pRemoteChar_1 = pRemoteService->getCharacteristic(charUUID_1);
  pRemoteChar_2 = pRemoteService->getCharacteristic(charUUID_2);
  pRemoteChar_3 = pRemoteService->getCharacteristic(charUUID_3);
  pRemoteChar_4 = pRemoteService->getCharacteristic(charUUID_4);
  /*pRemoteChar_5 = pRemoteService->getCharacteristic(charUUID_5);
  pRemoteChar_6 = pRemoteService->getCharacteristic(charUUID_6);
  pRemoteChar_7 = pRemoteService->getCharacteristic(charUUID_7);
*/
  if(connectCharacteristic(pRemoteService, pRemoteChar_1) == false)
    connected = false;
  else if(connectCharacteristic(pRemoteService, pRemoteChar_2) == false)
    connected = false;
  else if(connectCharacteristic(pRemoteService, pRemoteChar_3) == false)
    connected = false;
  else if(connectCharacteristic(pRemoteService, pRemoteChar_4) == false)
    connected = false;
 /* else if(connectCharacteristic(pRemoteService, pRemoteChar_5) == false)
    connected = false;
  else if(connectCharacteristic(pRemoteService, pRemoteChar_6) == false)
    connected = false;
  else if(connectCharacteristic(pRemoteService, pRemoteChar_7) == false)
    connected = false;
*/
  if(connected == false) {
    pClient-> disconnect();
    Serial.println("At least one characteristic UUID not found");
    return false;
  }
  return true;
}

// Function to chech Characteristic
bool connectCharacteristic(BLERemoteService* pRemoteService, BLERemoteCharacteristic* l_BLERemoteChar) {
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  if (l_BLERemoteChar == nullptr) {
    Serial.print("Failed to find one of the characteristics");
    Serial.print(l_BLERemoteChar->getUUID().toString().c_str());
    return false;
  }
  Serial.println(" - Found characteristic: " + String(l_BLERemoteChar->getUUID().toString().c_str()));

  if(l_BLERemoteChar->canNotify())
    l_BLERemoteChar->registerForNotify(notifyCallback);

  return true;
}

// Scan for BLE servers and find the first one that advertises the service we are looking for.
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  //Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());
  
    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
  
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;
  
    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

const char* value1;
const char* value2;
const char* value3;
const char* value4;
const char* value5;
const char* value6;
const char* value7;
String myStatus = "";

void setup() {

  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\n WIFI Connected.");
  }

  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }


  if (connected) {
    
  
    std::string rxValue1 = pRemoteChar_1->readValue();
    Serial.print("Characteristic 1 (readValue): ");
    Serial.println(rxValue1.c_str());
    value1= rxValue1.c_str();
    ThingSpeak.setField(1, value1);

    std::string rxValue2 = pRemoteChar_2->readValue();
    Serial.print("Characteristic 2 (readValue): ");
    Serial.println(rxValue2.c_str());
    value2= rxValue2.c_str();
    ThingSpeak.setField(2, value2);
  
    std::string rxValue3 = pRemoteChar_3->readValue();
    Serial.print("Characteristic 3 (readValue): ");
    Serial.println(rxValue3.c_str());
    value3= rxValue3.c_str();
    ThingSpeak.setField(3, value3);

    std::string rxValue4 = pRemoteChar_4->readValue();
    Serial.print("Characteristic 4 (readValue): ");
    Serial.println(rxValue4.c_str());
    value4= rxValue4.c_str();
    ThingSpeak.setField(4, value4);

    int value5 = atoi(rxValue1.c_str());
    if(value5  >=1250){
      ThingSpeak.setField(5, 1);
      ThingSpeak.setField(6, 1);
    }
    else{
      ThingSpeak.setField(5, 0);
      ThingSpeak.setField(6, 0);
    }
    
    int value6 = atoi(rxValue4.c_str());
    if(value6>=600){
        ThingSpeak.setField(7, 1);
    }
    else{
      ThingSpeak.setField(7, 0);
    }
    
    // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }


  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}

