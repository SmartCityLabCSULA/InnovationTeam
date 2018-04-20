#include <Printers.h>
#include <XBee.h>

//This version adds Xbee code 
//************************************************************
//                Setup
//************************************************************
//Libraries included
#include <Printers.h>
#include <XBee.h>

//Xbee Set up
XBee xbee1 = XBee();
// two byts are allocated to hold 10-bit analog reading
uint8_t payload[] = { 0, 0, 0, 0}; // data that will be transmitted (Car Id, Scenario, velocity, distance)
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4106a272);
Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));
XBeeResponse response = XBeeResponse();
// reusable responses we will be handeling
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

//********** DEFINING VARIABLES ******************************
//For Case Statements AND 
int scenario;
bool contS1 = true;
int pinS1 = 2;
int j;
int CarIdReceived; // used for the filter
int CarId = 1;


//Ultrasonic
byte trigPin = 12;    // Trigger is connected to this pin
byte echoPin = 11;    // Echo is connected to this pin
float echoTime;       // Variable to store echo pulse time  
float CMs;            // Variable to carry Cm values
const double SpeedSound2 = 0.0343 / 2; //used to get cm/s
float distance;       // Variable to hold calculated distance
long distance2;        // variable to hold distance range for motor speed

//H-Bride & Motor
byte motorPin2 = 21;  //Teensy PWM pin for motor fwd (h bridge pin 2)
byte motorPin7 = 22;  //Teensy PWM pin for motor rev (h bridge pin 7)
byte enablePin = 23;  //Teensy PWM pin Enable on Hbridge pin 1
int motorSpeed;

//LED
int Ton = 13;// teensy LED
int ledPinR = 19;
int ledPinG = 20;


void setup() {
  //Distance is defined to zero
  distance = 0;
  
  //Set up for Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);   // Set pin to Output
  pinMode(echoPin, INPUT);    // Set pin to Intput
  digitalWrite(trigPin, LOW); // Start the tigger pin off as low
  
  //Motor and H-Bridge
  pinMode(motorPin2, OUTPUT);   // Set pin to Output motor pin 2(h-bridge)
  pinMode(motorPin7, OUTPUT);   // Set pin to Output motor pin 7(h-bridge)
  pinMode(enablePin, OUTPUT);   // Set pin to Output
  pinMode(13, OUTPUT);       // Set pin to Output

  digitalWrite(enablePin, HIGH);// turn car on

  // LEDs
  pinMode(Ton, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);

  //Set up for serial frequency (baude rate)
  Serial.begin(115200);         // Open the Serial Port
  Serial1.begin(115200);        // used for XBee
  xbee1.setSerial(Serial1);   // Serial is created for XBees use

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

  echoTime = pulseIn(echoPin, HIGH);  //Collect the echo pulse DURATION
  CMs = echoTime * SpeedSound2;                //Conversion in Data Sheet
  return CMs;                         // Return the calculated value
 
}
//***********************************************************
// LED Distance indicator
//***********************************************************
void LED(){
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
//***********************************************************
// Breaking function
//***********************************************************
void breaking(){
  if (distance < 20){
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin7, HIGH);
        analogWrite(enablePin, 150);
        payload[2] = 150;
        ReceiveData();
        while (distance < 17){
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin7, LOW);
        break;
        payload[2] = 0;
        payload[3] = distance;
        ReceiveData();  
          }
          
    }
    ReceiveData();
  }

//***********************************************************
// motor speed based on distance
//***********************************************************
//Void Variable will map the speed of the motor through PWM proportional to the distance 
void Variable() {
  while(contS1 == true){
  if (distance > 45){
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin7, LOW);
        analogWrite(enablePin, 100);
        payload[2] = 100;
        ReceiveData();
   
}else if(distance < 45);{
  distance2 = 45 - distance;  //collect distance
  motorSpeed = map(distance2, 15,275,90,0);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin7, LOW);
        analogWrite(enablePin, motorSpeed);     //write PWM to motor based on distance 
        payload[2] = motorSpeed;
        //payload[3] = distance;
        ReceiveData();
   }
breaking();
    ReceiveData();
  }
      delay (10);
}
//************************************************************
//                XBee Recieve Data
//************************************************************
void ReceiveData() {
  xbee1.send(tx);
  xbee1.readPacket(10);
  if (xbee1.getResponse().isAvailable()) {
    if (xbee1.getResponse().getApiId() == RX_16_RESPONSE) {
      xbee1.getResponse().getRx16Response(rx16);
      CarIdReceived = rx16.getData(1);
      //scenario = rx16.getData(0);
    }
//    if (scenario == 0) {
//      contS1 = false;
//    }
  }
  if (CarIdReceived == CarId) {
    for (j = 0; j < 5; j++) {
      xbee1.send(tx);
    }
  }
}
//************************************************************
//                Main Loop
//************************************************************
void loop() {
  digitalWrite(Ton, HIGH);// turn teensy on
  distance = echoCM();    // Call non-void function to get the distance in cm
  payload[3] = distance;
  payload[0] = CarId;
  payload[1] = 1;
  LED();                  //Calls LED function
  Variable();
/*  switch (scenario){
  case 1:
    Serial.println("Varying");
    Variable();   //calls Varying speed function
    delay(1000);

    break;
    default:
    break;
  }*/
//code that is commented out between /**/ is for displaying distance and PWM (motorSpeed)
  Serial.println("Distance in Cms = " + (String)distance);    // print data
  Serial.println(" ");    // Print blank Space
  Serial.println("motorSpeed = " + (String)motorSpeed);
  Serial.println(" ");

  ReceiveData();          // Calls Receive data function 
  
}
