const int signalPins[] = {A2,A3,A4,A5,A6};
int signalData[8];

int motorControl[] = {2,3,4,5,A7,A8};

int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 200;

bool cal = true;

float Kp = 0;
float Kd = 0;
float Ki = 0;

int thershold = 450;

int minValues[6], maxValues[6], threshold[6];

void setup() {
  Serial.begin(9600);
  for(int i = 0; i<6; i++) {
    pinMode(signalPins[i],INPUT);
  }
  for(int i = 0; i<6; i++) {
    pinMode(motorControl[i],OUTPUT);
  }

  analogWrite(motorControl[4], lfspeed);
  analogWrite(motorControl[5], lfspeed);
}

void loop(){

  if(analogRead(1) < threshold && analogRead(5) > threshold)
  {
    hardRight();
  }
  else if(analogRead(1) > threshold && analogRead(5) < threshold)
  {
    hardLeft();
  }
  else if(analogRead(3) < threshold)
  {
    Kp = 0.005 * (1000 - analogRead(3));
    Kd = 10 * Kp;
    lineFollow();
  }
  Serial.print("one");
  Serial.println(analogRead(1));

  Serial.print("two");
  Serial.println(analogRead(2));

  Serial.print("three ");
  Serial.println(analogRead(3));

  Serial.print("four");
  Serial.println(analogRead(4));

  Serial.print("five");
  Serial.println(analogRead(5) );

}

void lineFollow()
{
  int error = (analogRead(2) - analogRead(4));



  P = error;
  I = I + error;
  D = error + previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  if(lsp > 255) {
    lsp = 255;
  }
  if(lsp < 0) {
    lsp = 0;
  }
  if(rsp > 255) {
    rsp = 255;
  }
  if(rsp < 0) {
    rsp = 0;
  }
  analogWrite(7, lsp);
  analogWrite(8, rsp);
  Forward();

}

int readSensor() {
  for(int i=0; i<8; i++) {
    // if(analogRead(signalPins[i])>250) {
      signalData[i] = analogRead(signalPins[i]);
    // }else {
    //   signalData[i] = 0;
    // }
  }
  Serial.println(readSensor());
}

void calibration() {
  for (int i=1; i<6; i++) {
    minValues[i] = analogRead(i);
    maxValues[i] = analogRead(i);
  }

  for(int i=0; i<3000; i++) {
    hardLeft();

    for(int i = 1; i<6; i++) {
      if(analogRead(i) < minValues[i])
      {
        minValues[i] = analogRead(i);
      }
      if(analogRead(i) > maxValues[i])
      {
        maxValues[i] = analogRead[i];
      }
    }
  }
  
  for (int i = 1; i<6; i++)
  {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print(threshold[i]);
    Serial.print("  ");
  }
  Serial.println();
}

void hardLeft()
{
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
   // Full speed
  digitalWrite(motorControl[2], HIGH);
  digitalWrite(motorControl[3], LOW);
  // Full speed
  Serial.println("going left");
}

void hardRight()
{
  digitalWrite(motorControl[0], HIGH);
  digitalWrite(motorControl[1], LOW);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
  // Full speed

  Serial.println("going right");
}

void Forward()
{
  

  analogWrite(motorControl[4], LOW);
  analogWrite(motorControl[5], HIGH);

  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);

  Serial.println("");
 Serial.print("Forward ");
 Serial.print(lsp);
 Serial.print(" ");
 Serial.println(rsp);
}