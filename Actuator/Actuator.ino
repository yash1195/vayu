#include <SoftwareSerial.h>
#include <AlertNodeLib.h>

#define EndOfInput '$'

// XBee stuff

// set to control serial monitor output from this program
boolean myDebugging = true;

// a constant to identify this node to the library object
const String myNodeName = "Room 42";

// just some aliases to make code more readable
const boolean SENDING = true;
const boolean RECEIVING = false;

// this connects the program to the XBee module
// you must use pin 2 for TX and pin 3 for RX
// the XBee must be set to 9600 baud
AlertNode myNode;

// XBee stuff ends

String message = "";

//SoftwareSerial XBee(2, 3); // RX, TX

int ir_led_pin = A4;
int power_signal_in = 10;
int speed_signal_in = 11;
int swing_signal_in = 12;

int led1 = 6;
int led2 = 7;
int led3 = 8;

int power_signal_val = 0;
int speed_signal_val = 0;
int swing_signal_val = 0;

int fanSignal[] = {
  130, 44,
  132, 40,
  46, 128,
  132, 42,
  134, 40,
  134, 40,
  44, 130,
  46, 128,
  46, 128,
  132, 42,
  132, 40,
  46, 824,
  134, 40,
  134, 40,
  46, 128,
  132, 42,
  132, 42,
  132, 42,
  46, 128,
  46, 128,
  44, 130,
  132, 40,
  134, 40,
  46, 824,
  132, 42,
  132, 42,
  46, 128,
  132, 42,
  132, 42,
  132, 40,
  46, 130,
  44, 128,
  46, 128,
  134, 40,
  132, 42,
  46, 824,
  132, 42,
  132, 42,
  44, 130,
  132, 44,
  130, 44,
  130, 44,
  42, 128,
  46, 128,
  46, 128,
  132, 44,
  130, 44,
  44, 824,
  132, 44,
  130, 0};

uint16_t power_control_code[] = {
// ON, OFF (in 10's of microseconds)
  134, 40,
  136, 38,
  48, 126,
  136, 38,
  134, 40,
  48, 124,
  50, 126,
  48, 124,
  50, 124,
  136, 38,
  48, 126,
  48, 822,
  136, 38,
  136, 38,
  48, 126,
  136, 38,
  136, 38,
  48, 126,
  48, 126,
  48, 126,
  48, 126,
  138, 36,
  48, 126,
  48, 822,
  134, 40,
  134, 40,
  54, 120,
  134, 38,
  136, 40,
  48, 124,
  48, 126,
  50, 124,
  48, 126,
  136, 38,
  48, 126,
  48, 822,
  144, 30,
  136, 38,
  50, 124,
  136, 38,
  134, 40,
  48, 126,
  48, 126,
  48, 126,
  48, 126,
  136, 38,
  48, 126,
  48, 822,
  134, 40,
  134, 0};

uint16_t speed_control_code[] = {
// ON, OFF (in 10's of microseconds)
  132, 42,
  132, 42,
  44, 130,
  132, 40,
  134, 42,
  132, 40,
  46, 128,
  46, 128,
  46, 128,
  134, 40,
  132, 42,
  46, 824,
  132, 42,
  132, 42,
  46, 128,
  132, 42,
  132, 42,
  132, 42,
  46, 128,
  44, 130,
  46, 128,
  132, 42,
  130, 44,
  44, 826,
  132, 42,
  132, 40,
  46, 130,
  130, 42,
  134, 40,
  132, 42,
  46, 128,
  46, 128,
  46, 128,
  132, 42,
  134, 40,
  46, 824,
  132, 42,
  132, 42,
  44, 130,
  134, 40,
  132, 42,
  132, 42,
  44, 130,
  46, 128,
  44, 130,
  132, 42,
  132, 42,
  44, 826,
  132, 42,
  132, 0};
  
uint16_t swing_control_code[] = {
// ON, OFF (in 10's of microseconds)
  132, 42,
  132, 42,
  44, 130,
  132, 42,
  132, 42,
  132, 42,
  44, 130,
  46, 128,
  44, 130,
  44, 130,
  132, 40,
  132, 740,
  132, 42,
  132, 42,
  44, 130,
  132, 40,
  134, 42,
  132, 42,
  44, 128,
  46, 130,
  44, 128,
  46, 128,
  134, 40,
  134, 738,
  132, 42,
  130, 44,
  44, 128,
  134, 42,
  132, 40,
  134, 40,
  46, 130,
  44, 128,
  46, 128,
  46, 128,
  132, 42,
  132, 740,
  132, 42,
  132, 40,
  46, 130,
  130, 42,
  134, 40,
  132, 42,
  46, 128,
  46, 128,
  46, 128,
  46, 128,
  134, 40,
  132, 738,
  134, 40,
  132, 0};

