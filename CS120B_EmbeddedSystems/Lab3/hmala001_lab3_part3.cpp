/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #3  Exercise #3
*         Exercise Description:
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/0JBc3HJrnPI
*/

#define PHOTO_PIN A1
#define POTEN_PIN A0

char red = 9;
char green = 10;
char blue = 11;

int B[4] = {2, 3, 4, 5};
void writeToAll(char val){
  for (char i = 0; i < 4; i++){
    digitalWrite(B[i], val); //
  }
}

enum States {Init, Night, Day} cState = Init;
int Tick(){
  const unsigned char min = 250;

  char read = map(analogRead(A0), 0, 1023, 0, 5) - 1;
  short r = (millis() % 1000 * 512 / 1000) - 256; r = (r < 0) ? (r *-1) : r; //absolute values it so that it goes from 0 - 255 - 0
  short g = (millis() % 2000 * 512 / 2000) - 256; g = (g < 0) ? (g *-1) : g;
  short b = (millis() % 4000 * 512 / 4000) - 256; b = (b < 0) ? (b *-1) : b;

  short sun = analogRead(PHOTO_PIN);

  //Transitions
  switch(cState){
    case Init:
      cState = Night;
      break;
    case Night:
      cState = (sun > min) ? Day : Night;
      break;
    case Day:
      cState = (sun > min) ? Day : Night;
      break;
    default:
      cState = Init;
      break;
  }

  //Actions
  switch(cState){
    case Night:
      writeToAll(LOW);
      analogWrite(red, r);
      analogWrite(green, g);
      analogWrite(blue, b);
      break;
    case Day:
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
      for (char i = 0; i < 4; i++){
        digitalWrite(B[i], ((read) >= i) ? HIGH : LOW);
      }
      break;
    default:
      cState = Night;
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