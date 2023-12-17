/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #2  Exercise #2
*         Exercise Description:
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/A6HcsCak9DI
*/

int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;

//Delay
int num = 250;

//Light info
bool up = true;
char cnt = 0;

void setup() {

  // put your setup code here, to run once:
  pinMode(PD, INPUT);
  pinMode(PU, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}


void loop() {
  //Input First
  if (num < 1250 && digitalRead(PU) == HIGH){
    num *= 2;
  }else if (num > 250 && digitalRead(PD) == LOW){
    num /= 2;
  }

  delay(num);
  if (up){
    cnt++;
    if (cnt >= 4){
      up = false;
    }
  }else{
    cnt--;
    if (cnt <= 0){
      up = true;
    }
  }

  for (char i = 0; i < cnt; i++){
    digitalWrite(B[i], HIGH);
  }
  for (char i = cnt; i < 4; i++){
    digitalWrite(B[i], LOW);
  }
}