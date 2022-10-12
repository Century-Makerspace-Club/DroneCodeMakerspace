/*

Reciever

*/
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <Servo.h>

Servo ESC1; // Servo object is ESC/Motor handle : Pin 9
Servo ESC2; // Pin 6
Servo ESC3; // Pin 3
Servo ESC4; // Pin 5

const uint64_t pipeIn = 0xE8E8F0F0E1LL;

RF24 radio(8, 10); // RF24 is the transmitter/reciever (transciever), 8 & 10 arduino wires to reciever

struct StickValues {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte sw1;
    byte sw2;
};

StickValues data;

void resetData() {
    data.throttle = 0;
    data.yaw = 127; // center/middle
    data.pitch = 127;
    data.roll = 127;
    data.sw1 = 0;
    data.sw2 = 0;
}

void setup() {

    // boiler plate
    {
        resetData();

        Serial.begin(9600); // ignore

        radio.begin(); // ignore
        radio.setDataRate(RF24_250KBPS); // both endpoints must have this set the same, 250 kp/s for both ends
        radio.setAutoAck(false);
    }

    // start reading
    radio.openReadingPipe(1, pipeIn); // 1 pin
    radio.startListening();

    ESC1.attach(9, 1000, 2000); // pin, min pulse width, max pulse width in microseconds
    ESC1.write(0); // null
    delay(2000); // sleep mls
    ESC2.attach(6);
    ESC2.write(0);
    delay(2000);
    ESC3.attach(3);
    ESC3.write(0);
    delay(2000);
    ESC4.attach(5);
    ESC4.write(0);
    delay(2000);
}

void loop() {
    while (radio.available()) {
        radio.read(&data, sizeof(StickValues)); // get into data
    }

    int val = data.throttle;
    Serial.print(val);
    Serial.print("\n");

    ESC1.write(val); // 0 - 180, speed
    ESC2.write(val);
    ESC3.write(val);
    ESC4.write(val);
}
