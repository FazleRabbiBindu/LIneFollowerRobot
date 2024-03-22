
#define motorL1 2
#define motorL2 3

#define INA 9


void setup() {
  Serial.begin(9600);

  pinMode(motorL1,OUTPUT);
  pinMode(motorL2,OUTPUT);
  pinMode(INA,OUTPUT);

}

void loop() {
  // speedControlTest('h');
  speedControlTest('a');
  // speedControlTest('l');



}

void speedControlTest(char state){
  switch (state){
    case 'a':
      for(int i=0; i<256; i++)
      {
        analogWrite(INA, i);
        delay(20);
      }
      break;
    case 'h':
      analogWrite(INA, HIGH);
      break;
    case 'l':
      analogWrite(INA, LOW);
      break;
  }
      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);

}

