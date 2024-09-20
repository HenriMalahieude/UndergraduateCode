/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #5  Exercise #2
 *         Exercise Description: 
 *            Note: the video shows the RGB Light turning off with the Photometer, but in person it was simply going down in brightness due to a drop in voltage or whatever
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/TnXcbDlD9hA
*/
#define ANALOG_X_PIN 1
#define ANALOG_Y_PIN 0

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

struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
};

const unsigned short tasksNum = 2;
task Tasks[tasksNum];

enum Inputs{NIL = 0, LEFT, UP, RIGHT, DOWN};

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

bool detectJoyIn(Inputs check){
  const short upperLim = 778; //For the Joystick
  const short lowerLim = 256;

  if (check == LEFT){
    return analogRead(ANALOG_X_PIN) < lowerLim;
  } else if (check == RIGHT){
    return analogRead(ANALOG_X_PIN) > upperLim;
  } else if (check == UP){
    return analogRead(ANALOG_Y_PIN) > upperLim;
  }else if (check == DOWN){
    return analogRead(ANALOG_Y_PIN) < lowerLim;
  }else if (check == NIL){
    short x = analogRead(ANALOG_X_PIN);
    short y = analogRead(ANALOG_Y_PIN);
    return x >= lowerLim && x <= upperLim && y >= lowerLim && y <= upperLim;
  }

  return false;
}

enum DoorStatus{OPENING, OPEN, CLOSING, CLOSED} Door_Stat = CLOSED;
bool Taking_Input = true;

Inputs correct[4] = {LEFT, LEFT, UP, UP};
Inputs current[4] = {NIL, NIL, NIL, NIL};
char inputLvl = 0;

bool addInput(Inputs in){
  current[inputLvl] = in;

  if (inputLvl == 3){
    inputLvl = 0;
    return true;
  }
  
  inputLvl++;
  return false;
}

void AllPins(char vv){
  digitalWrite(upPin, vv);
  digitalWrite(dwPin, vv);
  digitalWrite(riPin, vv);
  digitalWrite(lePin, vv);
}

//Blink the Lights, for Input
enum SM1States {SM1_Init, SM1_DZone, SM1_Left, SM1_Up, SM1_Right, SM1_Down};
long SM1_Light_Period = 500;
long SM1_Light_Last = 0;

bool SM1_Light_Deb = true;
int SM1_Tick(int cState){
  //Switch the States
  switch(cState){
    case SM1_Init:
      cState = SM1_DZone;
      break;
    case SM1_DZone:
      if (Taking_Input){
        if (detectJoyIn(UP)){
          Serial.println("UP");
          cState = SM1_Up;
        }else if (detectJoyIn(DOWN)){
          Serial.println("DOWN");
          cState = SM1_Down;
        }else if (detectJoyIn(LEFT)){
          Serial.println("LEFT");
          cState = SM1_Left;          
        }else if (detectJoyIn(RIGHT)){
          Serial.println("RIGHT");
          cState = SM1_Right;
        }

        SM1_Light_Last = millis();
      }
      break;
    default:
      if (millis() - SM1_Light_Last >= SM1_Light_Period && detectJoyIn(NIL)){ //Set back to normal once they've stopped inputting
        cState = SM1_DZone;
        SM1_Light_Deb = true;
        AllPins(LOW);
      }
      
      break;
  }

  //Switch the Behavior
  switch(cState){
    case SM1_DZone:
      break;
    case SM1_Up:
      if (SM1_Light_Deb){
        AllPins(LOW);
        digitalWrite(upPin, HIGH);
        Taking_Input = !addInput(UP);
        SM1_Light_Deb = false;
      }
      break;
    case SM1_Down:
      if (SM1_Light_Deb){
        AllPins(LOW);
        digitalWrite(dwPin, HIGH);
        Taking_Input = !addInput(DOWN);
        SM1_Light_Deb = false;
      }
      break;
    case SM1_Left:
      if (SM1_Light_Deb){
        AllPins(LOW);
        digitalWrite(lePin, HIGH);
        Taking_Input = !addInput(LEFT);
        SM1_Light_Deb = false;
      }
      break;
    case SM1_Right:
      if (SM1_Light_Deb){
        AllPins(LOW);
        digitalWrite(riPin, HIGH);
        Taking_Input = !addInput(RIGHT);
        SM1_Light_Deb = false;
      }
      break;
  }

  return cState;
}

bool checkMatching(){
  for (char i = 0; i < 4; i++){
    if (correct[i] != current[i]){
      return false;
    }
  }

  return true;
}

