// Motor A, TivaC and L298N connections
int enA = 26;   //ENABLE pin (PD3) for Motor A to provide PWM 
int in1 = 11;   //IN1 pin (PA2) for Motor A for direction
int in2 = 12;   //IN2 pin (PA3) for Motor A for direction
const int SW2 = 17;   //Pin number for Switch SW2
bool direction = true;  //Flag for clockwise or anti-clockwise direction
bool lastButtonState = HIGH;
void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  
  //Specify pinModes for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  //Initialize SW2 Switch as Input
  pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
}

void loop() {
  // Read the state of the pushbutton
  bool buttonState = digitalRead(SW2);

  // Check if the button state has changed
  if (buttonState != lastButtonState && buttonState == LOW) {
    // Debounce delay
    delay(50);
    // Confirm button press
    if (digitalRead(SW2) == LOW) {
      // Toggle direction flag
      direction = !direction;
    }
    // Additional delay to avoid multiple toggles
    delay(500);
  }

  // Update the last button state
  lastButtonState = buttonState;

  // Set motor direction
  if (direction) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 70);  // Speed for clockwise
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 255);  // Speed for anti-clockwise
  }

  // Optional: Short delay for stability
  delay(100);}

void changeState() {
  direction = !direction;}

void tenP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 10%
//    for (int i=0; i<50; i++){
//      digitalWrite(enA, HIGH);
//      delayMicroseconds(2000); // High for 2ms, Duty Cycle of 10%
//      digitalWrite(enA, LOW);
//      delayMicroseconds(18000); // Off for remaining  18ms
//    analogWrite(enA, 64);
//    delay(100);
    
//    analogWrite(enA, 128);
//    delay(500);
//    analogWrite(enA, 192);
//    delay(500);
//    analogWrite(enA, 255);
//    delay(500);
//  if (SW2==LOW) {
//    state1();}
//  else {state2();}
}


/*
void changeDirection(){
  //To be used for task03 only
    if(digitalRead(SW2) == 0){
      //toggle between State 1 and State 2
    }
    delay(1000);  
}*/
