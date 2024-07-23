const int analogInPin = A0; // Analog
const int analogInPin1 = A1; // Analo
int sensorValue = 0; // value read fr
int sensorValue1 = 0; // value read f

void setup() {
// put your setup code here, to run on
Serial.begin(9600);
}

void loop() {
 sensorValue = analogRead(analogInPin);
sensorValue1 = analogRead(analogInPin);
Serial.print(sensorValue);
Serial.print(",");
Serial.print("2");
Serial.print(",");
Serial.println(sensorValue1);
delay(500);
}