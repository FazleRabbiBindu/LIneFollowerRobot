const int signalPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int signalData[8];

int readSensor();
String showSignalData();
void sendData();

void setup() {
Serial.begin(9600);
Serial1.begin(9600);
}

void loop() {
  readSensor();
  sendData();
  
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
