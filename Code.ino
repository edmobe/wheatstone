char sensorVal = 'r'; // determines which sensor is being used

int v1; // voltage 1
int v2; // voltage 2
float voltage; // voltage difference for the resistor comparisson

void setup()
{
  pinMode(9, OUTPUT); // resistance sensor
  pinMode(10, OUTPUT); // light sensor
  pinMode(11, OUTPUT); // temperature sensor
  
  pinMode(LED_BUILTIN, OUTPUT);

  useResSensor(); // default starting sensor
  
  Serial.begin(9600);
}

void loop()
{  

  if (Serial.available() > 0) {
      sensorVal = Serial.read();
      if (sensorVal == 'r') {
        useResSensor();  
      } else if (sensorVal == 'l') {
        useLightSensor();
      } else if (sensorVal == 't'){
        useTempSensor();
      }
  }
  
  // Compare voltages
  v1 = analogRead(A0);
  v2 = analogRead(A1);
  voltage = (v1 - v2) * (5.0 / 1023.0);
  
  // Serial.print("Sensor: ");
  if (sensorVal == 'r') {
    // Vab is inversely proportional to the sensor resistance
    // In other words: the bigger the voltage, the smaller the resistance

    // Resistor: sensor parameter increase -> more resistance -> less voltage
    if (voltage > 0) { // high voltage -> less resistance -> sensor parameter decreases
      ledOff(); 
    } else {
      ledOn();    
    }
  } else if (sensorVal == 'l') { // Light sensor: sensor parameter increase -> less resistance -> more voltage
    if (voltage > 0) { // high voltage -> less resistance -> sensor parameter increase
      ledOff();
    } else {
      ledOn();
    }
  } else { // Temperature sensor: sensor parameter increase -> less resistance -> more voltage
    if (voltage > 0) { // high voltage -> less resistance -> sensor parameter increase
      ledOn(); 
    } else{
      ledOff();
    }
  }

  Serial.println(voltage);
  delay(100);

}

void useResSensor() {
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void useLightSensor() {
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void useTempSensor() {
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
