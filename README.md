# xaar128

## Background

The Xaar 128 is a piezoelectric inkjet printhead used in large format vinyl sign-making. It *might* be useful in 3d printing, conductive ink, or masking applications. This guide is intended to help others experiment with the Xaar 128 and different materials in hopes that they’ll share their results.

Why piezo? TLDR: Most inkjet printheads are “bubble jet”: They work by superheating a fraction of the ink in a chamber, turning it into gas, which expands to force the remainder of the ink out of a nozzle. Superheating limits the range of materials that can be used in these printheads. Piezoelectric printheads are less common, and since they use a mechanical operation to force fluid out of a nozzle, they don’t have to modify the state of the fluid to operate, and can work with a broader range of materials.

## Known Limitations

Xaar approved inks have viscosity around 0-12cps. Higher viscosity fluids are unlikely to work with this printhead.

## Parts List
- Xaar XJ128 Blue
- Alternative 1: “GLUX” 30 > 21 pin adapter (2)
  - 21 pin 1.0mm FFC
  - 1.0mm 30 pin FFC connector (bottom leads) (Mouser) (Amazon)
  - Proto-Advantage FFC to breadboard adapter
  - Alternative (Adafruit)
- Sunfounder 2 Channel 5V Relay Board (not rated for 36V)
- 2 x 36V DC power supplies
- Arduino Uno / Mega
- Breadboard, hookup wire, etc.

## Xaar 128 Operations Guide
Not available from the Xaar website (please add more sources):
- [Unofficial Source](http://d1.amobbs.com/bbs_upload782111/files_36/ourdev_619324HXZTX0.pdf)

## References

- http://ytec3d.com/forum/viewtopic.php?t=47
- https://www.youtube.com/watch?v=dnBx0aCWNms

## Adapters
### “GLUX” 30 > 21 Pin Adapter

Dillinger is currently extended with the following plugins. Instructions on how to use them in your own application are linked below.

| Adapter | Signal | Xaar 128 |
| ------ | ------ | ----- |
| 1 | VPPH | 3 |
| 2 | VPPH | 3 |
| 3 | VPPL | 4 |
| 4 | GNDL | 5 |
| 5 | GNDH | 2 |
| 6 | GNDH | 2 |
| 7 | nRESET | 7 |
| 8 | nSS2 | 1 |
| 9 | GND | 16 |
| 10 | MOSI* | 8 |
| 11 | VDD | 17 |
| 12 | VDD | 17
| 13 | SCK | 19 |
| 14 | GND | 16 |
| 15 | nSS1 | 20 |
| 16 | GND | 16 |
| 17 | READY | 24 |
| 18 | PHO | 25 |
| 19 | nFIRE | 26 |
| 20 | MISO | 27 |
| 21 | CLK | 28 |
| - | nFAULT | |

## Driving the Xaar 128
- 1mhz CLK to drive signal logic in printhead ICs.
- Data is loaded via SPI interface.
- SCK for the SPI interface is independent of CLK above.
- 2 shift registers, each hold 64 bits of data corresponding to 128 nozzles.
- State machine for one print cycle:
  - READY (output from Xaar 128) is HIGH (okay to load data)
  - Enable nSS2, Clock in 64 bits.
  - Disable nSS2.
  - Enable nSS1, Clock in 64 bits.
  - Disable nSS1.
  - nFIRE (active LOW) input to Xaar 128 indicates that data is loaded and ready to fire.
  - READY goes LOW when firing nozzles.
  - READY returns to HIGH

![](https://raw.githubusercontent.com/gkyle/xaar128/master/trace.png)
Trace from Saleae Logic.

See Operations Guide pg. 33.
