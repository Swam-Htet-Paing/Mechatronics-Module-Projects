#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
short int relay = 8;
short int onTrack = 0;
short int total = 0;
short int IR1 = 9;
short int IR2 = 11;

void setup() {
  //Relay, I2C communication with LCD and IR sensor pins are set up
  pinMode(relay, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  lcd.init();   
  lcd.backlight();
}

void loop() {
  // number of object on the convayer belt (onTrack) increases by 1 if IR1 is HIGH
  if(digitalRead(IR1) == 1)
    onTrack += 1;
  //number of object moved is increased by 1 and that of object on the belt is decreased by 1 if IR2 is HIGH  
  if(digitalRead(IR2) == 1){
    onTrack -= 1;
    total += 1;
  }
  //As long as there are objects on the belt (i.e. onTrack isn't zero, the belt motor must be powered on)
  if(onTrack != 0)
    digitalWrite(relay, HIGH);
  //When there's no object on the belt anymore, the belt motor is stopped.
  else if(onTrack == 0)
    digitalWrite(relay, LOW);
  //handles the display process on the LCD
  lcd.setCursor(0,0);
  lcd.print("On track:");
  lcd.setCursor(8,0);
  lcd.print(String(onTrack));
  lcd.setCursor(1,0);
  lcd.print("Total:");
  lcd.setCursor(8,0);
  lcd.print(String(total));
}
