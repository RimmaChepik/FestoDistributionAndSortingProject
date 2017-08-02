//port 9 // for distributing station 
/*
  FESTO DISTRIBUTION Station
  Middlesex University
  Course: Computer Science
  1st year Summer Project "Festo Sorting Station"
  Project leader: Michael Heeney 
  Stud. Rimma Chepik  
  07 2017
 */
 
// NOTE: IMPORTANT ACTIVATE/DESACTIVATE APROPIATE INPUT/OUTPUT
// M-Duino 21 IOs have I0X, Q0X
// M-Duino 42 IOs have I0x + I1X, Q0X + Q1X
// M-Duino 58 IOs have I0x + I1X + I2X , Q0X + Q1X + Q2X

//Configuration Digital IN (24Vdc) INTERRUPT IN
int I06 = 3; //INTERRUPT #1
int I05 = 2; //INTERRUPT #0
int I16 = 19; //INTERRUPT #4
int I15 = 18; //INTERRUPT #5
int I26 = 21; //INTERRUPT #2
int I25 = 20; //INTERRUPT #3

//Configuration Digital IN (24Vdc)

int I04 = 26;    // select the Analog/PWM Digital IN
int I03 = 25;    // Digital IN
int I02 = 24;    // Digital IN
int I01 = 23;    // Digital IN
int I00 = 22;    // Digital IN
int I14 = 31;    // Digital IN
int I13 = 30;    // Digital IN
int I12 = 29;    // Digital IN
int I11 = 28;    // Digital IN
int I10 = 27;    // Digital IN
int I23 = 35;    // Digital IN
int I22 = 34;    // Digital IN
int I21 = 33;    // Digital IN
int I20 = 32;    // Digital IN

//Configuration Analog/PWM/Digital IN (0-10Vdc or 24Vdc)
int Q05 = 4;    // select the Analog/PWM Digital OUT
int Q06 = 5;    // select the Analog/PWM Digital OUT
int Q07 = 6;    // select the Analog/PWM Digital OUT
int Q15 = 8;    // select the Analog/PWM Digital OUT
int Q16 = 7;    // select the Analog/PWM Digital OUT
int Q17 = 9;    // select the Analog/PWM Digital OUT
int Q25 = 12;    // select the Analog/PWM Digital OUT
int Q26 = 13;    // select the Analog/PWM Digital OUT

//Configuration Digital OUT (24Vdc)
int Q00 = 36;    // Digital OUT
int Q01 = 37;    // Digital OUT
int Q02 = 38;    // Digital OUT
int Q03 = 39;    // Digital OUT
int Q04 = 40;    // Digital OUT
int Q10 = 41;    // Digital OUT
int Q11 = 42;    // Digital OUT
int Q12 = 43;    // Digital OUT
int Q13 = 44;    // Digital OUT
int Q14 = 45;    // Digital OUT
int Q20 = 46;    // Digital OUT
int Q21 = 47;    // Digital OUT
int Q22 = 48;    // Digital OUT
int Q23 = 49;    // Digital OUT
//
//volatile int state = LOW;
//
//////////////
//// Ethernet
//////////////
//#include<EtherCard.h>
//
//static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
//uint8_t ntpServer[] = {128,138,141,172}; // time.nist.gov NTP server
//byte ntpMyPort = 8888;
//byte Ethernet::buffer[1000];   // tcp/ip send and receive buffer
//////////////

