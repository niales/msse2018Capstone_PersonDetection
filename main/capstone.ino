//#include "support/distance_sensor.ino";
//#include "support/motion_sensor.cpp";


//Distance pins
//the trigger pin sends out an ultrasonic pulse
int trigPin = A0;
//the echopin receives the echo from the pulse transmitted by the trigger pin
int echoPin = A1;

//motion sensor pins
int motionPin = D4;
int ledPin = D7;

//For this file
int basicDelay = 150;
bool activeMotion = false;
char pirState = LOW;
int suspectTimeThreshold = 5000; // in MS
int suspectTimePassed = 0;

//App settings
int lowThreshDistance;
int highThreshDistance;

int distanceSleepDelay = 3000;
int currentDistanceSleepTime = 0;
bool isInDistanceSleep = false;

//Debug evaluator
int count = 0;

//state
// Empty = 0, Occupied = 1, SuspectedEmpty = 2
int roomState = 0;
bool calibrationMode;
int calibrationCount;

void setup() {
    //Generic setup
    Serial.begin(9600);

    //Distance sensor setup
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //motion sensor setup
    pinMode(motionPin, INPUT);
    pinMode(ledPin, OUTPUT);

    calibrationMode = true;
    calibrationCount = 0;
}

void loop(){
    //Transmit
    long distance;
    distance = DistanceCheck(trigPin, echoPin);
    bool motion;
    motion = MotionCheck(motionPin, ledPin);

    Serial.println("Low: " + String(lowThreshDistance) + " | High: " + String(highThreshDistance)+" | D: " + String(distance) + " M: " + String(motion) + " | RS: " + String(roomState) + " | time: " + millis());

    if(calibrationMode){
      calibrate(distance);

    }
    else{
      evaluate(distance, motion);

      if(roomState==1 || roomState==2){
        digitalWrite(ledPin, HIGH);
      }
      else{
        digitalWrite(ledPin, LOW);
      }
    }

    delay(basicDelay);
}

void calibrate(int distance){
    if(distance == -1){
        return;
    }
    if(count==0){
      lowThreshDistance = distance;
      highThreshDistance = distance;
    }
    if(lowThreshDistance> distance){
      lowThreshDistance = distance;
    }
    if(highThreshDistance< distance){
      highThreshDistance = distance;
    }

    count++;
    if(count >= 15){
      lowThreshDistance = lowThreshDistance - 10;
      highThreshDistance = highThreshDistance + 10;
      calibrationMode = false;
    }

}

void evaluate(long distance, bool motion){

  bool distanceTriggered = distanceTrip(distance);

  if(roomState == 0){ //currently empty
    if(distanceTriggered){
      roomState = 1;
      Serial.println("distance detected - changed state to 1");
    }
    if(motion){
      roomState = 1;
      Serial.println("motion detected - changed state to 1");
    }
  }
  else if(roomState == 1){ //Currently occupied
    if(distanceTriggered){
      roomState = 2;
      Serial.println("distance detected - changed state to 2");
    }
  }
  else if (roomState == 2 && motion){ //we suspect it's empty
    roomState = 1;
    Serial.println("motion detected - changed state to 1");
  }

  // if (motion) {
  //     // check if the input is HIGH
  //     digitalWrite(ledPin, HIGH);  // turn LED ON
  //     if (pirState == LOW) {
  //         // we have just turned on
  //         Serial.println("Motion detected!");
  //         // We only want to print on the output change, not state
  //         pirState = HIGH;
  //     }
  // }
  // else {
  //     digitalWrite(ledPin, LOW); // turn LED OFF
  //     if (pirState == HIGH){
  //         // we have just turned of
  //         Serial.println("Motion ended!");
  //         // We only want to print on the output change, not state
  //         pirState = LOW;
  //     }
  // }

}

bool distanceTrip(int distance){
  bool trigger = false;
  if(currentDistanceSleepTime > distanceSleepDelay){
    currentDistanceSleepTime = 0;
  }

  if(currentDistanceSleepTime == 0 && (distance < lowThreshDistance || distance > highThreshDistance)){
    trigger = true;
  }

  if(currentDistanceSleepTime != 0 || trigger){
    currentDistanceSleepTime = currentDistanceSleepTime + basicDelay;
  }

  return trigger;
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
    if (distance >= 500 || distance <=0) {
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
