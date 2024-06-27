
const int trig_pin = 6;
const int echo_pin = 5;
short int time;
float distance;
void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(11, OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  time = pulseIn(echo_pin, HIGH);
  distance = time * 0.0343 / 2.0;
  Serial.println(distance);
  if (distance < 50 && distance > 5)
  {
    digitalWrite(11,HIGH);
    digitalWrite(8,HIGH);
    //analogWrite(11, 1000 / distance);
  }
  else if (distance<100 && distance>50)
  {
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
    delay(300);
    digitalWrite(8,LOW);
    delay(300);

  }
}
