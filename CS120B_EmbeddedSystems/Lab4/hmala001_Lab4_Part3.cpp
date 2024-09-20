/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #4  Exercise #3
 *         Exercise Description: 
 *            Note: the video shows the RGB Light turning off with the Photometer, but in person it was simply going down in brightness due to a drop in voltage or whatever
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/-YbPQBlUpfQ
*/
const char b_size = 4;
const char b[b_size] = {2, 3, 4, 5};
const char rpin = 9;
const char gpin = 10;
const char bpin = 11;

unsigned short period = 100;
unsigned timeTicked = 0;
unsigned long ranges[4] = {100, 125, 150, 175};

char out = 0x00;
enum States{Zero = 0, First, Second, Third, Fourth} cState = Zero;

void setup() {
  // put your setup code here, to run once:
  for (char i = 0; i < b_size; i++){
    pinMode(b[i], OUTPUT);
  }

  Serial.begin(9600);
}

void Tick1(){
  long read = analogRead(A1);

  switch(cState){
    case Zero:
      cState = (read < ranges[0]) ? Zero : First;
      break;
    case First:
      if (read >= ranges[1]){
        cState = Second;
      }else if (read < ranges[0]){
        cState = Zero;
      }
      break;
    case Second:
      if (read >= ranges[2]){
        cState = Third;
      }else if (read < ranges[1]){
        cState = First;
      }
      break;
    case Third:
      if (read >= ranges[3]){
        cState = Fourth;
      }else if (read < ranges[2]){
        cState = Second;
      }
      break;
    case Fourth:
      cState = (read < ranges[3]) ? Third : Fourth;
      break;
    default:
      cState = Zero;
      break;
  }
  
  //Outputs
  switch(cState){
    case Zero:
      out = 0x00;
      break;
    case First:
      out = 0x01;
      break;
    case Second:
      out = 0x03;
      break;
    case Third:
      out = 0x07;
      break;
    case Fourth:
      out = 0x0F;
      break;
    default:
      out = 0x00;
      break;
  }
}
enum States2{S2_Init = 0, Forever} c2State = S2_Init;

void Tick2(){
  int photometer = analogRead(A0);
  unsigned char r = clamp(photometer, 0, 255);
  unsigned char g = clamp(photometer, 256, 511) - 256;
  unsigned char b = clamp(photometer, 512, 1023) - 512;

  //States
  switch(c2State){
    case S2_Init:
      c2State = Forever;
      break;
    default:
      c2State = Forever;
      break;
  }

  //Actions
  switch(c2State){
    case Forever:
      analogWrite(rpin, r);
      analogWrite(gpin, g);
      analogWrite(bpin, b);
      break;
    default:
      c2State = Forever;
      break;
  }
}

char getBit(unsigned char b, unsigned char p){
  return (b & (0x01 << p)) >> p;
}

long clamp(long v, long b, long t){
  return (v > t) ? t : ((v < b) ? b : v);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - timeTicked > period){
    //Photoresistor
    Tick1();
    for (char i = 0; i < b_size; i++){
      digitalWrite(b[i], (getBit(out, i) == 1) ? HIGH : LOW);
    }
    timeTicked = millis();
  }

  Tick2();
}