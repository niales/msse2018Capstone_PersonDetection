//
// bool MotionCheck(int motionPin, int ledPin){
//     //What did the port read?
//     int rval = analogRead(motionPin);
//     bool motion = false;
//
//     //do we have NEW motion detected?
//     if(rval > 2048){
//         motion = true;
//         digitalWrite(ledPin, HIGH);
//     }
//
//     //have we just detected a change to no motion?
//     if(rval < 2048){
//         motion = false;
//         Serial.println("LOW");
//     }
//     return motion;
// }
