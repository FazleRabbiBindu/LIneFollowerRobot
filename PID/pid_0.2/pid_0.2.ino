const int signalPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int signalData[8];
int flag=0;

int motorControl[] = {2,3,4,5,9,10}; //lm1,lm2,rm1,rm2,enA,enB

// int P, D, I, previousError, PIDvalue, error;
// int lsp, rsp;
// int lfspeed = 200;

// bool cal = true;

// float Kp = 0;
// float Kd = 0;
// float Ki = 0;

int readSensor();
String showSignalData();
void sendData();
void Forward();
void Backward();
void softLeft();
void hardLeft();
void softRight();
void hardRight();
void Stop();
void Search();


void setup() {
Serial.begin(9600);
Serial1.begin(9600);
  for(int i = 0; i<6; i++){
    pinMode(motorControl[i],OUTPUT);
  }
    analogWrite(motorControl[4],80);
    analogWrite(motorControl[5],80);
}

void loop() {
  int sum;
  readSensor();
  // sendData(showSignalData());
  Serial.println(digitalDataConvertion());
  sum= digitalDataConvertion();

  Logic(sum);
  
}




void Forward()
{
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
}
void Backward()
{
  digitalWrite(motorControl[0], HIGH);
  digitalWrite(motorControl[1], LOW);
   // Full speed
  digitalWrite(motorControl[2], HIGH);
  digitalWrite(motorControl[3], LOW);
}
void softLeft()
{  
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], LOW);
  // Full speed
}
void hardLeft()
{
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], HIGH);
   // Full speed
  digitalWrite(motorControl[2], HIGH);
  digitalWrite(motorControl[3], LOW);
  // Full speed
}
void softRight()
{
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], LOW);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
  // Full speed
}
void hardRight()
{
  digitalWrite(motorControl[0], HIGH);
  digitalWrite(motorControl[1], LOW);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], HIGH);
  // Full speed
}
void Stop()
{
  digitalWrite(motorControl[0], LOW);
  digitalWrite(motorControl[1], LOW);
   // Full speed
  digitalWrite(motorControl[2], LOW);
  digitalWrite(motorControl[3], LOW);
}


int readSensor(){
  for(int i=0; i<8; i++)
  {
    if(analogRead(signalPins[i])>250)
    {
      signalData[i] = 1;      
    }
    else
    {
      signalData[i] = 0;
    }

  }
}
void sendData(String data){
  data = data+"\n";
  Serial.print(data);
  Serial1.write(data.c_str());
}
String showSignalData(){
  String data = "";
  for(int i=7; i>=0; i--)
  {
    Serial.print(signalData[i]);
    Serial.print(" ");
    data = data + signalData[i]+ " ";
  }
  Serial.println("");
  data = data + "\n";
  return data;
}

int digitalDataConvertion(){
  readSensor();

  return ((signalData[0]*1)+(signalData[1]*2)+(signalData[2]*4)+(signalData[3]*8)+(signalData[4]*16)+(signalData[5]*32)+(signalData[6]*64)+(signalData[7]*128));

}

void Logic(int sum){
  if(sum==199||sum==231 ||sum==227||sum==243||sum==207){
    flag=0;
    sendData("Forward Logic");
    Forward();
  }else if(sum==241||sum==249||sum==248){
    sendData("Soft Right L");
    if(sum==199||sum==231 ||sum==227||sum==243||sum==207){
      Forward();
    }
    else{
    hardRight();
    }
    // delay(100);
  }else if(sum==254||sum==252||sum==240){
    flag=1;
    sendData("Hard Right L");
     if(sum==199||sum==231 ||sum==227||sum==243||sum==207){
      Forward();
    }
    else{
    softRight();
    }
    // softRight();
    // delay(100);
  }else if(sum==31||sum==159||sum==143){
    sendData("Soft Left L");
    if(sum==199||sum==231 ||sum==227||sum==243||sum==207){
      Forward();
    }
    else{
    // softRight();
    hardLeft();
    }
    // delay(100);
  }else if(sum==127||sum==63||sum==15){
    flag=-1;
    sendData("Hard Left L");
    if(sum==199||sum==231 ||sum==227||sum==243||sum==207){
      Forward();
    }
    else{
    softLeft();
    }
  }else if(sum==255){
    sendData("Search");
    Search();
  }
  else if(sum == 0)
  {
    Stop();
    Forward();
    delay(500);
  }
  else{
    // Stop();
    Search();
  }
}
void Search()
{
  if(flag==1){
    hardRight();
  }else if(flag==-1){
    hardLeft();
  }else{
    Stop();
  }
}
