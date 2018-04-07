//************************************************************
//                Setup
//************************************************************
//Ultrasonic
byte trigPin = 12;    // Trigger is connected to this pin
byte echoPin = 11;    // Echo is connected to this pin
float echoTime;       // Variable to store echo pulse time  
float CMs;            // Variable to carry Cm values
float distance;       // Variable to hold calculated distance
long distance2;        // variable tp hold distance range for motor speed
 
unsigned long time;

//LED
int Ton = 13;// teensy LED
int ledPinR = 19;
int ledPinG = 20;

//For Case Statements
/*int scenario;
int DistSpeeds;
bool contS1 = true;
*/

//H-Bride & Motor
byte motorPin2 = 21;  //Teensy PWM pin for motor fwd (h bridge pin 2)
byte motorPin7 = 22;  //Teensy PWM pin for motor rev (h bridge pin 7)
byte enablePin = 23;  //Teensy PWM pin Enable on Hbridge pin 1
bool x = true;
int motorSpeed;


void setup() {
  distance = 0;
  //Set up for Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);   // Set pin to Output
  pinMode(echoPin, INPUT);    // Set pin to Intput
  digitalWrite(trigPin, LOW); // Start the tigger pin off as low
  Serial.begin(9600);         // Open the Serial Port
  
  //Motor
  pinMode(motorPin2, OUTPUT);   // Set pin to Output motor pin 2(h-bridge)
  pinMode(motorPin7, OUTPUT);   // Set pin to Output motor pin 7(h-bridge)
  pinMode(enablePin, OUTPUT);   // Set pin to Output
  pinMode(13, OUTPUT);       // Set pin to Output
  

  digitalWrite(enablePin, HIGH);// turn car on

  // LEDs
  pinMode(Ton, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);

}
//************************************************************
//                Calculate distance in cm
//************************************************************
float echoCM() {
  digitalWrite(trigPin, LOW);  // Make sure the pin starts off low
  delay(1);                    // Min between triggers is 50us so let's do 1000us
  digitalWrite(trigPin, HIGH); // Set trigger pin High for....
  delayMicroseconds(10);       // 10 microseconds.
  digitalWrite(trigPin, LOW);  // Set it low again

  echoTime = pulseIn(echoPin, HIGH);  //Collect the echo pulse
  CMs = echoTime / 58;                //Conversion in Data Sheet
  return CMs;                         // Return the calculated value
  
}

//***********************************************************
// motor speed based on distance
//***********************************************************
void Variable() {
   if (distance < 25);{
  distance2 = 25 - distance;  //collect distance
  motorSpeed = map(distance2, 10,25,150,0);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin7, LOW);
        analogWrite(enablePin, motorSpeed);     //write PWM to motor based on distance 
   }
  
if ( distance < 15){
      digitalWrite(ledPinR, HIGH);
      digitalWrite(Ton, LOW);
      digitalWrite(ledPinG, LOW);
}
else if (15 < distance < 25){
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, LOW);
      digitalWrite(Ton, HIGH);
}
if ( 25 < distance){
      digitalWrite(Ton, LOW);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinR, LOW);
}

}
void loop() {
  digitalWrite(Ton, HIGH);// turn teensy on
  distance = echoCM();    // Call non-void function to get the distance in cm
  Serial.println("Distance in Cms = " + (String)distance);    // print data
  Serial.println(" ");    // Print blank Space
  Variable();

}
