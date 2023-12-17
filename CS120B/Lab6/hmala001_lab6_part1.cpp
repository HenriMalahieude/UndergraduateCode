/*         Your Name & E-mail: Henri Malahieude (hmala001@ucr.edu)
 *         Discussion Section: 23
 *         Assignment: Lab #6  Exercise #1
 *         Exercise Description: Speedrun 2047
 *        
 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *
 *         Demo Link: https://youtu.be/nokuhD3Nv1w
*/
#define WATER_LVL A0
#define ICE_LVL A1

#define YELLOW 2
#define BLUE 3
#define RED 4
#define WHITE 5
#define GREEN 6

//int b_size = 5;
//int b[b_size] = {2, 3, 4, 5, 6}; //Y, B, R, W, G

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
bool pause = false;
const unsigned short tasksNum = 6;
task tasks[tasksNum];

enum PWM_States {PWM_Init = 0, PWM_High, PWM_Low, PWM_Pause, PWM_Off};

short WaterSensor = 0, IceSensor = 0;
int Water_Tick(int cState);
int Ice_Tick(int cState);

//Water Pump PWM
const short waterPeriod = 300;
const char w_h = 1, w_l = 4; //20% Duty Cycle
unsigned short waterTime = 0; //ms
int SM1_Tick(int cState);

//Nitrogen Pump PWM
const short nitroPeriod = 500;
const char n_h = 7, n_l = 3; //70% Duty Cycle
unsigned short nitroTime = 0; //ms
int SM2_Tick(int cState);

//Dispenser PWM
const short dispenserPeriod = 100;
const char d_h = 1, d_l = 9; //10% Duty Cycle
unsigned short dispenserTime = 0; //ms
int SM3_Tick(int cState);

//Main Controller
enum Mngr_States {MNGR_Init = 0, MNGR_Off, MNGR_WaterLow, MNGR_IceHigh, MNGR_FlowWater1, MNGR_PumpNitro2, MNGR_Dispense3};
int SM4_Tick(int cState);

void setup() {
   delay_gcd = 10; // GCD

  // put your setup code here, to run once:
  unsigned char i = 0;
  tasks[i].state = PWM_Init;
  tasks[i].period = waterPeriod / 5;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = PWM_Init;
  tasks[i].period = nitroPeriod / 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = PWM_Init;
  tasks[i].period = dispenserPeriod / 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  i++;
  tasks[i].state = MNGR_Init;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;
  i++;
  tasks[i].state = 0;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Water_Tick;
  i++;
  tasks[i].state = 0;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Ice_Tick;

  Serial.begin(9600);
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}

int Water_Tick(int cState){
  WaterSensor = analogRead(WATER_LVL);
}

int Ice_Tick(int cState){
  IceSensor = analogRead(ICE_LVL);
}

int PWM_Meta(int cState, short pwmPeriod, unsigned short *time, unsigned char pin, unsigned char *cnt, char high, char low){
  short timeDrop = pwmPeriod; //Amount to drop per Complete H/L Cycle

  //States
  switch(cState){
    case PWM_Init:
      cState = PWM_Off;
      break;
    case PWM_High:
      (*cnt) += 1;
      if (*cnt > high) cState = PWM_Low;
      if (pause) cState = PWM_Pause;
      break;
    case PWM_Low:
      (*cnt) += 1;
      if (*cnt > (high+low)){
        (*time) -= timeDrop;
        *cnt = 0;
        cState = (*time <= 0) ? PWM_Off : PWM_High;
        break;
      }
      if (pause) cState = PWM_Pause;
      break;
    case PWM_Pause:
      if (!pause){
        if (*time == 0){
          *cnt = 0;
          cState = PWM_Off;
        } else if (*cnt < high){
          cState = PWM_High;
        }else{
          cState = PWM_Low;
        }
      }
      break;
    case PWM_Off:
      if (*time > 0) cState = PWM_High;
      break;
    default:
      cState = PWM_Off;
      break;
  }

  //Actions
  switch (cState){
    case PWM_Off:
      digitalWrite(pin, LOW);
      break;
    case PWM_High:
      digitalWrite(pin, HIGH);
      break;
    case PWM_Low:
      digitalWrite(pin, LOW);
      break;
    case PWM_Pause:
      digitalWrite(pin, LOW);
      break;
    default:
      break;
  }

  return cState;
}

