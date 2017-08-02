/*Rimma Chepik                                                                                                                                            
Summer Project 
FESTO SORTING
Middlesex University
Tutor: Michael Heeney
07 2017
*/
//Arduino Uno master
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

/* Declaring integers*/
int start = 0;
int reset_button = 0;
int button4 = 3; // pin3
int button3 = 4; // pin4
int button2 = 5; // pin5
int button1 = 6; // pin5   reset
int pink_counter =  0;
int metal_counter = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  // Print a message to the LCD.
  //lcd.print("button 4");
  pinMode(button4, INPUT);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Rimma Chepik");
  lcd.setCursor(0,1 );
  lcd.print("Summer project");
  delay(2000);
  lcd.begin(16, 2);//reset ldc screen
  lcd.setCursor(0, 0);
  lcd.print("FESTO SORTING");
  lcd.setCursor(0, 1);
  lcd.print("   2017     ");
  delay(2000);
  lcd.begin(16, 2);//reset ldc screen
}

void loop() {
  setCounters(); 
}


/* Declaring functions*/

void sendToSlave() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(pink_counter);
  delay(1000);
  Wire.write(metal_counter);              // sends one byte
  delay(1000);
  Wire.write(start);
  delay(1000);
  Wire.endTransmission();    // stop transmitting
  delay(1000);
}

void setCounters() {
  int pink = digitalRead(button4);
  int metal = digitalRead(button3);
  int start_btn = digitalRead(button2);
  int reset_btn = digitalRead(button1);


  /*Set LCD Screen */  
  lcd.setCursor(0, 0);
  lcd.print("pink:");
  lcd.setCursor(0, 1);
  lcd.print("metal:");
  lcd.setCursor(7, 0);
  lcd.print(pink_counter);
  lcd.setCursor(7, 1);
  lcd.print(metal_counter);
  lcd.setCursor(9, 0);
  lcd.print("Start");
  lcd.setCursor(9, 1);
  lcd.print("Reset");


  if (pink == LOW) {
    pink_counter ++;
    lcd.setCursor(7, 0);
    lcd.print(pink_counter);
    delay(200);
  }


  if (metal == LOW) {
    metal_counter ++;
    lcd.setCursor(7, 1);
    lcd.print(metal_counter);
    delay(200);
  }

  if (start_btn == LOW) {
    start = 1;
    lcd.setCursor(15, 0);
    lcd.print("*");
    sendToSlave();// if OK button is pressed send to slave(Arduino Mega)
    delay(200);
  }
  if (start_btn == HIGH) {
    start = 0;
    lcd.setCursor(15, 0);
    lcd.print("  ");
    delay(20);
  }

  if (reset_btn == LOW) {
    reset_button = 1;
    lcd.setCursor(15, 1);
    lcd.print("*");
    delay(20);
    resetCounters(); //Call function reset counters
  }

  if (reset_btn == HIGH) {
    reset_button = 0;
    lcd.setCursor(15, 1);
    lcd.print("   ");
    delay(20);
  }

}
 
//reset function (button cancel)
void resetCounters () {
  //if button "cancel" pressed reset pink and metal counter
  if (reset_button == 1)
  {
    pink_counter = 0;
    metal_counter = 0;
    lcd.setCursor(7, 1);
    lcd.print(metal_counter);
    lcd.setCursor(7, 0);
    lcd.print(pink_counter);
    Serial.print("Reset");
  }
  else
    Serial.print("Reset button is not pressed");
}
