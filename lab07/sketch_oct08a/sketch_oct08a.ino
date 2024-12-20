const int analogInPin = 29;  // Connect Output from LDR at PE3/A0
const int analogOutPin = 30; // Analog Output to Built-in RED LED at PF1

int ADCValue = 0;      // ADC Value read from LDR in range 0-4095
int brightness = 0;    // ADC Output to Built-in LED to control it's brightness
float voltage = 0;     //Voltage to be calculated basedd on ADC value

void setup() {
  
  Serial.begin(115200);

  
  pinMode(analogInPin, OUTPUT);
  pinMode(analogOutPin, OUTPUT);
  
}

void loop() {
  //Read the analog value using analogRead(pin) and store in variable ADCValue:
  ADCValue = analogRead(analogInPin);
  //        
    
  brightness = map(ADCValue, 0, 4095, 0, 255);
  
  
  analogWrite(analogOutPin, brightness);
  

  voltage = ADCValue * (3.3 / 4095);
  
  
  Serial.print("ADC Input Value = " );                   
  Serial.print(ADCValue);      
  Serial.print("\t Brightness = ");      
  Serial.println(brightness);
  Serial.print("\t Voltage = ");      
  Serial.println(voltage);  

  delay(100);                     
}
