//#include "support/distance_sensor.ino";
//#include "support/motion_sensor.cpp";

//Distance pins
//the trigger pin sends out an ultrasonic pulse
int trigPin = A0;
//the echopin receives the echo from the pulse transmitted by the trigger pin
int echoPin = A1;

//motion sensor pins
int motionPin = A4;
int ledPin = D7;

//For this file
int basicDelay = 300;
bool activeMotion = false;

void setup() {
    //Generic setup
    Serial.begin(115200);

    //Distance sensor setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //motion sensor setup
    pinMode(motionPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop(){
    //Transmit
    long distance = DistanceCheck(trigPin, echoPin);
    bool motion = MotionCheck(motionPin, ledPin);

    Serial.println(distance);
    Serial.println("Motion Detected:" + String(motion));

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
    distance = (duration/2) / 25;

    return (distance);
  }


  bool MotionCheck(int motionPin, int ledPin){
      //What did the port read?
      int rval = analogRead(motionPin);
      bool motion = false;

      //do we have NEW motion detected?
      if(rval > 2048){
          motion = true;
          digitalWrite(ledPin, HIGH);
      }

      //have we just detected a change to no motion?
      if(rval < 2048){
          motion = false;
          digitalWrite(ledPin, LOW);
      }
      return motion;
  }
