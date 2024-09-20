#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define SERVO_PIN 2
#define BEEP_PIN 3
#define DIGIT1_PIN 11
#define DIGIT2_PIN 12
#define DIGIT3_PIN 13

typedef struct task{
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
}task;

char numbers[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,0,0,1,1}, //9
};

void selectDigit(char d = 1){
  d = (d > 3) ? 3 : d; //make sure it's between 1 and 4
  d = (d < 1) ? 1 : d;

  digitalWrite(DIGIT1_PIN, (d == 1) ? LOW : HIGH);
  digitalWrite(DIGIT2_PIN, (d == 2) ? LOW : HIGH);
  digitalWrite(DIGIT3_PIN, (d == 3) ? LOW : HIGH);
}

void writeNumber(char n = 0){
  int segApin = 4;
  n = (n > 9) ? 9 : n; //make sure it's between 0 and 9
  n = (n < 0) ? 0 : n;

  for (int i = 0; i < 7; i++){
    digitalWrite(i+segApin, numbers[n][i]);
  }
}

enum SegmentStates{SEG_Init, SEG_Digit1, SEG_Digit2, SEG_Digit3};
int Segment_Tick(int cState);

unsigned short reportedDist = 0, beepDist = 15;
bool trig = false;
enum SonarStates{SON_Init = 0, SON_Wait, SON_TrigUp, SON_TrigDown, SON_Listen1, SON_Listen2};
int Sonar_Tick(int cState);

short servo_period = 100; //us
short servo_min = 800, servo_max = 1800;
short currentAngle = servo_min;
enum ServoStates{SS_Init, SS_High, SS_Low, SS_Pause};
int Servo_Tick(int cState);

bool forward = true;
short servo_mngr_period = 500; //ms
unsigned char servo_step = 100;
//TODO: Get Distance reading between each
enum ServoManagerStates{SMS_Init, SMS_Move, SMS_GetReadingT, SMS_GetReadingE};
int ServoManager_Tick(int cState);

bool beep = false;
int Beep_Tick(int c){
  if (beep){
    digitalWrite(BEEP_PIN, HIGH);
    beep = false;
  }else{
    digitalWrite(BEEP_PIN, LOW);
  }
  return c;
}

const char msNum = 3;
task msTasks[msNum];

const char usNum = 2;
task usTasks[usNum];

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  for (char i = 2; i < 14; i++){
    pinMode(i, OUTPUT);
  }

  //Millisecond Tasks
  int m = 0;
  msTasks[m].TickFct = &Segment_Tick;
  msTasks[m].period = 5; //ms
  msTasks[m].elapsedTime = 0;
  msTasks[m].state = 0;
  m++;
  msTasks[m].TickFct = &ServoManager_Tick;
  msTasks[m].period = servo_mngr_period;
  msTasks[m].elapsedTime = 0;
  msTasks[m].state = 0;
  m++;
  msTasks[m].TickFct = &Beep_Tick;
  msTasks[m].period = 250;
  msTasks[m].elapsedTime = 0;
  msTasks[m].state = 0;

  int u = 0;
  usTasks[u].TickFct = &Sonar_Tick;
  usTasks[u].period = 10; //us
  usTasks[u].elapsedTime = 0;
  usTasks[u].state = 0;
  u++;
  usTasks[u].TickFct = &Servo_Tick;
  usTasks[u].period = servo_period;
  usTasks[u].elapsedTime = 0;
  usTasks[u].state = 0;

  //Serial.begin(9600);
}

//unsigned long test = 0;
void loop() {
  for (char m = 0; m < msNum; m++){
    if (millis() - msTasks[m].elapsedTime >= msTasks[m].period){
      msTasks[m].state = msTasks[m].TickFct(msTasks[m].state);
      msTasks[m].elapsedTime = millis();
    }
  }

  for (char u = 0; u < usNum; u++){
    if (micros() - usTasks[u].elapsedTime >= usTasks[u].period){
      usTasks[u].state = usTasks[u].TickFct(usTasks[u].state);
      usTasks[u].elapsedTime = micros();
    }
  }
}

void clamp(unsigned short *v, int bot, int top){
  (*v) = (*v > top) ? top : *v;
  (*v) = (*v < bot) ? bot : *v;
}

