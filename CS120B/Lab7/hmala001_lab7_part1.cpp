/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #7  Exercise #1
 *         Exercise Description: 
 *            DM-, whoops I mean DHT hahahaha
 *            Crystal M-, whoops I mean LiquidCrystal hahahaha
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/9fStsj5Z2u0
*/

#include <LiquidCrystal.h>
#include <DHT.h>

#define BLUE 8
#define YLLW 9
#define WHIT 10
#define REDP 11

#define JOYBUT 12

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(A0, DHT11);

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

const short delay_gcd = 5;
const char taskNum = 7;
task tasks[taskNum];

char DetectedTemp = -1, TargetTemp = 75;
char DetectedHumid = -1, TargetHumid = 30;

//Pulse Width Modulators
enum PWMMetaStates{PWM_Init, PWM_Off, PWM_Low, PWM_High};
const short humidPeriod = 200; const char hum_h = 1; const char hum_l = 4; //total 5, 20%
bool HumidOn = false;
int HumidifierTick(int cState);

const short dehumPeriod = 400; const char deh_h = 1; const char deh_l = 3; //total 4, 25%
bool DehumOn = false;
int DehumidifierTick(int cState);

const short coolrPeriod = 300; const char coo_h = 3; const char coo_l = 2; //total 5, 60%
bool CoolrOn = false;
int CoolerTick(int cState);

const short heatrPeriod = 100; const char hea_h = 19; const char hea_l = 1; //total 20, 95%
bool HeatrOn = false;
int HeaterTick(int cState);

//Big Boy Manager
enum MNGRState{MNGR_Init, MNGR_Off, MNGR_ReleaseF, MNGR_ReleaseN, MNGR_On}; //Release state is doubled so for each direction Off <--> On
int MNGRTick(int cState);

enum JoySampleState{JS_Init, JS_TempMode, JS_HumidMode};
int SampleJoystick(int cState);