//Safe Operating
enum SM2State {SM2_Init, SM2_Closed, SM2_Wrong, SM2_Open, SM2_NewCode};
char SM2_Wrong_C = 0; //Max: 6 (on + off states)
long SM2_Wrong_Period = 200;
long SM2_Wrong_Last = 0;
int SM2_Tick(int cState){
  switch(cState){
    case SM2_Init:
      cState = SM2_Closed;
      break;
    case SM2_Closed:
      if (!Taking_Input){
        if (Door_Stat == CLOSED){
          if (checkMatching()){
            Serial.println(" - RIGHT!");
            Door_Stat = OPENING;
            cState = SM2_Open;
            Taking_Input = true;
          } else {
            Serial.println(" - WRONG!");
            cState = SM2_Wrong; //Incorrect, therefore flash
            SM2_Wrong_Last = millis();
          }
        }
      }
      break;
    case SM2_Wrong:
      if (SM2_Wrong_C < 6){ //Flash'
        if (millis() - SM2_Wrong_Last >= SM2_Wrong_Period){
          SM2_Wrong_C++;
          SM2_Wrong_Last = millis();
        }
      }else{
        SM2_Wrong_C = 0; //Finished Flashing
        cState = SM2_Closed;
        Taking_Input = true;
      }
      break;
    case SM2_Open:
      if (!Taking_Input){ //To Close the Safe
        if (Door_Stat == OPEN){
          if (checkMatching()){
            Door_Stat = CLOSING;
          }else{
            AllPins(LOW);
            Taking_Input = true;
          }
        }else if (Door_Stat == CLOSED){
          cState = SM2_Closed;
          Taking_Input = true;
        }

        
      } else if (!digitalRead(sw)){ //To Change PassCode
        cState = SM2_NewCode;
        AllPins(LOW); //so we can see the input
        inputLvl = 0;
        Taking_Input = true;
      }
      break;
    case SM2_NewCode: //I need to do behaviors in here unfortunately
      if (!Taking_Input){
        for (char i = 0; i < 4; i++){
          correct[i] = current[i]; //Set the Password
        }
        cState = SM2_Open;
        inputLvl = 0;
        Taking_Input = true;
      }
      break;
  }

  switch(cState){
    case SM2_Wrong:
      if (SM2_Wrong_C % 2 == 1){
        AllPins(HIGH);
      }else{
        AllPins(LOW);
      }
      break;
    case SM2_Open:
      AllPins(HIGH);
      break;
    default:
      break;
  }

  return cState;
}

volatile short angle = 0;
short maxAng = 200;
short step = 0;
short ST_Period = 2;
long ST_Last = 0;

void SimpleTick(){
  switch(Door_Stat){
    case OPENING:
      //Serial.println((int)angle);
      if (step >= 7){
        step = 0;
        angle++;
      } else {
        step++;
      }

      if (angle >= maxAng){
        angle = 0;
        Door_Stat = OPEN;
      }

      break;
    case CLOSING:
      if (step <= 0){
        step = 7;
        angle++;
      } else {
        step--;
      }
      
      if (angle >= maxAng){
        angle = 0;
        Door_Stat = CLOSED;
        AllPins(LOW);
      }
      break;
    default:
      break;
  }

  writeStepper(step);
}

void setup() {
  //Pin Set Up
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode(lePin, OUTPUT);
  pinMode(upPin, OUTPUT);
  pinMode(riPin, OUTPUT);
  pinMode(dwPin, OUTPUT);

  pinMode(sw, INPUT_PULLUP);

  // Task/State-Machine Set up
  unsigned char tI = 0;
  Tasks[tI].state = SM1_Init;
  Tasks[tI].period = 1;
  Tasks[tI].elapsedTime = 0;
  Tasks[tI].TickFct = &SM1_Tick; //Input Taking Function

  tI++;
  Tasks[tI].state = SM2_Init;
  Tasks[tI].period = 10;
  Tasks[tI].elapsedTime = 0;
  Tasks[tI].TickFct = &SM2_Tick; //Safe Operating Function

  Serial.begin(9600);
}

long SM1_last = 0;
void loop() {
  for (char i = 0; i < tasksNum; ++i) {
     if ( (millis() - Tasks[i].elapsedTime) >= Tasks[i].period) {
        Tasks[i].state = Tasks[i].TickFct(Tasks[i].state);
        Tasks[i].elapsedTime = millis(); // Last time this task was ran
     }
   }

   if (millis() - ST_Last >= ST_Period){
     SimpleTick();
     ST_Last = millis();
     //Serial.println(Door_Stat);
   }
}
