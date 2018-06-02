import processing.serial.*;
int res_x1 = 100;
int light_x1 = 350;
int temp_x1 = 600;
int buttonX = 200;
int buttonY = 50;
int globalY = 200;
float voltage = 0;
String sensorUsed = "r";

Serial port; //<>//

void setup() {
  size(900, 400);
  port = new Serial(this, "COM3", 9600);
  background(0);
}

void draw() {  
  if (voltage < 0) {
    background(0);
    fill(255, 0, 0);
    rect(450, 50, voltage * 100, 50); 
  } else {
    background(255, 255, 0);
    fill(0, 100, 0);
    rect(450, 50, voltage * 100, 50); 
  }
  
  displayButtons();
  String data = port.readStringUntil('\n');
  
  if (data != null) {
    voltage = float (data);
  }
  
}

void displayButtons() { 
  
  if (sensorUsed == "r") {
    fill(0, 100, 0);
    rect(res_x1, globalY, buttonX, buttonY);
    fill(255, 0, 0);
    rect(light_x1, globalY, buttonX, buttonY);
    rect(temp_x1, globalY, buttonX, buttonY);
  } else if (sensorUsed == "l") {
    fill(0, 100, 0);
    rect(light_x1, globalY, buttonX, buttonY);
    fill(255, 0, 0);
    rect(res_x1, globalY, buttonX, buttonY);
    rect(temp_x1, globalY, buttonX, buttonY);
  } else {
    fill(0, 100, 0);
    rect(temp_x1, globalY, buttonX, buttonY);
    fill(255, 0, 0);
    rect(res_x1, globalY, buttonX, buttonY);
    rect(light_x1, globalY, buttonX, buttonY);
  }
  
  fill(255);
  textSize(25);
  text("Resistor", res_x1 + 50, globalY + 35);
  text("Light", light_x1 + 70, globalY + 35);
  text("Temperature", temp_x1 + 25, globalY + 35);
}

void mousePressed() {
  if (mouseX > res_x1 && mouseX < res_x1 + buttonX && mouseY > globalY && mouseY < globalY + buttonY) {
    sensorUsed = "r";
    port.write('r');
  } else if (mouseX > light_x1 && mouseX < light_x1 + buttonX && mouseY > globalY && mouseY < globalY + buttonY) {
    sensorUsed = "l";
    port.write('l');
  } else if (mouseX > temp_x1 && mouseX < temp_x1 + buttonX && mouseY > globalY && mouseY < globalY + buttonY) {
    sensorUsed = "t";
    port.write('t');
  }
}
