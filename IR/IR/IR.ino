
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

int rokuPower[] = {
// ON, OFF (in 10's of microseconds)
  914, 452,
  60, 54,
  62, 166,
  60, 54,
  62, 164,
  62, 52,
  62, 166,
  60, 166,
  60, 168,
  60, 166,
  60, 166,
  62, 164,
  62, 54,
  62, 52,
  60, 54,
  62, 164,
  62, 166,
  60, 166,
  62, 164,
  62, 166,
  60, 54,
  60, 166,
  62, 54,
  60, 54,
  60, 54,
  60, 54,
  60, 54,
  62, 52,
  62, 166,
  62, 52,
  60, 166,
  60, 168,
  60, 166,
  62, 3834,
  914, 452,
  64, 50,
  64, 164,
  62, 52,
  64, 162,
  64, 50,
  64, 162,
  66, 162,
  64, 162,
  64, 164,
  64, 162,
  64, 162,
  64, 50,
  66, 50,
  64, 50,
  64, 0};

int signalLen = 0;
int IRledPin = 13;

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  12;

int buttonState = 0; 

// loop
int i;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to transmit IR!");
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(IRledPin, OUTPUT);
//  pinMode(latchPin, OUTPUT);
//  pinMode(dataPin, OUTPUT);  
//  pinMode(clockPin, OUTPUT);
}

void loop(void) {

   buttonState = digitalRead(buttonPin);
   // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);

    // send signal
    sendCode(fanSignal, 100);

    delay(2000);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
 
}

// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}

void sendCode(int signal[], int len) {

//  bool flag = true;
//  for (i = 0; i < len; i++ ) {
//    long pulseLen = signal[i]*10;
//    Serial.println(pulseLen);
//    if (flag) {
//      pulseIR(pulseLen);
//      flag = false;
//    } else {
//      delayMicroseconds(pulseLen);
//      flag = true; 
//    }
//  }

  long pulseLen1 = 0;
  long pulseLen2 = 0;

  for (i = 0; i < len; i = i+2 ) {
    pulseLen1 = signal[i]*10;
    pulseLen2 = signal[i + 1]*10;
    pulseIR(pulseLen1);
    delayMicroseconds(pulseLen2);
    
  }
  
}
