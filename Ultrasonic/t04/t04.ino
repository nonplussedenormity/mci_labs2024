// Ultrasonic Pins Definition, here we specify pin usage for our tivaC Board
const int echo = 9;
const int Trig = 10;  // Pin connections for HC-SR04
const int LED1 = 11;            // Specify Pin for LED1
const int LED2 = 12;            // Specify Pin for LED2
const int LED3 = 13;            // Specify Pin for LED3
// Time Update Variables
long duration, cm;                          // To measure pulse width and distance in cm
unsigned long LastUpdateMillisecs = 0;
unsigned long CurrentMillisecs = 0;
const int blinkInterval = 500;
bool systemOn = false; 
// Pin Definitions for Switches
const int sw1 = 31;  // PF4
const int sw2 = 17;  // PF0
// Initializing Pins Function
void setup() {
  Serial.begin(115200);     // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig, OUTPUT);    // Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
  pinMode(echo, INPUT);     // Echo is input since it will detect the reflected wave from HC-SR04
  pinMode(LED1, OUTPUT);    // Pin for LED1 should output HIGH(on) or LOW(off)
  pinMode(LED2, OUTPUT);    // Pin for LED2 should output HIGH(on) or LOW(off)
  pinMode(LED3, OUTPUT);    // Pin for LED3 should output HIGH(on) or LOW(off)
  pinMode(sw1, INPUT_PULLUP); // SW1
  pinMode(sw2, INPUT_PULLUP); // SW2
}
// Main Loop that will keep on running
void loop() {
  if (digitalRead(sw1) == LOW) {
    // Switch ON the system
    systemOn = true;
    Serial.print("System Activated");Serial.print("\n");
  }
  if (digitalRead(sw2) == LOW) {
    // Switch OFF the system
    systemOn = false;
    Serial.print("System Deactivated");Serial.print("\n");
  }
  if (systemOn) {
    Update_Ultra_Sonic(); // This function operates HC-SR04
    delay(100);           // Delay between prints on Serial Monitor
  } else {
    // Turn off all LEDs when the system is OFF
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
}
// Will update ultrasonic sensors through Serial port
void Update_Ultra_Sonic() {
  const int Readings = 10;
  long TotalDistance = 0;
  long AvgDist = 0;
  for (int i = 0;i < Readings; i++) {
    
    // Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(echo, HIGH); 
  cm = microsecondsToCentimeters(duration);
  TotalDistance += cm;
  delay(100);}
  AvgDist = TotalDistance/Readings;
  Serial.print("Averaged Distance=");
  Serial.print("\t");
  Serial.print(AvgDist);
  Serial.print(" cm\n");
   // Convert the time into a distance
  if (AvgDist > 100) {
    // Blink all LEDs if no object in sight
    CurrentMillisecs = millis();
    if (CurrentMillisecs - LastUpdateMillisecs >= blinkInterval) {
      LastUpdateMillisecs = CurrentMillisecs;
      digitalWrite(LED1, !digitalRead(LED1));
      digitalWrite(LED2, !digitalRead(LED2));
      digitalWrite(LED3, !digitalRead(LED3));
      Serial.print("Average Distance=");
      Serial.print("\t");
      Serial.print(AvgDist);
      Serial.print("\n");
      //Serial.print("LED1 ");
      //Serial.print(digitalRead(LED1) ? "on" : "off");
      //Serial.print("\nLED2 ");
      //Serial.print(digitalRead(LED2) ? "on" : "off");
      //Serial.print("\nLED3 ");
      //Serial.print(digitalRead(LED3) ? "on" : "off");
      //Serial.print("\n");
    }
  } else if (AvgDist > 15 && AvgDist <= 30) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    //Serial.print("LED1 on\nLED2 off\nLED3 off\n");
    //Serial.print("Distance=");
    //Serial.print("\t");
    //Serial.print(cm);
    //Serial.print("\n");
  } else if (AvgDist > 5 && AvgDist <= 15) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    //Serial.print("LED1 on\nLED2 on\nLED3 off\n");
    //Serial.print("Distance=");
    //Serial.print("\t");
    //Serial.print(cm);
    //Serial.print("\n");
  } else if (AvgDist >= 0 && AvgDist <= 5) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    //Serial.print("LED1 on\nLED2 on\nLED3 on\n");
    //Serial.print("Distance=");
    //Serial.print("\t");
    //Serial.print(cm);
    //Serial.print("\n");
  } else {
    Serial.print("LED1 off\nLED2 off\nLED3 off\n");
    //Serial.print("Distance=");
    //Serial.print("\t");
    //Serial.print(cm);
    //Serial.print("\n");
  }
  // Sending through serial port to print on Monitor
  Serial.print("Average Distance=");
  Serial.print("\t");
  Serial.print(AvgDist);
  Serial.print("\n");
}
// Conversion of microsecond to centimeter
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // Convert speed of sound from m/s to cm/us
  // Use the formula: distance(cm) = speed(cm/us) * time(us)
  long distance = 0.0343 * microseconds;
  // We take half of the distance travelled since it's a reflected wave
  return distance / 2;
}
