/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #4  Exercise #2
 *         Exercise Description: [optional - include for your own benefit]
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/ytVtC7179As
*/
const char b_size = 4;
const char b[b_size] = {2, 3, 4, 5};

unsigned short period = 500;
unsigned long timeTicked = 0;

char out = 0x00;
enum States{Start = 0, First, Second, Third, Fourth} cState = Start;
States lastState = Start;

void setup() {
  // put your setup code here, to run once:
  for (char i = 0; i < b_size; i++){
    pinMode(b[i], OUTPUT);
  }

  Serial.begin(9600);
}

void Transition(States to){
  lastState = cState;
  cState = to;
}

void Tick(){
  switch(cState){
    case Start:
      Transition(First);
      break;
    case First:
      Transition(Second);
      break;
    case Second:
      (lastState == First) ? Transition(Third) : Transition(First) ;
      break;
    case Third:
      (lastState == Second) ? Transition(Fourth) : Transition(Second);
      break;
    case Fourth:
      Transition(Third);
      break;
    default:
      cState = First;
      break;
  }
  
  switch(cState){
    case Start:
      out = 0x01;
      break;
    case First:
      out = 0x01;
      break;
    case Second:
      out = 0x02;
      break;
    case Third:
      out = 0x04;
      break;
    case Fourth:
      out = 0x08;
      break;
    default:
      out = 0x01;
      break;
  }
}

enum States2{S2_Init = 0, Forever} c2State = S2_Init;
void Tick2(){
  unsigned short reading = analogRead(A0);
  switch(c2State){
    case S2_Init:
      c2State = Forever;
      break;
    default:
      c2State = Forever;
      break;
  }

  switch(c2State){
    case Forever:
      period = map(reading, 0, 1023, 100, 500);
      break;
    default:
      c2State = Forever;
      break;
  }
}

char getBit(unsigned char b, unsigned char p){
  return (b & (0x01 << p)) >> p;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() - timeTicked >= period){
    Tick();
    for (char i = 0; i < b_size; i++){
      digitalWrite(b[i], (getBit(out, i)) ? HIGH : LOW);
    }
    timeTicked = millis();
  }
  

  Tick2();
}