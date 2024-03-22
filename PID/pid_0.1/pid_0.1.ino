const int signalPins[] = {A5,A4,A3,A2,A1,A0};

int motorControl[] = {2,3,4,5,9,10};
int signalData[6];
int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 80;

bool cal = true;

float Kp = 70;
float Kd = 120;
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
}

void loop(){
  if(pidError() == 0)
  {
    analogWrite(motorControl[4], 80);
    analogWrite(motorControl[5], 80);
  }else if (pidError() == 10)
  { 
    Stop();
  }
  else{
    lineFollow();
  }
    Forward();


  // if(analogRead(1) < threshold && analogRead(5) > threshold)
  // {
  //   analogWrite(motorControl[4], lfspeed);
  //   analogWrite(motorControl[5], lfspeed);
  //   hardRight();
  // }
  // else if(analogRead(1) > threshold && analogRead(5) < threshold)
  // {
    
  //   analogWrite(motorControl[4], lfspeed);
  //   analogWrite(motorControl[5], lfspeed);
  //   hardLeft();
  // }
  // else if(analogRead(3) < threshold)
  // {
  //   Kp = 0.005 * (1000 - analogRead(3));
  //   Kd = 10 * Kp;
  //   lineFollow();
  //   Forward();
  // }

  // Serial.print(analogRead(1));
  // Serial.print(" ");

  // // Serial.print("two");
  // Serial.print(analogRead(2));
  // Serial.print(" ");

  // // Serial.print("three ");
  // Serial.print(analogRead(3));
  // Serial.print(" ");

  // // Serial.print("four");
  // Serial.print(analogRead(4));
  // Serial.print(" ");

  // // Serial.print("five");
  // Serial.print(analogRead(5) );
  // Serial.print(" ");

}

void lineFollow()
{
  error = pidError();
  

  P = error;
  I = I + error;
  D = error + previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  lsp = lfspeed + PIDvalue;
  rsp = lfspeed - PIDvalue;
  
  lsp = map(lsp, -1295, 1805, 0,100);
  rsp = map(rsp, -1295, 1805, 0,100);
  // constrain(lsp,0,255);
  // constrain(rsp,0,255);

  analogWrite(motorControl[4], lsp);
  analogWrite(motorControl[5], rsp);
  Serial.print("lsp: ");
  Serial.print(lsp);
  Serial.print("rsp: ");
  Serial.print(rsp);
  Serial.print(" errror: ");
  Serial.println(error);

}

int readSensor() {
  for(int s=0; s<6; s++) {
    if(analogRead(signalPins[s])>450) {
      signalData[s] = 0;
      }else {
      signalData[s] = 1;
    }
    }
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

int pidError(){
  readSensor();

  if(signalData[0] == 1 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = -5;
  }
  else if(signalData[0] == 1 && signalData[1] == 1 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0)
  {
    error =-4;
  }
  else if(signalData[0] == 0 && signalData[1] == 1 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = -3;
  }
    else if(signalData[0] == 0 && signalData[1] == 1 && signalData[2] == 1 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = -2;
  }
  else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 1 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = -1;
  }
    else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 1 && signalData[3] == 1 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = 0;
  }
  else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 1 && signalData[4] == 0 && signalData[5] == 0)
  {
    error = 1;
  }
    else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 1 && signalData[4] == 1 && signalData[5] == 0)
  {
    error = 2;
  }
  else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 1 && signalData[5] == 0)
  {
    error = 3;
  }
    else if(signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 1 && signalData[5] == 1)
  {
    error = 4;
  }
  else if (signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 1)
  {
    error = 5;
  }
  else if (signalData[0] == 0 && signalData[1] == 0 && signalData[2] == 0 && signalData[3] == 0 && signalData[4] == 0 && signalData[5] == 0) 
  {
    error = 10;
  }
  // else{ error = 10;}
  // Serial.print("Error: ");
  // Serial.println(error);
  return error;
}

void hardLeft()
{
  analogWrite(motorControl[4], 100);
  analogWrite(motorControl[5], 150);
  
  // Right
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
   // Left
  digitalWrite(motorControl[2], HIGH);
  digitalWrite(motorControl[3], LOW);
  // Full speed
  Serial.println("going left");
}

void hardRight()
{
  analogWrite(motorControl[4], 150);
  analogWrite(motorControl[5], 100);

  // Right motor
  digitalWrite(motorControl[0], HIGH);
  digitalWrite(motorControl[1], LOW);
   // Left
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
  // Full speed

  Serial.println("going right");
}

void Forward()
{
 Serial.println("");
 Serial.print("Forward "); 

  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
}

void Stop(){
digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], LOW);
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], LOW);

}