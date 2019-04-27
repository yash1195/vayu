//#define IRpin_PIN      PIND
//#define IRpin          2
//
//// the maximum pulse we'll listen for - 65 milliseconds is a long time
//#define MAXPULSE 65000
//#define NUMPULSES 50
//
//// what our timing resolution should be, larger is better
//// as its more 'precise' - but too large and you wont get
//// accurate timing
//#define RESOLUTION 20 
//
//// What percent we will allow in variation to match the same code
//#define FUZZINESS 20
//
//// we will store up to 100 pulse pairs (this is -a lot-)
//uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
//uint8_t currentpulse = 0; // index for pulses we're storing

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

//int latchPin = 5;
//int clockPin = 6;
//int dataPin = 4;

//byte leds = 0;
//int counter = -1;
//int LED_COUNT = 7;

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
//  int numberpulses;
//  
//  numberpulses = listenForIR();
//  
//  Serial.print("Heard ");
//  Serial.print(numberpulses);
//  Serial.println("-pulse long IR signal");
//  
//  if (IRcompare(numberpulses, fanSignal,sizeof(fanSignal)/4)) {
//    Serial.println("FAN BTN");
////    btnPress();
//  } else if (IRcompare(numberpulses, rokuPower,sizeof(rokuPower)/4)) {
//    Serial.println("ROKU POWER");
////    btnPress();
//  } else {
//    Serial.println("Some other Btn");
//  }
////  printpulses();
// 
//  delay(1000);

  
}

//void btnPress() {
//
//  counter++;
//  if (counter == 7) {
//    counter = 0;
//    leds = 0;
//  }
//  
//  
//  bitSet(leds, counter);
//  updateShiftRegister();
//  delay(500);
//}
//
//void updateShiftRegister()
//{
//   digitalWrite(latchPin, LOW);
//   shiftOut(dataPin, clockPin, LSBFIRST, leds);
//   digitalWrite(latchPin, HIGH);
//}
//
////KGO: added size of compare sample. Only compare the minimum of the two
//boolean IRcompare(int numpulses, int Signal[], int refsize) {
//  int count = min(numpulses,refsize);
//  Serial.print("count set to: ");
//  Serial.println(count);
//  for (int i=0; i< count-1; i++) {
//    int oncode = pulses[i][1] * RESOLUTION / 10;
//    int offcode = pulses[i+1][0] * RESOLUTION / 10;
//    
//#ifdef DEBUG    
//    Serial.print(oncode); // the ON signal we heard
//    Serial.print(" - ");
//    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
//#endif   
//    
//    // check to make sure the error is less than FUZZINESS percent
//    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
//#ifdef DEBUG
//      Serial.print(" (ok)");
//#endif
//    } else {
//#ifdef DEBUG
//      Serial.print(" (x)");
//#endif
//      // we didn't match perfectly, return a false match
//      return false;
//    }
//    
//    
//#ifdef DEBUG
//    Serial.print("  \t"); // tab
//    Serial.print(offcode); // the OFF signal we heard
//    Serial.print(" - ");
//    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
//#endif    
//    
//    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
//#ifdef DEBUG
//      Serial.print(" (ok)");
//#endif
//    } else {
//#ifdef DEBUG
//      Serial.print(" (x)");
//#endif
//      // we didn't match perfectly, return a false match
//      return false;
//    }
//    
//#ifdef DEBUG
//    Serial.println();
//#endif
//  }
//  // Everything matched!
//  return true;
//}
//
//int listenForIR(void) {
//  currentpulse = 0;
//  
//  while (1) {
//    uint16_t highpulse, lowpulse;  // temporary storage timing
//    highpulse = lowpulse = 0; // start out with no pulse length
//  
////  while (digitalRead(IRpin)) { // this is too slow!
//    while (IRpin_PIN & (1 << IRpin)) {
//       // pin is still HIGH
//
//       // count off another few microseconds
//       highpulse++;
//       delayMicroseconds(RESOLUTION);
//
//       // If the pulse is too long, we 'timed out' - either nothing
//       // was received or the code is finished, so print what
//       // we've grabbed so far, and then reset
//       
//       // KGO: Added check for end of receive buffer
//       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
//         return currentpulse;
//       }
//    }
//    // we didn't time out so lets stash the reading
//    pulses[currentpulse][0] = highpulse;
//  
//    // same as above
//    while (! (IRpin_PIN & _BV(IRpin))) {
//       // pin is still LOW
//       lowpulse++;
//       delayMicroseconds(RESOLUTION);
//        // KGO: Added check for end of receive buffer
//        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
//         return currentpulse;
//       }
//    }
//    pulses[currentpulse][1] = lowpulse;
//
//    // we read one high-low pulse successfully, continue!
//    currentpulse++;
//  }
//}
//
//    void printpulses(void) {
//      Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
//      for (uint8_t i = 0; i < currentpulse; i++) {
//        Serial.print(pulses[i][0] * RESOLUTION, DEC);
//        Serial.print(" usec, ");
//        Serial.print(pulses[i][1] * RESOLUTION, DEC);
//        Serial.println(" usec");
//      }
//     
//      // print it in a 'array' format
//      Serial.println("int IRsignal[] = {");
//      Serial.println("// ON, OFF (in 10's of microseconds)");
//      for (uint8_t i = 0; i < currentpulse-1; i++) {
//        Serial.print("\t"); // tab
//        Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
//        Serial.print(", ");
//        Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
//        Serial.println(",");
//      }
//      Serial.print("\t"); // tab
//      Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
//      Serial.print(", 0};");
//    }


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
  
  // This is the code for my particular Nikon, for others use the tutorial
  // to 'grab' the proper code from the remote
 
//  pulseIR(2080);
//  delay(27);
//  pulseIR(440);
//  delayMicroseconds(1500);
//  pulseIR(460);
//  delayMicroseconds(3440);
//  pulseIR(480);
// 
// 
//  delay(65); // wait 65 milliseconds before sending it again
// 
//  pulseIR(2000);
//  delay(27);
//  pulseIR(440);
//  delayMicroseconds(1500);
//  pulseIR(460);
//  delayMicroseconds(3440);
//  pulseIR(480);
}
