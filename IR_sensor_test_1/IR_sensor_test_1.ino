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
  sendData();
  if(Serial1.available()>0)
  {
//    char data =Serial1.read();
//    String value = String(data);
//    Serial.print(value);
    readSensor();
    showSignalData(); 
  }
}

int readSensor(){
  for(int i=0; i<8; i++)
  {
    signalData[i] = analogRead(signalPins[i]);
  }
}
void sendData(){
  String data;
  data = showSignalData();
  Serial1.write(data.c_str());
}
String showSignalData(){
  String data = "";
  for(int i=0; i<8; i++)
  {
    Serial.print(signalData[i]);
    Serial.print(" ");
    data = data + signalData[i]+ " ";
  }
  Serial.println("");
  data = data + "\n";
  return data;
}
