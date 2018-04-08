//#include "support/distance_sensor.ino";
//#include "support/motion_sensor.cpp";

//Distance pins
//the trigger pin sends out an ultrasonic pulse
int trigPin = A0;
//the echopin receives the echo from the pulse transmitted by the trigger pin
int echoPin = A1;

//motion sensor pins
int motionPin = D4;
int ledPin = D3;

//For this file
int basicDelay = 500;
bool activeMotion = false;
char pirState = LOW; 

void setup() {
    //Generic setup
    Serial.begin(9600);

    //Distance sensor setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //motion sensor setup
    pinMode(motionPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop(){
    //Transmit
    long distance;
    distance = DistanceCheck(trigPin, echoPin);
    bool motion;
    motion = MotionCheck(motionPin, ledPin);
    
    //char val = digitalRead(motionPin);  // read input value
    //val = analogRead(inputPin);  // read input value
    //Serial.println(val);
    
    //=================================================================
    // The below code is a LED on/off code just by the status of the PIR sensor. We have to write our own logic to combine both the sensor data.
    if (motion) { 
        // check if the input is HIGH
        digitalWrite(ledPin, HIGH);  // turn LED ON
        if (pirState == LOW) {
            // we have just turned on
            Serial.println("Motion detected!");
            // We only want to print on the output change, not state
            pirState = HIGH;
        }
    } 
    else {
        digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH){
            // we have just turned of
            Serial.println("Motion ended!");
            // We only want to print on the output change, not state
            pirState = LOW;
        }
    }  
    //=================================================================
    Serial.println(distance);
    //Serial.println("Motion Detected:" + String(motion));

    delay(basicDelay);
}

long DistanceCheck(int trigPin, int echoPin){
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    //read in the echo
    duration = pulseIn(echoPin, HIGH);
    //calculate the distance based on the time it took to get the echo
    //https://www.tindie.com/products/upgradeindustries/hc-sr05--hy-srf05-precision-ultrasonic-sensor/
    //Distance (in cm) = (elapsed time * sound velocity (340 m/s)) / 100 / 2 ~=
    distance = (duration/2) * 0.0343;
    if (distance >= 400 || distance <=2) {
       Serial.println("Out of Range");
       distance = -1;
    }

    return (distance);
}

bool MotionCheck(int motionPin, int ledPin){
    //What did the port read?
    char rval = digitalRead(motionPin);  // read input value
    bool motion = false;

    //do we have NEW motion detected?
    if(rval == HIGH){
        motion = true;
    }

    //have we just detected a change to no motion?
    if(rval == LOW){
        motion = false;
    }
    return motion;
}