int SampleDHT(int cState){
  DetectedTemp = dht.readTemperature(true);
  DetectedHumid = dht.readHumidity();
}

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(BLUE, OUTPUT);
  pinMode(YLLW, OUTPUT);
  pinMode(WHIT, OUTPUT);
  pinMode(REDP, OUTPUT);
  pinMode(JOYBUT, INPUT_PULLUP);

  int i = 0;
  tasks[i].state = PWM_Init; //Humidifier PWM
  tasks[i].elapsedTime = 0;
  tasks[i].period = humidPeriod / (hum_h + hum_l);
  tasks[i].TickFct = &HumidifierTick;
  i++;
  tasks[i].state = PWM_Init; //Dehumidifier PWM
  tasks[i].elapsedTime = 0;
  tasks[i].period = dehumPeriod / (deh_h + deh_l);
  tasks[i].TickFct = &DehumidifierTick;
  i++;
  tasks[i].state = PWM_Init;
  tasks[i].elapsedTime = 0;
  tasks[i].period = coolrPeriod / (coo_h + coo_l);
  tasks[i].TickFct = &CoolerTick;
  i++;
  tasks[i].state = PWM_Init;
  tasks[i].elapsedTime = 0;
  tasks[i].period = heatrPeriod / (hea_h + hea_l);
  tasks[i].TickFct = &HeaterTick;
  i++;
  tasks[i].state = 0;
  tasks[i].elapsedTime = 0;
  tasks[i].period = 300;
  tasks[i].TickFct = &SampleJoystick;
  i++;
  tasks[i].state = 0;
  tasks[i].elapsedTime = 0;
  tasks[i].period = 500;
  tasks[i].TickFct = &SampleDHT;
  i++;
  tasks[i].state = MNGR_Init;
  tasks[i].elapsedTime = 0;
  tasks[i].period = delay_gcd;
  tasks[i].TickFct = &MNGRTick;
  i++;

  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  for (unsigned char i = 0; i < taskNum; ++i) {
    if ((millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}

int PWMMetaTick(int cState, unsigned char *cnt, bool on, char pin, short high, short low){
  //Transitions
  switch(cState){
    case PWM_Init:
      cState = PWM_Off;
      break;
    case PWM_Off:
      cState = (on) ? PWM_Low : PWM_Off;
      break;
    case PWM_Low:
      (*cnt) += 1;
      cState = (*cnt > low) ? PWM_High : ((on) ? PWM_Low : PWM_Off);
      break;
    case PWM_High:
      (*cnt) += 1;
      if (*cnt > (high + low)){
        cState = ((on) ? PWM_Low : PWM_Off);
        (*cnt) = 0;
      }
      break;
    default:
      Serial.println("Default PWM State?");
      cState = PWM_Off;
      break;
  }

  //Actions
  switch(cState){
    case PWM_Low:
      digitalWrite(pin, LOW);
      break;
    case PWM_High:
      digitalWrite(pin, HIGH);
      break;
    default:
      digitalWrite(pin, LOW);
      break;
  }

  return cState;
}

int HumidifierTick(int cState){
  static unsigned char count = 0;
  return PWMMetaTick(cState, &count, HumidOn, BLUE, hum_h, hum_l);
}

int DehumidifierTick(int cState){
  static unsigned char count = 0;
  return PWMMetaTick(cState, &count, DehumOn, YLLW, deh_h, deh_l);
}

int CoolerTick(int cState){
  static unsigned char count = 0;
  return PWMMetaTick(cState, &count, CoolrOn, WHIT, coo_h, coo_l);
}

int HeaterTick(int cState){ 
  static unsigned char count = 0;
  return PWMMetaTick(cState, &count, HeatrOn, REDP, hea_h, hea_l);
}

int MNGRTick(int cState){
  switch(cState){
    case MNGR_Init:
      cState = MNGR_Off;
      break;
    case MNGR_Off:
      cState = (digitalRead(JOYBUT) == LOW) ? MNGR_ReleaseN : MNGR_Off;
      break;
    case MNGR_On:
      cState = (digitalRead(JOYBUT) == LOW) ? MNGR_ReleaseF : MNGR_On;
      break;
    case MNGR_ReleaseN:
      cState = (digitalRead(JOYBUT) != LOW) ? MNGR_On : MNGR_ReleaseN;
      break;
    case MNGR_ReleaseF:
      cState = (digitalRead(JOYBUT) != LOW) ? MNGR_Off : MNGR_ReleaseF;
      break;
    default:
      Serial.println("Default Manager?");
      cState = MNGR_Off;
      break;
  }

  switch(cState){
    case MNGR_On:
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.print((int)DetectedTemp);
      lcd.print(" Set:");
      lcd.print((int)TargetTemp);

      lcd.setCursor(0, 1);
      lcd.print("Hum%:");
      lcd.print((int)DetectedHumid);
      lcd.print(" Set:");
      lcd.print((int)TargetHumid);

      if (DetectedHumid > TargetHumid){
        DehumOn = true;
        HumidOn = false;
      }else if (DetectedHumid < TargetHumid){
        DehumOn = false;
        HumidOn = true;
      }else{
        HumidOn = false;
        DehumOn = false;
      }

      if (DetectedTemp > TargetTemp){
        CoolrOn = true;
        HeatrOn = false;
      } else if (DetectedTemp < TargetTemp){
        CoolrOn = false;
        HeatrOn = true;
      } else {
        CoolrOn = false;
        HeatrOn = false;
      }
      break;
    default:
      lcd.clear();
      HumidOn = false;
      DehumOn = false;
      CoolrOn = false;
      HeatrOn = false;
      break;
  }

  
  return cState;
};

int SampleJoystick(int cState){
  const short B_Lim = 450, T_Lim = 650;
  switch(cState){
    case JS_Init:
      cState = JS_TempMode;
      break;
    case JS_TempMode:
      cState = (analogRead(A1) < B_Lim) ? JS_HumidMode : JS_TempMode; //Vertical Direction (Mode Selection)
      break;
    case JS_HumidMode:
      cState = (analogRead(A1) > T_Lim) ? JS_TempMode : JS_HumidMode;
      break;
    default:
      Serial.println("Default Sample JS?");
      cState = JS_TempMode;
      break;
  }

  switch (cState){
    case JS_TempMode:
      if (analogRead(A2) < B_Lim){ 
        TargetTemp -= 1;
      } else if (analogRead(A2) > T_Lim){
        TargetTemp += 1;
      }
      break;
    case JS_HumidMode:
      if (analogRead(A2) < B_Lim){
        TargetHumid -= 1;
      } else if (analogRead(A2) > T_Lim){
        TargetHumid += 1;
      }
      break;
    default:
      Serial.println("Default Sample JS2?");
      cState = JS_TempMode;
      break;
  }

  return cState;
}

