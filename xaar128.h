#ifndef XAAR128_H_
#define XAAR128_H_

#ifdef ARDUINO_AVR_MEGA2560
  // MEGA SPI: SCK: 52, MISO: 50, MOSI: 51

  // Supply / Supply Ctrl pins
  #define nSS1          10 // Chip select for XARR 128 1st IC
  #define nSS2           7 // Chip select for XARR 128 2nd IC
  #define relayVHCH     49
  #define relayVHCL     48
  
  #define nCLK          11
  #define xVDD          23

#elif AVR_UNO
  // UNO SPI: SCK: 13, MISO: 12, MOSI: 11
  
  // Supply / Supply Ctrl pins
  #define nSS1          10 // Chip select for XARR 128 1st IC
  #define nSS2           7 // Chip select for XARR 128 2nd IC
  #define relayVHCH     19
  #define relayVHCL     18
  
  #define nCLK           9
  #define xVDD           4

#endif

// Output pins
//int PHO = 5;
#define nRESET           8
#define nFIRE            5

// Input pins
#define READY            2 // This will be an interrupt pin.

class Xaar128 {

public:
  int readyState = 0;

  Xaar128();
  void init();
  void powerUp();
  void powerDown();
  void loadBuffer64(byte *val);
  void loadData(int pending);
  void go(int pending);
  bool fire();
};

#endif