//Water Pump
int SM1_Tick(int cState1){
  static char cnt = 0;
  return PWM_Meta(cState1, waterPeriod, &waterTime, BLUE, &cnt, w_h, w_l);
}

//Nitrogen Pump
int SM2_Tick(int cState2){
  static char cnt = 0;
  return PWM_Meta(cState2, nitroPeriod, &nitroTime, WHITE, &cnt, n_h, n_l);
}

//Dispenser PWM
int SM3_Tick(int cState3){
  static char cnt = 0;
  return PWM_Meta(cState3, dispenserPeriod, &dispenserTime, GREEN, &cnt, d_h, d_l);
}

//Global Manager
int SM4_Tick(int cState4){
  const short coveredWat = 40;
  const short coveredIce = 30;

  //States
  switch (cState4){
    case MNGR_Init:
      cState4 = MNGR_Off;
      break;
    case MNGR_Off:
      pause = true;
      if (!(WaterSensor < coveredWat && IceSensor < coveredIce)){
        cState4 = MNGR_FlowWater1;
        waterTime = 3000;
        nitroTime = 0; dispenserTime = 0;
        pause = false;
      }else if (WaterSensor < coveredWat){
        cState4 = MNGR_WaterLow;
      }else{
        cState4 = MNGR_IceHigh;
      }
      break;
    case MNGR_FlowWater1:
      if (WaterSensor < coveredWat){
        pause = true;
        cState4 = MNGR_WaterLow;
      } else if (IceSensor < coveredIce){
        pause = true;
        cState4 = MNGR_IceHigh;
      }
      if (waterTime <= 0 && cState4 != MNGR_IceHigh){
        cState4 = MNGR_PumpNitro2;
        nitroTime = 5000;
        waterTime = 0; dispenserTime = 0;
      }
      break;
    case MNGR_PumpNitro2:
      if (IceSensor < coveredIce){
        pause = true;
        cState4 = MNGR_IceHigh;
      }
      if (nitroTime <= 0){
        cState4 = MNGR_Dispense3;
        dispenserTime = 2000;
        waterTime = 0; nitroTime = 0;
      }
      break;
    case MNGR_Dispense3:
      if (IceSensor < coveredIce){
        pause = true;
        cState4 = MNGR_IceHigh;
      }else if (dispenserTime <= 0){
        cState4 = MNGR_FlowWater1;
        waterTime = 3000;
        nitroTime = 0; dispenserTime = 0;
      }
      break;
    case MNGR_WaterLow:
      pause = true;
      digitalWrite(RED, HIGH);
      if (IceSensor < coveredIce){
        digitalWrite(RED, LOW);
        cState4 = MNGR_Off;
      }
      if (WaterSensor >= coveredWat){
        digitalWrite(RED, LOW);
        pause = false;
        if (waterTime > 0){
          cState4 = MNGR_FlowWater1;
          nitroTime = 0; dispenserTime = 0;
        } else if (nitroTime > 0){
          cState4 = MNGR_PumpNitro2;
          waterTime = 0; dispenserTime = 0;
        } else {
          cState4 = MNGR_Dispense3;
          waterTime = 0; nitroTime = 0;
        }
      }
      break;
    case MNGR_IceHigh:
      pause = true;
      digitalWrite(YELLOW, HIGH);
      if (WaterSensor < coveredWat){
        digitalWrite(YELLOW, LOW);
        cState4 = MNGR_Off;
      }
      if (IceSensor >= coveredIce){
        digitalWrite(YELLOW, LOW);
        pause = false;
        if (waterTime > 0){
          cState4 = MNGR_FlowWater1;
          nitroTime = 0; dispenserTime = 0;
        } else if (nitroTime > 0){
          cState4 = MNGR_PumpNitro2;
          waterTime = 0; dispenserTime = 0;
        } else {
          cState4 = MNGR_Dispense3;
          waterTime = 0; nitroTime = 0;
        }
      }
      break;
    default:
      cState4 = MNGR_Off;
      break;
  }
  return cState4;
}