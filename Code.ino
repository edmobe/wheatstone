// #include <LiquidCrystal.h>

// LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // LCD pins
int sensorVal = LOW;
int buttonVal = LOW; // push button status
int compVal = LOW; // comparator operational amplifier value

void setup()
{
  pinMode(8, INPUT_PULLUP); // push button
  
  pinMode(9, OUTPUT); // resistance sensor
  pinMode(10, OUTPUT); // light sensor
  pinMode(11, OUTPUT); // temperature sensor
  
  pinMode(12, INPUT); // operational Amplifier
  pinMode(7, OUTPUT); // LED
  pinMode(LED_BUILTIN, OUTPUT);

  useResSensor(); // default starting sensor
  
  // lcd.begin(16,2); // default values for the lcd

  Serial.begin(9600);
  Serial.println("Serial communiation started");
}

void loop()
{  
  // lcd.home(); // resets the cursor position
  
  // Push button
  buttonVal = digitalRead(8);
  delay(100);
  
  Serial.println(compVal, DEC);
  
  if (buttonVal == LOW) {
    if (sensorVal == 1) {
      useLightSensor();
    } else if (sensorVal == 2) {
      useTempSensor();
    } else {
      useResSensor();
    }
  	// lcd.clear();
  }
  
  // LCD and LED
  Serial.print("Sensor: ");
  compVal = digitalRead(12);
  // lcd.print("Sensor:");
  // lcd.setCursor(2,1);
  if (sensorVal == 1) {
  	// lcd.print("Resistencia");
    Serial.print("resistencia\n");
    
    // Vab is inversely proportional to the sensor resistance
    // In other words: the bigger the voltage, the smaller the resistance

    // Resistor: sensor parameter increase -> more resistance -> less voltage
    if (compVal == HIGH) { // high voltage -> less resistance -> sensor parameter decreases
      ledOff(); 
    } else {
      ledOn();    
    }
  } else if (sensorVal == 2) { // Light sensor: sensor parameter increase -> less resistance -> more voltage
  	Serial.print("luz\n");
  	// lcd.print("Luz");
    if (compVal == HIGH) { // high voltage -> less resistance -> sensor parameter increase
      ledOff();
    } else {
      ledOn();
    }
  } else { // Temperature sensor: sensor parameter increase -> less resistance -> more voltage
  	Serial.print("temperatura\n");
  	// lcd.print("Temperatura");
    if (compVal == HIGH) { // high voltage -> less resistance -> sensor parameter increase
      ledOn(); 
    } else{
      ledOff();
    }
  }

}

void useResSensor() {
  sensorVal = 1;
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void useLightSensor() {
  sensorVal = 2;
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void useTempSensor() {
  sensorVal = 3;
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(7, HIGH);
}

void ledOff() {
  digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(7, LOW);
}