void setup() {

  while (!Serial);
  Serial.begin(9600);

  Serial.print("\n\n*** Radio name: ");
  Serial.println(myNodeName);

  // change the value in this call to control debugging messages from the library
  myNode.setDebug(false);

  // this starts up the XBee and does other AlertNode initialization stuff.
  // the argument is just to identify your node by a name.
  myNode.begin(myNodeName);

  pinMode(ir_led_pin, OUTPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(power_signal_in, INPUT);
  pinMode(speed_signal_in, INPUT);
  pinMode(swing_signal_in, INPUT);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

}



void loop() {

  power_signal_val = digitalRead(power_signal_in);
  speed_signal_val = digitalRead(speed_signal_in);
  swing_signal_val = digitalRead(swing_signal_in);

//  // debug
//  Serial.println(power_signal_val);
//  Serial.println(speed_signal_val);
//  Serial.println(swing_signal_val);
  
  if (power_signal_val == HIGH) {
    Serial.println("power");
    digitalWrite(led1, HIGH);

    // send IR signal
    sendCode(power_control_code, sizeof(power_control_code)/sizeof(uint16_t));
    
    delay(3500);
    digitalWrite(led1, LOW);
    
  } else if (speed_signal_val == HIGH) {
    Serial.println("speed");
    digitalWrite(led2, HIGH);

    // send IR signal
    sendCode(speed_control_code, sizeof(speed_control_code)/sizeof(uint16_t));
    
    delay(3500);
    digitalWrite(led2, LOW);
    
  } else if (swing_signal_val == HIGH) {
    Serial.println("swing");
    digitalWrite(led3, HIGH);

    // send IR signal
    sendCode(swing_control_code, sizeof(swing_control_code)/sizeof(uint16_t));
    
    delay(3500);
    digitalWrite(led3, LOW);
  }

  Serial.println();

  power_signal_val = 0;
  speed_signal_val = 0;
  swing_signal_val = 0;

  // check for an incoming alert
  // alertReceived() returns 0 (NO_ALERT) if none have been received.
  // the method only returns an actual alert code when a complete and valid
  // alert message has been received.
  int alert = myNode.alertReceived();
  if (alert != AlertNode::NO_ALERT) {

    Serial.print("*** Alert received: ");
    Serial.print(alert);
    Serial.print(" ");
    Serial.println(myNode.alertName(alert));

    // send IR signal
    sendCode(power_control_code, sizeof(power_control_code)/sizeof(uint16_t));
    
    // do somehting
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(500);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(500);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  delay(500);

 

//  // check if there was a control message
//  char signal;
//  while(XBee.available()>0){
//    signal = XBee.read();
//    message+=signal;
//  }
//
//  int messageLen = message.length();
//  int lastCharIndex = messageLen - 1;
//
//  // Outputs the message to serial monitor
//  if (message[lastCharIndex] == EndOfInput) {
//    Serial.print("Control Message: ");
//    Serial.println(message.substring(0, messageLen - 1));
//    
//    // Sends an acknowledgement
//    XBee.println("CONTROL MESSAGE RECEIVED");
//    message = "";
//  }

//   int alert = myNode.alertReceived();
//   Serial.println(alert);
//   if (alert != AlertNode::NO_ALERT) {
//    Serial.print("*** Alert received: ");
//    Serial.print(alert);
//    Serial.print(" ");
//    Serial.println(myNode.alertName(alert)); 
//   }

//  delay(1000);
}

void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(ir_led_pin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(ir_led_pin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

void sendCode(int signal[], int len) {
  
  long pulseLen1 = 0;
  long pulseLen2 = 0;

  for (int i = 0; i < len; i = i+2 ) {
    pulseLen1 = signal[i]*10;
    pulseLen2 = signal[i + 1]*10;
    pulseIR(pulseLen1);
    delayMicroseconds(pulseLen2);   
  }
}
