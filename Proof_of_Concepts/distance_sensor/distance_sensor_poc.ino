//the trigger pin sends out an ultrasonic pulse
int trigPin = A0;
//the echopin receives the echo from the pulse transmitted by the trigger pin
int echoPin = A1;

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop(){
    //Transmit
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
    distance = (duration/2) / 34;


    Serial.println(distance);

    delay(300);
}
