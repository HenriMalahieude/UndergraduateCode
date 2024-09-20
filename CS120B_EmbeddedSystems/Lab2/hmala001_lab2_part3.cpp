/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #2  Exercise #3
*         Exercise Description: Arduino Introduction, Bit Masking
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/iD-ksPfqe9c
*/

int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;

//Delay
int num = 250;

void setup() {

  // put your setup code here, to run once:
  pinMode(PD, INPUT);
  pinMode(PU, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
  }
  Serial.begin(9600);
}

char getBit(unsigned char x, unsigned char p){
  return (x & (0x01 << p)) >> p;
}

void loop() {
  int pot = analogRead(A0);
  char mapped = map(pot, 0, 1023, 0, 15);
  
  for (char i = 0; i < 4; i++){
    digitalWrite(B[i], getBit(mapped, 3-i));
  }
  Serial.println(mapped, BIN);
}