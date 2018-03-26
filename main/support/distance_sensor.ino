//
//
// long DistanceCheck(int trigPin, int echoPin){
//   long duration, distance;
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   //read in the echo
//   duration = pulseIn(echoPin, HIGH);
//   //calculate the distance based on the time it took to get the echo
//   //https://www.tindie.com/products/upgradeindustries/hc-sr05--hy-srf05-precision-ultrasonic-sensor/
//   //Distance (in cm) = (elapsed time * sound velocity (340 m/s)) / 100 / 2 ~=
//   distance = (duration/2) / 25;
//
//   return (distance);
// }
