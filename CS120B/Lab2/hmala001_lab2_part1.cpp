/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #2  Exercise #1
*         Exercise Description:
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/LRC_krLJre0
*/

int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;

int num = 750;
void setup() {

  // put your setup code here, to run once:
  pinMode(PD, INPUT);
  pinMode(PU, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}

void on(){
  for (int i = 0; i < 4; i++) {
      digitalWrite(B[i], HIGH);
  }
}

void off(){
  for (int i = 0; i < 4; i++) {
      digitalWrite(B[i], LOW);
  }
}

void loop() {

  // put your main code here, to run repeatedly:

  //flash();
  if (digitalRead(PD) == LOW){
    on();
  }

  if (digitalRead(PU) == HIGH){
    off();
  }
}