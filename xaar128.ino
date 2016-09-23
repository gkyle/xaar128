#include "Arduino.h"
//#include "carriage.h"
#include "xaar128.h"

int PENDING = 200;
int CYCLES = 1;

Xaar128 xaar128;
 
void setup (void) {
  Serial.begin(115200);

  //Carriage carriage;
  xaar128.init();

  // Set up a 1mHZ square wave for Xaar state machine CLK.
  // http://forum.arduino.cc/index.php?topic=103370.0
  TCCR1A = _BV(COM1A0);              // toggle OC1A on compare match
  OCR1A = 7;                         // top value for counter
  // UNO //TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC mode, prescaler clock/1
  TCCR1B = _BV(WGM12) | _BV(CS10);   // CTC mode, prescaler clock/1

  Serial.print("Begin: ");
  Serial.println(PENDING);

  float steps = 0.0;
  float fails = 0.0;

  //carriage.init(LOW);
  xaar128.powerUp();
  delay(1000);

  for (int c=0; c<CYCLES; c++) {
    for (int p=0; p < PENDING; p++) {
      xaar128.loadData(p);
      delayMicroseconds(1);
      if (!xaar128.fire()) fails++;
      //carriage.step();
      steps++;
    }
    /*
    carriage.changeDir();
    for (int p=0; p < PENDING; p++) {
      carriage.step();
    }
    carriage.changeDir();
    */
  }

  delay(100);
  xaar128.powerDown();
  //carriage.shutdown();  
  printSummary(fails, steps);
}

void printSummary(float fails, float steps) {
  Serial.println("Done.");
  float f = fails / steps;
  Serial.print("Steps: ");
  Serial.print(steps);
  Serial.print("    Fails: ");
  Serial.print(fails);
  Serial.print("    Failure Rate: ");
  Serial.println(f, 4);
}

void loop (void) {} // end of loop
