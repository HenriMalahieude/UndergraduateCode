/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #3  Exercise #2
*         Exercise Description:
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/q4LvuwWOcpg
*/

char red = 9;
char green = 10;
char blue = 11;

enum States {Init, Forever} cState = Init;
int Tick(){
  // put your main code here, to run repeatedly:
  short r = (millis() % 1000 * 512 / 1000) - 256; r = (r < 0) ? (r *-1) : r; //absolute values it so that it goes from 0 - 255 - 0
  short g = (millis() % 2000 * 512 / 2000) - 256; g = (g < 0) ? (g *-1) : g;
  short b = (millis() % 4000 * 512 / 4000) - 256; b = (b < 0) ? (b *-1) : b;

  //Transitions
  switch(cState){
    case Init:
      cState = Init;
      break;
    default:
      cState = Forever;
      break;
  }

  //Actions
  switch(cState){
    case Forever:
      analogWrite(red, r);
      analogWrite(green, g);
      analogWrite(blue, b);
      break;
    default:
      cState = Forever;
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  Tick();  
}