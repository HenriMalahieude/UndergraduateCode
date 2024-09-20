/*        Henri Malahieude (hmala001@ucr.edu)
*         Discussion Section:
*         Assignment: Lab #1  Exercise #1
*         Exercise Description: Arduino Introduction, Bit Masking
*        
*         I acknowledge all content contained herein, excluding template or example code, is my own original work.
*
*         Demo Link: https://youtu.be/-zjzl622Njo
*/

char myData[20];
byte myHex[2];

int B[8] = {2,3,4,5,6,7,8,9};

void setup() {

  for(int i = 0; i < 8 ; i++){
    pinMode(B[i],OUTPUT);
  }

  Serial.begin(9600);
}

int getHex()
{
  for (int i = 0; i < 2; i++)
  {
    byte y = myData[i];
    if (y <= 0x39)
    {
      myHex[i] = y - 0x30;
    }
    else
    {
      myHex[i] = y - 0x37;
    }
  }
  return ((unsigned int)(myHex[0] << 4) | (unsigned int)(myHex[1]));
}

unsigned char getBit(unsigned char b, unsigned char p){
  return (b & (0x01 << p)) >> p;
}

void loop() {
  //Get an input
  Serial.print("What is the input A?\n");
  while(Serial.available() == 0){}

  byte m = Serial.readBytesUntil('\n', myData, 20);
  myData[m] = '\0';
  unsigned int reading = getHex();
  Serial.println(reading,HEX);
  Serial.println(reading,BIN);
  Serial.println(reading);
  
  // MY CODE ---------------------------------------------------------------------
  //Display the Binary we inputted
  for (unsigned char i = 0; i < 8; i++){
  	digitalWrite(B[i], (getBit(reading, i) == 1) ? HIGH : LOW);
  }

  //Get the bit we want
  Serial.print("Which bit of A would you like to access?\n(enter a value 0-7)\n");
  while(Serial.available() == 0){}
  
  unsigned char x = Serial.parseInt();
  Serial.println(x);
  Serial.print("masking...\n");
  
  delay(500);
  //Mask them down
  unsigned char chosenOne = getBit(reading, x);
  for (unsigned char i = 0; i < 8; i++){
  	digitalWrite(B[i], LOW);
  }
  digitalWrite(B[x], chosenOne == 1 ? HIGH : LOW);
  delay(500);
  
  for (char i = x-1; i >= 0; i--){
    delay(500);
    digitalWrite(B[i+1], LOW);
  	digitalWrite(B[i], chosenOne == 1 ? HIGH : LOW);
  }
  // END     ---------------------------------------------------------------------
}