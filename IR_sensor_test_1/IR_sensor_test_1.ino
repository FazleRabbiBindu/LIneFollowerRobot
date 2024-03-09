const int signalPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int signalData[8];

int readSensor();
void showSignalData();

void setup() {
Serial.begin(9600);
}

void loop() {
  readSensor();
  showSignalData();

}

int readSensor(){
  for(int i=0; i<8; i++)
  {
    signalData[i] = analogRead(signalPins[i]);
  }
}

void showSignalData(){
  for(int i=0; i<8; i++)
  {
    Serial.print(signalData[i]);
    Serial.print(" ");
  }
  Serial.println("=>");
}
