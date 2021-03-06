/*
   Build your own 'One-For-All HC8300 Light Control' with your Arduino!
   Version 0.2

   This sketch lets you control wireless outlets with your Logitech Harmony Remote.
   You need to add a 'One-For-All HC8300 Light Control'-Device to your Harmony,
   because the IR-codes from this devices remote are used here.
*/
#include "One_For_All_HC_8300_IR_Codes.h"

// Libraries
#include <IRremote.h>
#include <RCSwitch.h>
#define RCSwitchDisableReceiving

// PIN Configuration
#define IR_SENSOR_DATA 2
#define RF_TRANSMITTER_DATA 4

// RF Socket Configuration
char rfSystemCode1[] = "00001";
char rfSocket11[] = "10000"; // Main Poweroutlet
char rfSocket12[] = "01000"; // Couch Lamps
char rfSocket13[] = "00100"; // TV Lamp
char rfSocket14[] = "00010"; // Lightstrip
char rfSocket15[] = "00001"; // Unused

char rfSystemCode2[] = "00010";
char rfSocket21[] = "10000"; // Unused

// Delay
unsigned long powerOffDelay = 60000; // 1 min

decode_results results;
long lastIRCode;

IRrecv irrecv(IR_SENSOR_DATA);
RCSwitch rcSwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(1);
  rcSwitch.enableTransmit(RF_TRANSMITTER_DATA);
}

void loop() {
  if (irrecv.decode(&results)) {

    // REPEAT last IR code
    if (results.value != REPEAT) {
      lastIRCode = results.value;
    }

    Serial.print("Received code ");
    Serial.println(lastIRCode, HEX);

    switch (lastIRCode) {
      case HC8300_1ON: // Socket1 ON
        Serial.println("Switching Main-Poweroutlet on");
        rcSwitch.switchOn(rfSystemCode1, rfSocket11);
        break;

      case HC8300_1OFF: // Socket1 OFF
        Serial.println("Switching Main-Poweroutlet off");
        rcSwitch.switchOff(rfSystemCode1, rfSocket11);
        break;

      case HC8300_2ON: // Socket2 ON
        Serial.println("Switching Couch Lamps on");
        rcSwitch.switchOn(rfSystemCode1, rfSocket12);
        break;

      case HC8300_2OFF: // Socket2 OFF
        Serial.println("Switching Couch Lamps off");
        rcSwitch.switchOff(rfSystemCode1, rfSocket12);
        break;

      case HC8300_3ON: // Socket3 ON
        Serial.println("Switching TV Lamp on");
        rcSwitch.switchOn(rfSystemCode1, rfSocket13);
        break;

      case HC8300_3OFF: // Socket3 OFF
        Serial.println("Switching TV Lamp off");
        rcSwitch.switchOff(rfSystemCode1, rfSocket13);
        break;

      case HC8300_4ON: // Socket4 ON
        Serial.println("Switching Lightstrip on");
        rcSwitch.switchOn(rfSystemCode1, rfSocket14);
        break;

      case HC8300_4OFF: // Socket4 OFF
        Serial.println("Switching Lightstrip off");
        rcSwitch.switchOff(rfSystemCode1, rfSocket14);
        break;

      case HC8300_5ON: // Socket5 ON
        Serial.println("Switching Socket5 on");
        rcSwitch.switchOn(rfSystemCode1, rfSocket15);
        break;

      case HC8300_5OFF: // Socket5 OFF
        Serial.println("Switching Socket5 off");
        rcSwitch.switchOff(rfSystemCode1, rfSocket15);
        break;

      case HC8300_6ON: // Socket6 ON
        Serial.println("Switching Socket6 on");
        rcSwitch.switchOn(rfSystemCode2, rfSocket21);
        break;

      case HC8300_6OFF: // Socket6 OFF
        Serial.println("Switching Socket6 off");
        rcSwitch.switchOff(rfSystemCode2, rfSocket21);
        break;

      case HC8300_9ON: // ALL ON
        rcSwitch.switchOn(rfSystemCode1, rfSocket11);
        rcSwitch.switchOn(rfSystemCode1, rfSocket12);
        rcSwitch.switchOn(rfSystemCode1, rfSocket13);
        rcSwitch.switchOn(rfSystemCode1, rfSocket14);
        rcSwitch.switchOn(rfSystemCode1, rfSocket15);
        rcSwitch.switchOn(rfSystemCode2, rfSocket21);
        break;

      case HC8300_9OFF: // ALL OFF
        Serial.println("Switching All OFF");
        rcSwitch.switchOff(rfSystemCode2, rfSocket21);
        rcSwitch.switchOff(rfSystemCode1, rfSocket15);
        rcSwitch.switchOff(rfSystemCode1, rfSocket14);
        rcSwitch.switchOff(rfSystemCode1, rfSocket13);
        rcSwitch.switchOff(rfSystemCode1, rfSocket12);
        rcSwitch.switchOff(rfSystemCode1, rfSocket11);
        break;

      case HC8300_B1Off: // ALL OFF with Delay
        delay(powerOffDelay);
        Serial.println("Switching All OFF");
        rcSwitch.switchOff(rfSystemCode2, rfSocket21);
        rcSwitch.switchOff(rfSystemCode1, rfSocket15);
        rcSwitch.switchOff(rfSystemCode1, rfSocket14);
        rcSwitch.switchOff(rfSystemCode1, rfSocket13);
        rcSwitch.switchOff(rfSystemCode1, rfSocket12);
        rcSwitch.switchOff(rfSystemCode1, rfSocket11);
        break;

      default:
        break;
    }

    irrecv.resume();
  }
}
