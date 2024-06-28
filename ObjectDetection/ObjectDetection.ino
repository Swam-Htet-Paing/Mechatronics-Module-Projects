#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
short int relay = 8;
short int onTrack = 0;
short int total = 0;
short int IR1 = 9;
short int IR2 = 11;
short int trigPin = 11;
short int echoPin = 5;
long duration;
float distance;
float Swam_Htet_Paing;

float getDistance();

void setup()
{
  pinMode(trigPin, OUTPUT); // Trigger pin
  pinMode(echoPin, INPUT); // Echo pin
  pinMode(relay, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
  // Check IR1 sensor
  if (digitalRead(IR1) == LOW)
  {
    onTrack += 1;
    delay(1000);
  }

  // Check distance from ultrasonic sensor
  Swam_Htet_Paing = getDistance();
  if (Swam_Htet_Paing >= 5 && Swam_Htet_Paing <= 15)
  {
    delay(1000);
    onTrack -= 1;
    total += 1;
  }

  // Control relay
  if (onTrack != 0)
    digitalWrite(relay, HIGH);
  else
    digitalWrite(relay, LOW);

  // Update LCD display
  lcd.setCursor(0, 0);
  lcd.print("On track:");
  lcd.setCursor(9, 0);
  lcd.print(onTrack);
  lcd.setCursor(0, 1);
  lcd.print("Total:");
  lcd.setCursor(9, 1);
  lcd.print(total);

  // Debugging info
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(500); // Add a small delay to prevent rapid looping
}

float getDistance()
{
  // Send a 10 microsecond pulse to trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin, return distance in cm
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2;
  return distance;
}
