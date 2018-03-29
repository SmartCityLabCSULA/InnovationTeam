// Ultrasonic Sensor
const int trigPin1 = 14;
const int echoPin1 = 15;
long duration1;
float distance1;
unsigned long time;

// Ultrasonic Sensor2
const int trigPin2 = 16;
const int echoPin2 = 17;
long duration2;
float distance2;
//unsigned long time;
int led=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
    // Ultrasonic Sensor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
    // Ultrasonic Sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = (duration1 * 0.034) / 2;

      // Ultrasonic Sensor2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = (duration2 * 0.034) / 2;
  
  delay(150);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance Ultra 1: ");
  //Serial.print('\t');
  Serial.print(distance1);
  Serial.print('\n');
  Serial.print("Distance Ultra 2: ");
  Serial.print('\t');
  Serial.print(distance2);
  Serial.print('\n');
  
//delay(1000);
}
