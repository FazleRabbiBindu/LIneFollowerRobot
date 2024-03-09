const int signalPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int signalData[8];

int motorControl[] = {2,3,4,5,9,10}; //lm1,lm2,rm1,rm2,enA,enB

int readSensor();
String showSignalData();
void sendData();
void Forward();
void Backward();
void Left();
void Right();
void Stop();


void setup() {
Serial.begin(9600);
Serial1.begin(9600);
  for(int i = 0; i<6; i++){
    pinMode(motorControl[i],INPUT) 
  }
}

void loop() {
  readSensor();
  sendData();
  
}




void Forward()
{
  
}
void Backward()
{
  
}
void Left()
{
  
}
void Right()
{
  
}
void Stop()
{
  
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
void sendData(){
  String data;
  data = showSignalData();
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
