/*
 * Receiver
 */

//TODO: do logic with yaw and pitch and roll, IMU data

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <Servo.h>

Servo ESC1;     // create servo object to control the ESC
Servo ESC2;
Servo ESC3;
Servo ESC4;
const uint64_t pipeIn = 0xE8E8F0F0E1LL;

RF24 radio(8,10);

struct MyValues{
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte sw1; 
  byte sw2;
};

MyValues data;

void resetData(){
  data.throttle = 0;
  data.yaw = 127; //middle value 
  data.pitch = 127;
  data.roll = 127;
  data.sw1 = 0;
  data.sw2 = 0;
}

void setup(){
  resetData();
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS); // Both endpoints must have this set the same
  radio.setAutoAck(false);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

  ESC1.attach(9,1000,1500); //2000 max maybe
  ESC1.write(0);
  delay(2000); 
  ESC2.attach(6,700,1200);
  ESC2.write(0);
  delay(2000);
  ESC3.attach(3,700,1200);
  ESC3.write(0);
  delay(2000);
  ESC4.attach(5,700,1200);
  ESC4.write(0);
  delay(2000);
}

void loop() {
  while (radio.available()){
    radio.read(&data, sizeof(MyValues));
  }
  /* old 
  ESC1.write(val);
  ESC2.write(val);
  ESC3.write(val);
  ESC4.write(val);*/
}
