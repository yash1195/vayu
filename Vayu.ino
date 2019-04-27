// Libraries
#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi101.h>

/************************* WiFI Setup *****************************/

// Mobile hotspot
char ssid[] = "zekoFi";     //  your network SSID (name)
char pass[] = "hellozeko";    // your network password (use for WPA, or use as key for WEP)

// Home Wifi
//char ssid[] = "Ghar Wifi";     //  your network SSID (name)
//char pass[] = "silentearth285";    // your network password (use for WPA, or use as key for WEP)

// Demo Wifi
//char ssid[] = "sealab";     //  your network SSID (name)
//char pass[] = "Gh0meDemo";    // your network password (use for WPA, or use as key for WEP)


int status = WL_IDLE_STATUS;


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

#define AIO_USERNAME  "yashchoukse"
#define AIO_KEY       "308a5f7982d54f0ead4e0269fb17e2bb"


//Set up the wifi client
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Constants
char VAYU_FAN_FEED[] = "yashchoukse/feeds/vayunetwork.fan-control";

// API signals
uint16_t FAN_POWER_TOGGLE_SIGNAL = 5;
uint16_t FAN_SPEED_TOGGLE_SIGNAL = 6;
uint16_t FAN_SWING_TOGGLE_SIGNAL = 7;

// Fan Feed subscription
Adafruit_MQTT_Subscribe CONTROL_SIGNAL = Adafruit_MQTT_Subscribe(&mqtt, VAYU_FAN_FEED);

void connectWifi(void);
void connectToAdafruitIO(void);
uint16_t signal_val = 0;

// output pins
//int power_signal_pin = A0;
//int speed_signal_pin = A1;
//int swing_signal_pin = A2;
uint16_t power_signal_pin = 3;
uint16_t speed_signal_pin = 6;
uint16_t swing_signal_pin = 9;

uint16_t led = 8;

void setup() {

  pinMode(led, OUTPUT);

  pinMode(power_signal_pin, OUTPUT);
  pinMode(speed_signal_pin, OUTPUT);
  pinMode(swing_signal_pin, OUTPUT);
  
  digitalWrite(power_signal_pin, LOW);
  digitalWrite(speed_signal_pin, LOW);
  digitalWrite(swing_signal_pin, LOW);

  while (!Serial);
  Serial.begin(115200);

  // check for the presence of the breakout
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("Shield -1"));
    // don't continue:
    while (true);
  }
 
  Serial.println();

  mqtt.subscribe(&CONTROL_SIGNAL);

  connectWifi();
  connectToAdafruitIO();

  delay(1000);

}

void loop() {

  Serial.println("New Epoch");

  // check if wifi is connected
  connectWifi();
  connectToAdafruitIO();
  scan_fan_feed();
  
  Serial.print("Firing signal: ");
  Serial.println(signal_val);
  
  if (signal_val == FAN_POWER_TOGGLE_SIGNAL) {
      
      digitalWrite(power_signal_pin, HIGH);
      digitalWrite(led, HIGH);
      delay(3000);
      digitalWrite(led, LOW);
      digitalWrite(power_signal_pin, LOW);
      
  } else if (signal_val == FAN_SPEED_TOGGLE_SIGNAL) {
      
      digitalWrite(speed_signal_pin, HIGH);
      digitalWrite(led, HIGH);
      delay(3000);
      digitalWrite(led, LOW);
      digitalWrite(speed_signal_pin, LOW);
      
  } else if (signal_val == FAN_SWING_TOGGLE_SIGNAL) {
      
      digitalWrite(swing_signal_pin, HIGH);
      digitalWrite(led, HIGH);
      delay(3000);
      digitalWrite(led, LOW);
      digitalWrite(swing_signal_pin, LOW);
  }

  signal_val = 0;
  
  Serial.println();
  delay(2000);
}

void scan_fan_feed() {
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(2000))) {
    if (subscription == &CONTROL_SIGNAL) {
      Serial.print("RECV: ");
      Serial.println((char *)CONTROL_SIGNAL.lastread);
      if (strcmp((char *)CONTROL_SIGNAL.lastread, "5") == 0) {
        signal_val = 5;
      } else if (strcmp((char *)CONTROL_SIGNAL.lastread, "6") == 0) {
        signal_val = 6;
      } else if (strcmp((char *)CONTROL_SIGNAL.lastread, "7") == 0) {
        signal_val = 7;
      }
    }
  }
}


void connectWifi() {
  int count = 1;
  while (WiFi.status() != WL_CONNECTED) {
    
//    Serial.print("Wifi Try ");
    Serial.println(count);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    uint8_t timeout = 10;
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;
      delay(1000);
    }

    count++;
  }

//  Serial.println("Wifi 1");
  // DEBUG
//  Serial.println("Wifi connected");
}  

void connectToAdafruitIO() {
  while (!mqtt.connected()) {
//    Serial.println("MQTT 0");
//    Serial.println("Retrying MQTT connection in 2 seconds...");
    delay(1000);
    delay(1000);
    int ret = mqtt.connect();
    delay(1000);
  }
  // DEBUG
//  Serial.println("MQTT 1");
}
