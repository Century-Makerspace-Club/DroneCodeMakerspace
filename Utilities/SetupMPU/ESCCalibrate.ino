#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN1 9
#define MOTOR_PIN2 10
#define MOTOR_PIN3 11
#define MOTOR_PIN4 12
int DELAY = 1000;

Servo motorBL;
Servo motorBR;
Servo motorFL;
Servo motorFR;

void setup(){
    Serial.begin(9600);
    delay(1500);
    Serial.prinln("ESC Start");

    motorBL.attach(MOTOR_PIN1);
    Serial.print("Now writing maximum output: (");
    Serial.print(MAX_SIGNAL);
    Serial.print("\n");
    motor.writeMicroseconds(MAX_SIGNAL);

    while (!Serial.available());
    Serial.read();

    Serial.println("\n");
    Serial.println("\n");
    Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
    motor.writeMicroseconds(MIN_SIGNAL);
    Serial.println("The ESC is calibrated");
    Serial.println("----");
    Serial.println("Now, type a values between 1000 and 2000 and press enter");
    Serial.println("and the motor will start rotating.");
    Serial.println("Send 1000 to stop the motor and 2000 for full throttle");

}

void loop(){
    if (Serial.available() > 0){
        int DELAY = Serial.parseInt();
        if (DELAY > 999){
            motor.writeMicroseconds(DELAY);
            float SPEED = (DELAY - 1000)/ 10;
            Serial.print("\n");
            Serial.println("Motor speed:");
            Serial.print("   ");
            Serial.print(SPEED);
            Serial.print("%");
        }
    }
}