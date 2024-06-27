void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(9)==HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");
}
