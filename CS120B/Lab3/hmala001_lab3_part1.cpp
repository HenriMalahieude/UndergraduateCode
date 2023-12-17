/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #3  Exercise #1
*         Exercise Description:
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/dwkI9kt23YE
*/

int B[4] = {2, 3, 4, 5};
void writeToAll(char val){
  for (char i = 0; i < 4; i++){
    digitalWrite(B[i], val); //
  }
}

enum States {Init, On, Off} cState = Init;
void Tick(){
  char read = map(analogRead(A0), 0, 1023, 0, 5) - 1;
  //Transitions
  switch (cState){
    case Init:
      cState = Off;
      break;
    case Off:
      cState = (analogRead(A1) >= 150) ? On : Off;
      break;
    case On:
      cState = (analogRead(A1) < 150) ? Off : On;
      break;
    default:
      cState = Off;
      break;
  }

  //Actions
  switch (cState){
    case Off:
      writeToAll(LOW);
      break;
    case On:
      for (char i = 0; i < 4; i++){
        digitalWrite(B[i], ((read) >= i) ? HIGH : LOW);
      }
      break;
    default:
      cState = Off;
      break;
  }
}


void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  Tick();
}