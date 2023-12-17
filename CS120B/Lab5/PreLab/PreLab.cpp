int c = 0;
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

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int); //Function Pointer, point to a function... Pretty handy, pair this with a lambda function in C++ and things get toasty
    
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

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

enum SM1_States { SM1_INIT, SM1_S0};
int SM1_Step_Index = 0;
int SM1_Tick(int state1){
    switch(state1){ // State transitions
      case SM1_INIT:
        state1 = SM1_S0;
        break;
      case SM1_S0:
        (SM1_Step_Index == 7) ? SM1_Step_Index = 0 : SM1_Step_Index++; //increase the action we wanna show
        state1 = SM1_S0;
        break;
    }
    switch(state1){ // State Action
      case SM1_INIT:
        break;
      case SM1_S0:
        writeStepper(SM1_Step_Index);
        break;
    }

    return state1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  unsigned char task_index = 0; 
  tasks[task_index].state = SM1_INIT;
  tasks[task_index].period = 1;
  tasks[task_index].elapsedTime = 0;
  tasks[task_index].TickFct = &SM1_Tick; //give it the address to that function, BOOM, you can now access that specific function
  task_index++; //needed if we had a second task/state-machine
  //tasks[i].state = etc;
  //etc

  Serial.begin(9600);
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Update when the last time this task was ran
     }
   }

  Serial.print(analogRead(A0));
  Serial.print(", ");
  Serial.println(analogRead(A1));
}