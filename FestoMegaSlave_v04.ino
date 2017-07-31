/*
  FESTO SORTING Station
  Middlesex University
  Course: Computer Science
  1st year Summer Project "Festo Sorting Station"
  Project leader: Michael Heeney 
  Stud. Rimma Chepik  
  07 2017
*/
/* Slave code for Arduino Mega(FESTO)  */

#include <Wire.h>
//Integers received from master Arduino(Uno) 
int startButtonState = 0;         // current state of the start  button
int lastStartButtonState = 0;     // previous state of the  start button
int set_pink = 0;
int set_metal = 0;
int last_set_pink = 0;
int last_set_metal = 0;

//Festo machine
int beltSensor = 22; // Sensor at beggining detects if something is on the belt
int pinkSensor = 24;  
int metalSensor = 23;    
int chuteSensor = 25; // Sensor detects if cylinder slipped off to chute
int pinkCount = 0;
int metalCount = 0;

//Configuration Digital OUT (24Vdc)
int belt = 36;    // Digital OUT  
int gate1 = 37;   // Digital OUT  
int gate2 = 38;   // Digital OUT  
int cylinder_lock = 39;    // Digital OUT  

//LIGHTS
int greenLight = 40;
int amberLight = 4;
int redLight = 5;


void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  /* FESTO */
  //Configuration Digital IN (24Vdc)
  //sensors
  pinMode(beltSensor, INPUT);     
  pinMode(metalSensor, INPUT);
  pinMode(pinkSensor, INPUT);

  //Configuration Digital OUT (24Vdc)
  pinMode(belt, OUTPUT);
  pinMode(gate1, OUTPUT);
  pinMode(gate2, OUTPUT);
  pinMode(cylinder_lock, OUTPUT);

  //lights
  pinMode(greenLight, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(amberLight, OUTPUT);
}


void loop() {  
  while (startButtonState == 1) {
    sortFesto(); //Do sorting when Start button is pressed (once) and information with sorting parameters is received from master Arduino
  }

  delay(1000);
}

/* Declaring functions*/

//FESTO Machine Sorting Function
void sortFesto() {
  if (digitalRead(beltSensor) == HIGH) {
    run_belt();
    reset_lights();
    digitalWrite(greenLight, HIGH);
    delay(3000);
    //Sort metal cylinder
    if ((digitalRead(metalSensor) == HIGH) and (digitalRead(pinkSensor) == HIGH) and (metalCount < set_metal))
    {
      Serial.println("Debug message 1: Sorting metal cylinder.");
      unlock_belt();
      run_belt();
      gate2_close();
      delay(1000);
      metalCount = metalCount + 1; // if metal sensor detects cylinder, increment metalCount by 1
      unlock_belt();
      run_belt();
      print_counters();
    }
    //Sort pink cylinder
    else if ((digitalRead(pinkSensor) == HIGH) and (digitalRead(metalSensor) == LOW) and (pinkCount < set_pink))
    {
      Serial.print("Debug message 2: Sorting pink cylinder.");
      unlock_belt();
      run_belt();
      gate1_close();
      delay(1000);
      pinkCount = pinkCount + 1; // if pink colour sensor detects pink cylinder, increment pinCount by 1
      unlock_belt();
      run_belt();
      print_counters();
    }
    else
    Serial.println("Debug message 3: cylinder is neither metal or pink or this type of cylinder sorting is done. ");
    print_counters();
    unlock_belt();
    run_belt();
    reset_lights();
    digitalWrite(redLight, HIGH);
  }


  else if (digitalRead(chuteSensor) == HIGH) {
    Serial.println("Debug message 4: Cylinder slipped off to chute. ");
    lock_belt();
    stop_belt();
    gate1_open();
    gate2_open();
    reset_lights();
    digitalWrite(amberLight, HIGH);
  }

  Serial.println("Debug message 5: Sorting process is running fluently, print counters. ");
  print_counters();
  digitalWrite(greenLight, HIGH);
  digitalWrite(amberLight, LOW);
  digitalWrite(redLight, LOW);
}


//Function to receive information from master Arduino Uno
void receiveEvent(int howMany) {

  int pink = Wire.read(); // read value of set_pink button received from master arduino
  int metal = Wire.read();  // read value of set_metal button received from master arduino 
  int start = Wire.read(); // read value of start button received from master arduino

  // Print start button State message to serial monitor
  Serial.println("StartButtonState: ");
  Serial.println(startButtonState);
  delay(100);
  
  startButtonState = start;
  set_pink = pink;
  set_metal = metal;


  lastStartButtonState = startButtonState;
  last_set_pink = set_pink;
  last_set_metal = set_metal;
}


void print_button_states() {
  Serial.print("Start buttonState: ");
  Serial.println(startButtonState);
  Serial.println(" ");

  Serial.print("Set Number of Pink cylinders: ");
  Serial.println(set_pink);
  Serial.println(" ");

  Serial.print("Set Number of Megal cylinders: ");
  Serial.println(set_metal);
  Serial.println(" ");
}

//FESTO machine components control functions

void unlock_belt() {
  digitalWrite(cylinder_lock, HIGH);
}
void lock_belt() {
  digitalWrite(cylinder_lock, LOW);
}
void run_belt() {
  digitalWrite(belt, HIGH);
}

void stop_belt() {
  digitalWrite(belt, LOW);
}

void gate1_open() {
  digitalWrite(gate1, LOW);
}
void gate1_close() {
  digitalWrite(gate1, HIGH);
}

void gate2_open() {
  digitalWrite(gate2, LOW);
}
void gate2_close() {
  digitalWrite(gate2, HIGH);
}

//Turn off lights
void reset_lights(){
  digitalWrite(greenLight, LOW);
  digitalWrite(amberLight, LOW);
  digitalWrite(redLight, LOW);
}

//Print counters values to Serial Monitor 
void print_counters() {
  Serial.print("metalCount: ");
  Serial.println(metalCount);
  Serial.println(" ");
  Serial.print("pinkCount: ");
  Serial.println(pinkCount);
  Serial.println(" ");
}


