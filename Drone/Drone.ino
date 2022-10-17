/*

Reciever

*/
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <assert.h>

#include <Servo.h>

Servo ESC1; // Servo object is ESC/Motor handle : Pin 9
Servo ESC2; // Pin 6
Servo ESC3; // Pin 3
Servo ESC4; // Pin 5

const uint64_t pipeIn = 0xE8E8F0F0E1LL;

RF24 radio(8, 10); // RF24 is the transmitter/reciever (transciever), 8 & 10 arduino wires to reciever

struct StickValues {
    byte throttle; // left - up down
    byte yaw; // left - left right
    byte pitch; // right - up down
    byte roll; // right - left right
    byte button1;
    byte button2;
};

StickValues data;

void resetData() {
    data.throttle = 0;
    data.yaw = 127; // center/middle
    data.pitch = 127;
    data.roll = 127;
    data.button1 = 0;
    data.button2 = 0;
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

    ESC1.attach(9, 0, 0); // pin, min pulse width, max pulse width in microseconds
    ESC1.write(0); // null
    delay(2000); // sleep mls
    ESC2.attach(6, 0, 0); // TODO figure out what these 0's should be (anywhere from 700 to 10000 ?)
    ESC2.write(0);
    delay(2000);
    ESC3.attach(3, 0, 0);
    ESC3.write(0);
    delay(2000);
    ESC4.attach(5, 0, 0);
    ESC4.write(0);
    delay(2000);
}

void loop() {
    // ! Temp code
    if (true) {
        byte throttle = data.throttle * 180 / 127;
        Serial.print(throttle);
        Serial.print("\n");

        const int val = 180;

        ESC1.write(val); // 0 - 180, speed
        ESC2.write(val);
        ESC3.write(val);
        ESC4.write(val);

        return;
    }

    while (radio.available()) {
        radio.read(&data, sizeof(StickValues)); // get into data
    }

    byte throttle = data.throttle * 180 / 127;
    Serial.print(throttle);
    Serial.print("\n");

    const int val = 180;

    ESC1.write(val); // 0 - 180, speed
    ESC2.write(val);
    ESC3.write(val);
    ESC4.write(val);
}