// the setup routine runs once when you press reset:
void setup() {       

  //Configuration Analog/PWM/Digital OUT (0-10Vdc or 24Vdc)  
  pinMode(Q05, OUTPUT);  
  pinMode(Q06, OUTPUT);  
  pinMode(Q07, OUTPUT);  
  pinMode(Q15, OUTPUT);  
  pinMode(Q16, OUTPUT);  
  pinMode(Q17, OUTPUT);  
  pinMode(Q26, OUTPUT);  
  pinMode(Q25, OUTPUT);  
    
  //Configuration Digital IN (24Vdc)  
  pinMode(I00, INPUT);     //switches
  pinMode(I01, INPUT);     
  pinMode(I02, INPUT);     
  pinMode(I03, INPUT);
  pinMode(I04, INPUT);  
  pinMode(I10, INPUT);     
  pinMode(I11, INPUT);     
  pinMode(I12, INPUT);     
  pinMode(I13, INPUT);     
  pinMode(I14, INPUT);     
  pinMode(I20, INPUT);
  pinMode(I21, INPUT);  
  pinMode(I22, INPUT);     
  pinMode(I23, INPUT); 

  pinMode(I05, INPUT);     
  pinMode(I06, INPUT);     
  pinMode(I15, INPUT);
  pinMode(I16, INPUT);  
  pinMode(I25, INPUT);     
  pinMode(I26, INPUT); 

    
  //Configuration Digital OUT (24Vdc)
  pinMode(Q00, OUTPUT);     //sensors
  pinMode(Q01, OUTPUT);     
  pinMode(Q02, OUTPUT);     
  pinMode(Q03, OUTPUT);
  pinMode(Q04, OUTPUT);
  pinMode(Q10, OUTPUT);     
  pinMode(Q11, OUTPUT);     
  pinMode(Q12, OUTPUT);     
  pinMode(Q13, OUTPUT);
  pinMode(Q14, OUTPUT);
  pinMode(Q20, OUTPUT);     
  pinMode(Q21, OUTPUT);     
  pinMode(Q22, OUTPUT);     
  pinMode(Q23, OUTPUT);


}


void loop() {

 if (digitalRead(56) == LOW){ //piece in tube
  digitalWrite(Q00, HIGH);  
  digitalWrite(Q00, LOW);
  delay(1000);
  delay(1000); 
  digitalWrite(Q03, HIGH);   // move left  
  delay(1000); 
  digitalWrite(Q03, HIGH);   // move left  
  delay(1000);
  digitalWrite(Q03, HIGH);   // move left 
  delay(1000);
  digitalWrite(Q03, HIGH);   // move left 
  delay(1000);
  digitalWrite(Q03, LOW);
  delay(1000);
  digitalWrite(Q01, HIGH);   // sucks air in 
  delay(1000); 
  digitalWrite(Q01, HIGH); // sucks air in 
  delay(1000); 
  digitalWrite(Q01, HIGH); // sucks air in 
  digitalWrite(Q01, LOW);  // sucks air in OFF
  delay(1000);   
  digitalWrite(Q04, HIGH); //move right
  delay(1000);
  digitalWrite(Q04, HIGH);
  delay(1000);
  digitalWrite(Q04, HIGH);
  delay(1000);
  digitalWrite(Q04, HIGH);
  delay(1000);
  digitalWrite(Q04, LOW);
  digitalWrite(Q02, HIGH); //air out
  delay(1000);
  digitalWrite(Q02, LOW);
  digitalWrite(Q03, HIGH); //move left
  delay(1000);
  digitalWrite(Q03, HIGH); //move left
  delay(1000);
  digitalWrite(Q03, HIGH);
  //digitalWrite(Q02, LOW);
  digitalWrite(Q03, LOW);
  delay(1000);
   }  // 
 else { //(digitalRead(56) == HIGH) { //nothing in tube
   digitalWrite(Q00, LOW); //don't push
   delay(1000);
  digitalWrite(Q03, LOW);   // move left  
  delay(1000);
  digitalWrite(Q01, LOW); // sucks air in OFF
  delay(1000);   
  digitalWrite(Q04, LOW);
  delay(1000);
  digitalWrite(Q02, LOW);
  delay(1000);
  digitalWrite(Q03, LOW);
  delay(1000);
          } 
          
}




////////////
// Ethernet
////////////
//  unsigned long rtime = getNtpTime();
//  
//  char tmp[30];
//  sprintf(tmp,"Time: %ld\n",rtime);
//  
//  Serial.println(tmp);
////////////
//}

