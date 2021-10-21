#include <EEPROM.h>

// uC #

  int uCx = 0; // A B C D          addr = 0
  int uCy = 0; // 1 2 3 4 5 6 7    adrr = 1
  
int harmony = 500;
int trip    = 500;
unsigned long t, tt, tx, ty, tz, ta, dx, dy, dz, da;

// defines pins numbers

const int stepX = 2;
const int stepY = 3;
const int stepZ = 4;
const int stepA = 12;
const int dirX  = 5;
const int dirY  = 6;
const int dirZ  = 7;
const int dirA  = 13;

const int enPin = 8;
const int xEn   = 9;
const int yEn   = 10;
const int zOut  = 11;
const int sOut  = 12;


int k = 0, flagx = 0, flagy = 0, flagz = 0, flaga = 0, startx = 0, starty = 0, startz = 0, starta = 0;
;
double temp = 0;

String cmd = "";
char   Rx  = "";

int art1[8][16] = {{3, 0, 0, 4, 0, 0, 0, 7, 3, 0, 1, 0, 0, 2, 0, 0}, 
                   {4, 0, 1, 7, 0, 0, 4, 4, 0, 0, 7, 0, 0, 1, 0, 0}, 
                   {5, 1, 0, 6, 0, 2, 7, 0, 2, 0, 0, 6, 3, 4, 0, 0}, 
                   {6, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0}, // temp line
                   {7, 1, 4, 2, 0, 5, 0, 0, 6, 0, 0, 2, 3, 5, 0, 0}, 
                   {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0}, 
                   {2, 4, 0, 3, 0, 6, 7, 1, 0, 0, 0, 0, 5, 6, 0, 0}, 
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int wave[10][4] = {{1, 1, 1, 10}, 
                   {1, 1, 10, 8}, 
                   {1, 1, 8 , 6}, 
                   {1, 1, 6 , 4}, 
                   {1, 1, 4 , 4}, 
                   {1, 1, 4 , 6}, 
                   {1, 1, 6 , 8}, 
                   {1, 1, 8 , 10}, 
                   {1, 1, 10, 1}, 
                   {1, 1, 1 , 1}};
                   
void setup() {

  Serial.begin(115200);
  
  Serial.println("W W W . K A T H E B . C O M");
  //EEPROM.write(0, 3);
  //EEPROM.write(1, 6);
  uCx = EEPROM.read(0); // A B C D          addr = 0
  uCy = EEPROM.read(1); // 1 2 3 4 5 6 7    adrr = 1
    
  Serial.print  ("uCx: ");
  Serial.print  (uCx);
  Serial.print  ("    uCy: ");
  Serial.println(uCy);
  
  pinMode(stepX,OUTPUT);
  pinMode(stepY,OUTPUT);
  pinMode(stepZ,OUTPUT);
  pinMode(stepA,OUTPUT);
  pinMode(stepA,OUTPUT);
  
  pinMode(dirX,OUTPUT);
  pinMode(dirY,OUTPUT);
  pinMode(dirZ,OUTPUT);
  pinMode(dirA,OUTPUT);
  
  pinMode(enPin,OUTPUT);
  pinMode(xEn,INPUT_PULLUP);
  pinMode(yEn,INPUT_PULLUP);
  pinMode(zOut,OUTPUT);
  pinMode(sOut,OUTPUT);
  
  digitalWrite(enPin,LOW);
  digitalWrite(sOut,HIGH);
  digitalWrite(zOut,HIGH);

  randomSeed(analogRead(0));

  movUp  (1500, 100);

  
}

void loop() {

  t = millis();
  
  randomSeed(analogRead(0));
  
  movDown(1500, 2000);

  movRndm(1500, 4000, 20000);

  movDown(1500, 200 * (2 + uCy));
  movUp  (1500, 200 * (2 + uCy));

  sinWave(1500, 4000);
  
  movDown(1500, 200 * (8 - uCy));
  movUp  (1500, 200 * (8 - uCy)); 

  sinWave(1500, 4000);  

  movUp  (1500, 1900);
  
  draw(1500, 30000);

  movUp  (1500, 100);
  delay(30000);
  
    
  //while(yEn);                               // Stop #3

}

// ---------------------------------------------------------------
int draw(int h, int hold){
    Serial.println("DrawIN");
    dirDown();
    
    int steps = 0, counter = 0;    
    Serial.println(art1[uCy][uCx*4+0]);
    Serial.println(art1[uCy][uCx*4+1]);
    Serial.println(art1[uCy][uCx*4+2]);
    Serial.println(art1[uCy][uCx*4+3]);

    while(counter < 1){
    while(steps < 1200){
    if (counter < art1[uCy][uCx*4+0]) { digitalWrite(stepX,HIGH); } else {digitalWrite(stepX,LOW);}
    if (counter < art1[uCy][uCx*4+1]) { digitalWrite(stepY,HIGH); } else {digitalWrite(stepY,LOW);}
    if (counter < art1[uCy][uCx*4+2]) { digitalWrite(stepZ,HIGH); } else {digitalWrite(stepZ,LOW);}
    if (counter < art1[uCy][uCx*4 +3]){ digitalWrite(stepA,HIGH); } else {digitalWrite(stepA,LOW);}   
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    steps++;    }
    steps = 0;
    digitalWrite(sOut,HIGH);
    counter++;  }
    counter = 0;
    
    while(counter < 8){
    while(steps < 600){
    if (counter < art1[uCy][uCx*4+0]) { digitalWrite(stepX,HIGH); } else {digitalWrite(stepX,LOW);}
    if (counter < art1[uCy][uCx*4+1]) { digitalWrite(stepY,HIGH); } else {digitalWrite(stepY,LOW);}
    if (counter < art1[uCy][uCx*4+2]) { digitalWrite(stepZ,HIGH); } else {digitalWrite(stepZ,LOW);}
    if (counter < art1[uCy][uCx*4 +3]){ digitalWrite(stepA,HIGH); } else {digitalWrite(stepA,LOW);}   
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    steps++;    }
    steps = 0;
    digitalWrite(sOut,HIGH);
    counter++;  }
    counter = 0;

    delay(hold);
    
    //while(yEn);                               // Stop #2

    dirUp();
    Serial.println(art1[uCy][uCx*4+0]);
    Serial.println(art1[uCy][uCx*4+1]);
    Serial.println(art1[uCy][uCx*4+2]);
    Serial.println(art1[uCy][uCx*4+3]);
    
    while(counter < 1){
    while(steps < 1200){
    if (counter < art1[uCy][uCx*4+0]) { digitalWrite(stepX,HIGH); } else {digitalWrite(stepX,LOW);}
    if (counter < art1[uCy][uCx*4+1]) { digitalWrite(stepY,HIGH); } else {digitalWrite(stepY,LOW);}
    if (counter < art1[uCy][uCx*4+2]) { digitalWrite(stepZ,HIGH); } else {digitalWrite(stepZ,LOW);}
    if (counter < art1[uCy][uCx*4 +3]){ digitalWrite(stepA,HIGH); } else {digitalWrite(stepA,LOW);}   
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    steps++;    }
    steps = 0;
    digitalWrite(sOut,HIGH);
    counter++;  }
    counter = 0;

    while(counter < 8){
    while(steps < 600){
    if (counter < art1[uCy][uCx*4+0]) { digitalWrite(stepX,HIGH); } else {digitalWrite(stepX,LOW);}
    if (counter < art1[uCy][uCx*4+1]) { digitalWrite(stepY,HIGH); } else {digitalWrite(stepY,LOW);}
    if (counter < art1[uCy][uCx*4+2]) { digitalWrite(stepZ,HIGH); } else {digitalWrite(stepZ,LOW);}
    if (counter < art1[uCy][uCx*4 +3]){ digitalWrite(stepA,HIGH); } else {digitalWrite(stepA,LOW);}   
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    steps++;    }
    steps = 0;
    digitalWrite(sOut,HIGH);
    counter++;  }
    counter = 0;
    
    
    //digitalWrite(sOut,HIGH);
    //digitalWrite(zOut,HIGH);
    Serial.println("DrawOUT");
  }
//----------------------------------------------------------------

int sinWave(int h, int steps){
  
    Serial.println("sinWaveIn");

    double s = 0, xx=0, yy=0, zz=0, aa=0;
    flagx = 0, flagy = 0, flagz = 0, flaga = 0;
    startx = 0, starty = 0, startz = 0, starta = 0;
    
    tx  = micros();
    ty  = micros();
    tz  = micros();
    ta  = micros();

    //int lock = 0;
    //if(uCx != 0){    while(digitalRead(xEn) || lock < 100){if(!digitalRead(xEn)){lock++;} else {lock = 0;}}}

    dirDown();

    delay(9919 * uCx);
    Serial.println(millis() - t );
    while(1){

      if(xx >= steps)        { digitalWrite(zOut,LOW); Serial.println(millis() - t );}
      if(xx >= steps)        { digitalWrite(dirX,HIGH); xx = 0; flagx++;}
      if(yy >= steps)        { digitalWrite(dirY,HIGH); yy = 0; flagy++;}
      if(zz >= steps)        { digitalWrite(dirZ,HIGH); zz = 0; flagz++;}
      if(aa >= steps)        { digitalWrite(dirA,HIGH); aa = 0; flaga++;}

      if((micros() - tx) >   (h-sin( xx  /steps*PI)*h+500) && xx < steps              && flagx < 2 ) {digitalWrite(stepX,HIGH); }
      if((micros() - ty) >   (h-sin( yy  /steps*PI)*h+500) && starty  && yy < steps   && flagy < 2 ) {digitalWrite(stepY,HIGH); }
      if((micros() - tz) >   (h-sin( zz  /steps*PI)*h+500) && startz  && zz < steps   && flagz < 2 ) {digitalWrite(stepZ,HIGH); }
      if((micros() - ta) >   (h-sin( aa  /steps*PI)*h+500) && starta  && aa < steps   && flaga < 2 ) {digitalWrite(stepA,HIGH); }
      
      if((micros() - tx) > 2*(h-sin( xx  /steps*PI)*h+500) && xx < steps    ) {digitalWrite(stepX,LOW);  tx  = micros();      xx++;}
      if((micros() - ty) > 2*(h-sin( yy  /steps*PI)*h+500) && starty  ) {digitalWrite(stepY,LOW);  ty  = micros();      yy++;}
      if((micros() - tz) > 2*(h-sin( zz  /steps*PI)*h+500) && startz  ) {digitalWrite(stepZ,LOW);  tz  = micros();      zz++;}
      if((micros() - ta) > 2*(h-sin( aa  /steps*PI)*h+500) && starta  ) {digitalWrite(stepA,LOW);  ta  = micros();      aa++;}


      if(xx > steps/4)      {starty = 1;}
      if(xx > steps/2)      {startz = 1;}
      if(xx > (3*steps)/4)  {starta = 1;}
      if(aa >= steps && flaga == 2) { Serial.println(millis() - tt ); break;}

    }
    
    delay(9919 * ( 3 - uCx));
    Serial.println("sinWaveOut");
  }
// ---------------------------------------------------------------

int movDown(int h, int s){
  Serial.println("movIn");
  dirDown();

  for(int x = 0; x < s; x++) {
    
    digitalWrite(stepX,HIGH);
    digitalWrite(stepY,HIGH);
    digitalWrite(stepZ,HIGH);
    digitalWrite(stepA,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);

  }  
  Serial.println("movOut");

}

// ---------------------------------------------------------------

int movUp(int h, int s){
  Serial.println("movIn");
  dirUp();

  for(int x = 0; x < s; x++) {
    
    digitalWrite(stepX,HIGH);
    digitalWrite(stepY,HIGH);
    digitalWrite(stepZ,HIGH);
    digitalWrite(stepA,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);

  }  
  Serial.println("movOut");

}

// ---------------------------------------------------------------

int movRndm(int h, int s, int hold){
  
  Serial.println("movRndmIn");
  digitalWrite(sOut,HIGH);
  digitalWrite(zOut,HIGH);

  
  int rndmx = random(s);
  int rndmy = random(s);
  int rndmz = random(s);
  int rndma = random(s);

  tt = millis();

  dirDown();
  for(int x = 0; x < s; x++) {
    
    if (x < rndmx) digitalWrite(stepX,HIGH);
    if (x < rndmy) digitalWrite(stepY,HIGH);
    if (x < rndmz) digitalWrite(stepZ,HIGH);
    if (x < rndma) digitalWrite(stepA,HIGH);
    delayMicroseconds(h);
    if (x < rndmx) digitalWrite(stepX,LOW);
    if (x < rndmy) digitalWrite(stepY,LOW);
    if (x < rndmz) digitalWrite(stepZ,LOW);
    if (x < rndma) digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    
  } 

    while(millis() < tt + 10000);

    delay(hold);
    //while(yEn);                               // Stop #1
    
    tt = millis();

    dirUp();
    for(int x = 0; x < s; x++) {
    
    if (x < rndmx) digitalWrite(stepX,HIGH);
    if (x < rndmy) digitalWrite(stepY,HIGH);
    if (x < rndmz) digitalWrite(stepZ,HIGH);
    if (x < rndma) digitalWrite(stepA,HIGH);
    delayMicroseconds(h);
    if (x < rndmx) digitalWrite(stepX,LOW);
    if (x < rndmy) digitalWrite(stepY,LOW);
    if (x < rndmz) digitalWrite(stepZ,LOW);
    if (x < rndma) digitalWrite(stepA,LOW);
    delayMicroseconds(h);
    
  }

    while(millis() < tt + 10000);
    
    Serial.println("movRndmOut");
}

// ----------------------------------

int movX(int h, int s){
  for(int x = 0; x < s; x++) {
    digitalWrite(stepX,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepX,LOW);
    delayMicroseconds(h);
  }
}

// ----------------------------------

int movY(int h, int s){
  for(int x = 0; x < s; x++) {
    digitalWrite(stepY,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepY,LOW);
    delayMicroseconds(h);
  }
}

// ----------------------------------

int movZ(int h, int s){
  for(int x = 0; x < s; x++) {
    digitalWrite(stepZ,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepZ,LOW);
    delayMicroseconds(h);
  }
}

// ----------------------------------

int movA(int h, int s){
  for(int x = 0; x < s; x++) {
    digitalWrite(stepA,HIGH);
    delayMicroseconds(h);
    digitalWrite(stepA,LOW);
    delayMicroseconds(h);
  }
}

// ----------------------------------

int breakAll(){
  for(float i = 0; i <= 100; i += 1){
    digitalWrite(stepX,HIGH);
    digitalWrite(stepY,HIGH);
    digitalWrite(stepZ,HIGH);
    digitalWrite(stepA,HIGH);
    delayMicroseconds(2000 + 30 * i);
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(2000 + 30 * i);
  }
}

// ----------------------------------

int startAll(){

    
for(float i = 0.0; i <= 2* PI; i += 0.001){

/*
    Serial.print(sin(i - 0.000)*1000);
    Serial.print("    ");
    Serial.println(fmod(sin(i - 0.000)*1000, 2));
*/
    if ((fmod(sin(i - 0.000)*1000, 2) > 1) && i > 0     && i < PI        ) digitalWrite(stepX,HIGH);
    if ((fmod(sin(i - 0.125)*1000, 2) > 1) && i > 0.125 && i < PI + 0.125) digitalWrite(stepY,HIGH);
    if ((fmod(sin(i - 0.250)*1000, 2) > 1) && i > 0.250 && i < PI + 0.250) digitalWrite(stepZ,HIGH);
    if ((fmod(sin(i - 0.375)*1000, 2) > 1) && i > 0.375 && i < PI + 0.375) digitalWrite(stepA,HIGH);
    delayMicroseconds(1000);
    
    digitalWrite(stepX,LOW);
    digitalWrite(stepY,LOW);
    digitalWrite(stepZ,LOW);
    digitalWrite(stepA,LOW);
    delayMicroseconds(1000);
    
  }

}

// ----------------------------------
void dirUp(){
  digitalWrite(dirX,HIGH);
  digitalWrite(dirY,HIGH);
  digitalWrite(dirZ,HIGH);
  digitalWrite(dirA,HIGH);
  }

void dirDown(){
  digitalWrite(dirX,LOW);
  digitalWrite(dirY,LOW);
  digitalWrite(dirZ,LOW);
  digitalWrite(dirA,LOW);
  }

void SerialChk(){
  if  (Serial.available() > 0) {
    while (Serial.available() > 0) {
      Rx   = Serial.read();
      Serial.print(Rx);
      cmd += Rx;
    }
    //cmd = "";
  }

}
