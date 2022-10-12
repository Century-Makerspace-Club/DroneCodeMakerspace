/*

Transmitter

*/
#include <SPI.h>
#include <RF24.h>

RF24 myRadio (8, 10); // RF24 is the transmitter/reciever, 8 & 10 arduino wires to transmitter

const uint64_t pipeOut = 0xE8E8F0F0E1LL; // common encoding for both ends

struct StickValues {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte sw1;
    byte sw2;
};

StickValues data;

void setup() {
    pinMode(7, OUTPUT); // pin, write
    Serial.begin(9600); // ignore
    delay(1000);
    myRadio.begin();
    myRadio.setChannel(115); // ignore
    myRadio.setPALevel(RF24_PA_MAX); // radio stuff
    myRadio.setDataRate(RF24_250KBPS); // same
    myRadio.openWritingPipe(pipeOut); // open in write mode
    delay(1000);
}

void loop() {
    digitalWrite(7, HIGH); // pin 7, high = on led
    myRadio.write(&data, sizeof(data)); // send to

    delay(1000);
}
