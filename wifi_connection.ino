#include <Servo.h>
#include <SPI.h>
#include <WiFi101.h>
#include <aREST.h>

Servo servo1; // create servo motor object
Servo servo2;
int pos1 = 0;
int pos2 = 0;
char ssid[] = "AndroidAP";     //  your network SSID (name)
char pass[] = "dswd0073";    // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
aREST rest = aREST();

//the port to listen for incoming TCP connection
#define LISTEN_PORT 80

//create an instance of the server
WiFiServer server(LISTEN_PORT);

int iter = 1;

int forward(String s) {
  int length = s.toInt();
  // start();
  // delay(20);
  for (int i = 0; i < length; i++) {
    servo1.attach(9);
    servo1.write(1);
    delay(300);
    servo1.detach();
    servo2.attach(10);
    servo2.write(179);
    delay(260);
    servo2.detach();
  }
  //stop();
  delay(20);
  return 0;
}

int backward(String s) {
  int length = s.toInt();
  // start();
  // delay(20);
  for (int i = 0; i < length; i++) {
    servo1.attach(9);
    servo1.write(179);
    delay(260);
    servo1.detach();
    servo2.attach(10);
    servo2.write(1);
    delay(190);
    servo2.detach();
  }
  // stop();
  // delay(20);
  return 0;
}

int right(String s) {
  int length = s.toInt();
  Serial.println(length);
  // start();
  // delay(20);
  for (int i = 0; i < length; i++) {
    servo2.write(120);
    delay(1000);
    /*servo2.detach();
      delay(10);
      servo1.write(120);
      delay(1000);
      servo1.detach();
      delay(10);*/
  }
  // stop();
  // delay(20);
  return 0;
}

int left(String s) {
  int length = s.toInt();
  start();
  delay(20);
  for (int i = 0; i < length; i++) {
    //servo1.write(1);
    servo2.write(1);
    delay(1000);
  }
  stop();
  delay(20);
  return 0;
}

void stop() {
  servo1.detach();
  servo2.detach();
  delay(10);
}

void start() {
  servo1.attach(9);
  servo2.attach(10);
}

void setup() {
  // initialize serial and wait for the port to open:
  Serial.begin(9600);
  // scan for existing networks:
  Serial.println("Scanning available networks...");
  listNetworks();
  // attempt to connect using WEP encryption:
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);
  if (status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }
  else {
    // if you are connected, print out info about the connection:
    Serial.println("Connected to network");
  }

  server.begin();

  //give name and ID to the device
  rest.set_id("1");
  rest.set_name("mk1000");
  //Define API functions
  rest.function("left", left);
  rest.function("right", right);
  rest.function("forward", forward);
  rest.function("backward", backward);

  //printMacAddress();
  //print the IP address
  IPAddress ip = WiFi.localIP();
  Serial.println("IP Address:  ");
  Serial.println (ip);

}

void loop() {
  if ( WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost!");
  }
  //Handle REST level
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available()) {
    delay(1);
  }

  rest.handle(client);
  Serial.println("Command done");
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}


