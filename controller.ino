/*

Transmitter

./android_cli compile -b andriod:? controller.ino

*/
#include <SPI.h>
#include <RF24.h>

RF24 myRadio (8, 10); // RF24 is the transmitter/reciever, 8 & 10 arduino wires to transmitter

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

struct package {
    int id=1;
    float temperature = 18.3;
    char  text[100] = "Text to be transmitted";
};

typedef struct package Package;
Package data;

void setup() {
    pinMode(7, OUTPUT);
    Serial.begin(9600);
    delay(1000);
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate( RF24_250KBPS ) ;
    myRadio.openWritingPipe(pipeOut);
    delay(1000);
}

void loop() {
    digitalWrite(7, HIGH);
    myRadio.write(&data, sizeof(data));

    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.temperature);
    Serial.println(data.text);
    data.id = data.id + 1;
    data.temperature = data.temperature+0.1;
    delay(1000);
}
