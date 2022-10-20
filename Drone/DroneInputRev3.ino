/* 
 *  Transmitter
 */

#include <nRF24L01.h>
#include <pritnf.h>
#include <RF24.h>
#include <RF24_config.h>

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

int VRx1 = A0; //variable resistance 
int VRx2 = A2;
int VRy1 = A1;
int VRy2 = A3;

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
  Serial.begin(9600);
  pinMode(VRx1, INPUT);
  pinMode(VRx2, INPUT);
  pinMode(VRy1, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(7, OUTPUT);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS); //transmitter, receiver same
  radio.openWritingPipe(pipeOut);
  resetData();
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}

void loop() {
  digitalWrite(7, HIGH); // LED turn on 
  data.throttle = mapJoystickValues(analogRead(VRy1), 13, 0 , 1015, true);
  data.yaw = mapJoystickValues(analogRead(VRx1), 1, 505, 1020, true);
  data.pitch = mapJoystickValues(analogRead(VRy2), 12, 544, 1021, true);
  data.roll = mapJoystickValues(analogRead(VRx2),34, 522, 1020, true);
  data.sw1 = digitalRead(SW1);
  data.sw2 = digitalRead(SW2);
  
  int throttle = data.throttle;
  int yaw = data.yaw;
  int pitch = data.pitch;
  int roll = data.roll;
  byte b1 = data.sw1;
  byte b2 = data.sw2;
  
  Serial.print("throttle ")
  Serial.print(throttle);
  Serial.print("\n");
  Serial.print("yaw ");
  Serial.print(yaw);
  Serial.print("\n");
  Serial.print("pitch ")
  Serial.print(pitch);
  Serial.print("\n");
  Serial.print("roll ")
  Serial.print(roll);
  Serial.print("\n");
  if (b1 == 1){
    Serial.print("Button 1 HIGH");
  }
  if (b2 == 1){
    Serial.print("Button 2 HIGH");
  }

  /* old 
  ESC1.write(val);
  ESC2.write(val);
  ESC3.write(val);
  ESC4.write(val);*/

  radio.write(&data, sizeof(data)):
}
