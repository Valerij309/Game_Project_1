#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int xD = 0;
int yP = 0;
int Points = 0;
const int numEnemies = 300;     
int xE[numEnemies];            
int yE[numEnemies];            
unsigned long EnemyMove = 2000;   

void setup() {
  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();
  randomSeed(analogRead(3)); 
  resetEnemies();
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("MOVE!!!");
  delay(2000);
}

void loop() {
  xD = analogRead(0);
  
  pers_move();
  move_enemies();
  
  
  for (int i = 0; i < numEnemies; i++) {
    if (xE[i] == 1 && yE[i] == yP) {
      GameOver();
      return; 
    }
  }

  
  lcd.clear();
  
  
  lcd.setCursor(1, yP);
  lcd.print("X");
  
  
  for (int i = 0; i < numEnemies; i++) {
    if (xE[i] >= 0 && xE[i] < 16) {
      lcd.setCursor(xE[i], yE[i]);
      lcd.print("H");
    }
  }
  delay(50); 
}

void pers_move() {
  if (xD > 750) yP = 1;
  if (xD < 250) yP = 0;
}
void move_enemies() {
  if (millis() - EnemyMove >= 400) {
    for (int i = 0; i < numEnemies; i++) {
      xE[i]--; 
      if (xE[i] == 0) {
           Points++;
      }
    }
    EnemyMove = millis();
  }
}
void resetEnemies() {
  for (int i = 0; i < numEnemies; i++) {
    xE[i] = 15 + (i * 5); 
    yE[i] = random(0, 2);
  }
}

void GameOver() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("GAME OVER!");
  lcd.setCursor(4, 1);
  lcd.print("POINTS:");
  lcd.setCursor(11, 1);
  lcd.print(Points);
  tone(12, 1000, 500);
  delay(3000);
  resetEnemies();
  yP = 0;
  Points = 0;
  lcd.clear();
}