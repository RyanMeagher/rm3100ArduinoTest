#include <Arduino.h>
#include <Wire.h>

#include "../lib/QRM3100/src/QRM3100.h"


QRM3100 mag;

void setup() {
    // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(9600);

    // Check REVID register first, should return 0x22.
    if (mag.readRegister(0x36) != 0x22)
    {
        Serial.println("REVID NOT CORRECT!");
        Serial.print("REVID: ");
        Serial.println(mag.readRegister(0x36), HEX);
    }
    else
    {
        Serial.println("RM3100 Detected Properly");
        Serial.print("REVID: ");
        Serial.println(mag.readRegister(0x36), HEX);
    }
}

void loop()
{

    // poll the RM3100 for a single measurement
    mag.writeRegister(0x00, 0x70);

    delay(500); // delay to help monitor DRDY pin on eval board

    // Check if DRDY went high and wait unit high before reading results
    while ((mag.readRegister(0x34) & 0x80) != 0x80) {}

    // Read results, this will cause DRDY to go low
    uint8_t mx2 = mag.readRegister(0x24);
    uint8_t mx1 = mag.readRegister(0x25);
    uint8_t mx0 = mag.readRegister(0x26);
    uint8_t my2 = mag.readRegister(0x27);
    uint8_t my1 = mag.readRegister(0x28);
    uint8_t my0 = mag.readRegister(0x29);
    uint8_t mz2 = mag.readRegister(0x2A);
    uint8_t mz1 = mag.readRegister(0x2B);
    uint8_t mz0 = mag.readRegister(0x2C);


    int32_t x = ((mx2 << 16) | (mx1 << 8) | mx0 );
    int32_t y = ((my2 << 16) | (my1 << 8) | my0 );
    int32_t z = ((mz2 << 16) | (mz1 << 8) | mz0 );

    Serial.print("M:  ");
    Serial.print(x);
    Serial.print("   ");
    Serial.print(y);
    Serial.print("   ");
    Serial.println(z);



    delay(500);  // delay to help monitor DRDY pin on eval board

}
