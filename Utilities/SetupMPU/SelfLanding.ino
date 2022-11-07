//using ulstrasonic sensor for height
//using feedforward to correct uncertainity
#define echoPin 2
#define trigPin 3

long duration;
int distance;

void setup(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void cmToFt(float cm){
    float feet = cm * 0.0328084;
}

void loop(){
    digitalWrite(trigPin, LOW);
    delay(2);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, HIGH);
    distance = duration * 0.034/2;
    Serial.print("distance");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print("distance");
    Serial.print(cmToFt(distance));
    Serial.print("feet");
}

//as height gets lower by amount above threshold
//make decent lower
//implement self correcting
//open cv for bullseye recognition