int Segment_Tick(int cState){
  char D3_n = reportedDist / 100;
  char D2_n = (reportedDist - D3_n*100) / 10;
  char D1_n = (reportedDist - D3_n*100 - D2_n*10);
  //Serial.print(reportedDist); Serial.print(": "); Serial.print((int)D3_n); Serial.print(", "); Serial.print((int)D2_n); Serial.print(", "); Serial.println((int)D1_n);
  
  switch (cState){ //Simply transition form D1 -> D2 -> D3
    case SEG_Init:
      cState = SEG_Digit1;
      break;
    case SEG_Digit1:
      cState = SEG_Digit2;
      break;
    case SEG_Digit2:
      cState = SEG_Digit3;
      break;
    case SEG_Digit3:
      cState = SEG_Digit1;
      break;
    default:
      //Serial.println("Segmented Display Default 1?");
      cState = SEG_Digit1;
      break;
  }

  //Actions
  switch(cState){
    case SEG_Digit1:
      selectDigit(1);
      writeNumber(D1_n);
      break;
    case SEG_Digit2:
      selectDigit(2);
      writeNumber(D2_n);
      break;
    case SEG_Digit3:
      selectDigit(3);
      writeNumber(D3_n);
      break;
    default:
      //Serial.println("Segmented Display Default 2?");
      cState = SEG_Digit1;
      break;
  }

  return cState;
}

int Sonar_Tick(int cState){
  static unsigned long cnt = 0;
  
  switch (cState){
    case SON_Init:
      cState = SON_Wait;
      break;
    case SON_Wait:
      cState = (trig) ? SON_TrigUp : SON_Wait;
      break;
    case SON_TrigUp:
      cState = SON_TrigDown;
      break;
    case SON_TrigDown:
      cState = SON_Listen1;
      break;
    case SON_Listen1:
      cState = (digitalRead(ECHO_PIN)) ? SON_Listen2 : SON_Listen1;
      break;
    case SON_Listen2:
      if (!digitalRead(ECHO_PIN)){
        cState = SON_Wait;
        reportedDist = (micros() - cnt) / 58;
        clamp(&reportedDist, 0, 999);
        trig = false;
      }
      break;
    default:
     // Serial.println("Sonar Default 1?");
      cState = SON_Wait;
      break;
  }

  //Action
  switch (cState){
    case SON_TrigUp:
      digitalWrite(TRIGGER_PIN, HIGH);
      break;
    case SON_TrigDown:
      digitalWrite(TRIGGER_PIN, LOW);
      break;
    case SON_Listen1:
      cnt = micros();
      break;
    default:
      digitalWrite(TRIGGER_PIN, LOW);
      break;
  }

  return cState;
}

int Servo_Tick(int cState){
  static long cnt = 0;
  switch(cState){
    case SS_Init:
      cState = SS_High;
      break;
    case SS_High:
      cnt += servo_period;
      if (cnt > currentAngle){
        cState = SS_Low;
      }
      break;
    case SS_Low:
      cnt += servo_period;
      if (cnt >= 20000){
        cState = SS_Pause;
        cnt = 0;
      }
      break;
    case SS_Pause:
      cnt += servo_period;
      if (cnt >= 0) {
        cnt = 0;
        cState = SS_High;
      }
      break;
    default:
      Serial.println("Servo Tick Default 1");
      cState = SS_Init;
      break;
  }

  switch(cState){
    case SS_High:
      digitalWrite(SERVO_PIN, HIGH);
      break;
    default:
      digitalWrite(SERVO_PIN, LOW);
      break;
  }

  return cState;
}

int ServoManager_Tick(int cState){
  switch(cState){
    case SMS_Init:
      currentAngle = servo_min;
      cState = SMS_Move;
      break;
    case SMS_Move:
      if (forward){
        currentAngle += servo_step;
        if (currentAngle >= servo_max){
          forward = false;
          currentAngle = servo_max;
        }
      }else{ //moving backward
        currentAngle -= servo_step;
        if (currentAngle <= servo_min){
          forward = true;
          currentAngle = servo_min;
        }
      }
      cState = SMS_GetReadingT;
      break;
    case SMS_GetReadingT:
      trig = true;
      cState = SMS_GetReadingE;
      break;
    case SMS_GetReadingE:
      if (!trig){
        //Serial.println(reportedDist);
        cState = SMS_Move;
        if (reportedDist <= beepDist){
          beep = true;
        }
      }
      break;
    default:
      Serial.println("Servo Manager Tick Default 1");
      cState = SMS_Init;
      break;
  }

  return cState;
}
