/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #5  Exercise #1
 *         Exercise Description: 
 *            Note: the video shows the RGB Light turning off with the Photometer, but in person it was simply going down in brightness due to a drop in voltage or whatever
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/ML82uFN1Uss
*/
int lePin = 5;
int upPin = 4;
int riPin = 2;
int dwPin = 3;
int sw = 7;

int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int sig[4] = {IN1,IN2,IN3,IN4};
int steps[8][4] { //codes for the motor to turn properly
  {0,0,0,1},
  {0,0,1,1},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0},
  {1,1,0,0},
  {1,0,0,0},
  {1,0,0,1},
};

void writeStepper(char step){
  for (char bit = 0; bit < 4; bit++){
    if(steps[step][bit] == 1){
      digitalWrite(sig[bit], HIGH);
    }
    else{
      digitalWrite(sig[bit], LOW);
    }
  }
}

bool pause = false;

enum State{SM_Init, SM_CLOCK, SM_ANTI} cState;
char curStep = 0;
short SM1_period = 2;
void Tick(){
  short xDir = analogRead(A1);

  //State Change
  switch(cState){
    case SM_Init:
      cState = SM_ANTI;
      break;
    case SM_ANTI:
      if (xDir < 256){
        cState = SM_CLOCK;
      }
      break;
    case SM_CLOCK:
      if (xDir > 778){
        cState = SM_ANTI;
      }
      break;
    default:
      cState = SM_ANTI;
      break;
  }

  //Behaviors
  switch(cState){
    case SM_ANTI:
      digitalWrite(lePin, HIGH);
      digitalWrite(riPin, LOW);
      if (!pause) curStep = (curStep == 7) ? 0 : curStep + 1;
      break;
    case SM_CLOCK:
      digitalWrite(lePin, LOW);
      digitalWrite(riPin, HIGH);
      if (!pause) curStep = (curStep == 0) ? 7 : curStep-1;
      break;
    default:
      cState = SM_ANTI;
      break;
  }

  if (!pause){
    writeStepper(curStep);
  }else{
    digitalWrite(lePin, HIGH);
    digitalWrite(riPin, HIGH);
  }
};

enum States2 {SM2_Init, SM2_Lower, SM2_DZone, SM2_Upper, SM2_Pause} c2State;
const short lowerLim = 256;
const short upperLim = 778;
const short SM2_period = 100;
short SM2_last = 0;
void Tick2(){
  short yDir = analogRead(0);
  //State Switch
  switch(c2State){
    case SM2_Init:
      c2State = SM2_DZone;
      break;
    case SM2_DZone:
      if (yDir > upperLim){
        c2State = SM2_Upper;
      } else if (yDir < lowerLim){
        c2State = SM2_Lower;
      }

      if (pause){
        c2State =  SM2_Pause;
      }
      break;
    case SM2_Lower:
      if (yDir >= lowerLim){
        c2State = SM2_DZone;
      }
      break;
    case SM2_Upper:
      if (yDir <= upperLim){
        c2State = SM2_DZone;
      }
      break;
    case SM2_Pause:
      if (!pause) c2State = SM2_DZone;
      break;
    default:
      c2State = SM2_DZone;
      break;
  }

  //Behaviors Switch
  switch (c2State){
    case SM2_DZone:
      digitalWrite(upPin, LOW);
      digitalWrite(dwPin, LOW);
      break;
    case SM2_Lower:
      digitalWrite(upPin, HIGH);
      digitalWrite(dwPin, LOW);
      SM1_period = (SM1_period > 2) ? SM1_period - 1 : 2;
      break;
    case SM2_Upper:
      digitalWrite(upPin, LOW);
      digitalWrite(dwPin, HIGH);
      SM1_period = (SM1_period < 50) ? SM1_period + 1 : 50;
      break;
    case SM2_Pause:
      digitalWrite(upPin, HIGH);
      digitalWrite(dwPin, HIGH);
    default:
      c2State = SM2_DZone;
      break;
  }
}

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(lePin, OUTPUT);
  pinMode(upPin, OUTPUT);
  pinMode(riPin, OUTPUT);
  pinMode(dwPin, OUTPUT);

  pinMode(sw, INPUT_PULLUP);

  Serial.begin(9600);
}

long SM1_last = 0;
void loop() {

  if (millis() - SM1_last >= SM1_period){
    Tick();
    SM1_last = millis();
  }

  if (millis() - SM2_last >= SM2_period){
    Tick2();
    SM2_last = millis();
  }

  pause = !digitalRead(sw);
}
