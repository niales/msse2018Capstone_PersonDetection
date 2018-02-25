// //For ease of proof there are two outputs, the digital signal we receive to com port
// //and the led on the photon indicating motion has been detected.
// int sensorPin = A0;
// int ledPin = D7;
// int motion = 0;
// int basicDelay = 300;
//
// void setup() {
//     pinMode(sensorPin, INPUT);
//     pinMode(ledPin, OUTPUT);
//     Serial.begin(115200);
// }
//
// void loop() {
//     //What did the port read?
//     int rval = analogRead(A0);
//     Serial.println(rval);
//
//     //do we have NEW motion detected?
//     if(rval > 2048 && !motion){
//         motion = 1;
//         Serial.println("HIGH");
//         digitalWrite(ledPin, HIGH);
//     }
//
//     //have we just detected a change to no motion?
//     if(rval < 2048 && motion){
//         motion = 0;
//         digitalWrite(ledPin, LOW);
//         Serial.println("LOW");
//     }
//
//     delay(basicDelay);
// }
