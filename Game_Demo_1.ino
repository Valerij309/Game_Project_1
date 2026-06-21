#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int xD = 0;
int yP = 0;
int yE = 0;
bool spawn_position = 1;
int xE = 15;
unsigned long EnemyMove = 0;
unsigned long TimerSpawmEnemy = 0;

void setup() {
  lcd.init();                     
  lcd.init();
  lcd.backlight();
  randomSeed(analogRead(3)); 
  
}

void loop() {
  xD = analogRead(0);
  lcd.clear();
  pers_move();
  Serial.println(xD);
  enemy_spawn(xE,yE);
  if(xE == 1 && yE == yP){
     GameOver();
  }
}
void pers_move(){
  lcd.setCursor(1,yP);
  lcd.print("X");
  if(xD > 750){
    yP = 1;
  }
  if(xD < 250){
    yP = 0;
  }
  if(xE == 0){
    xE = 15;
    yE= random(0,2);
  }
}
void enemy_move(){
  if(millis() - EnemyMove >= 400){
    xE--;
    EnemyMove = millis();
  }
}
void enemy_spawn(int xE,int yE){
  lcd.setCursor(xE,yE);
  lcd.print("H");
  enemy_move();
}
void GameOver(){
  tone(12,1000,500);
  delay(2000);
  return;
}