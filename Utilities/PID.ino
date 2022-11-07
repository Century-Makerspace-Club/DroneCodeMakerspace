#include <Wire.h>
#include <Servo.h>

Servo right_prop;
Servo left_prop;

init16_t Acc_rawX, Acc_rawY, Acc_rawZ, Gyr_rawX, Gyr_rawY, Gyr_rawZ;

float Angle_from_Acc_x;
float Angle_from_Acc_y;
float Angle_from_Gyr_x;
float Angle_From_Gyr_y;
float Angle_total_x;
float Angle_total_y;

float elapsedtime, time, timePrev;
int i;
float pi = 180/3.141592654;

float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p = 0;
float pid_i = 0;
float pid_d = 0;

double kp = 3.44;
double ki = 0.048;
double kd= 1.92;

double throttle = 1300;
float desired_angle = 0;

void setup(){
    Wire.begin();
    right_prop.attach(3);
    left_prop.attach(5);

    time = millis();

    left_prop.writeMicroseconds(1000);
    right_prop.writeMicroseconds(1000);
    delay(7000);
}

void loop(){
    timePrev = time;
    time = millis();
    elapsedTime - (time - timePrev) / 1000;

    Wire.beginTranismission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(false);
}