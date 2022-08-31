#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int buttonPin=2;
int w_display=1;
int gameover=1;
int score=0;
int best_score=0;
int w_init=1;
int g_init=1;
int gg_init=1;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  if(w_display)
  {
    if(w_init)
    {
      lcd.clear();
      w_init=0;
      lcd.setCursor(0,0);
      lcd.print("-dino game-");
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("best score:");
      lcd.setCursor(11,1);
      lcd.print(best_score);
    }
    int buttonState;
    buttonState=digitalRead(buttonPin);
    
    if(buttonState==LOW)
    {
      w_display=0;
      gameover=1;
      score=0;
      g_init=1;
    }
  }
  else if(gameover)
  {
    if(g_init)
    {
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.print("3");
      delay(1000);
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.print("2");
      delay(1000);
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.print("1");
      delay(1000);
      lcd.clear();
      g_init=0;
    }
    for(int i=15;i>=0;i--)
    {
      if(!(score/10))
      {
        lcd.setCursor(15,0);
        lcd.print(score);
      }else
      {
        lcd.setCursor(14,0);
        lcd.print(score);
      }
      int buttonState;
      buttonState=digitalRead(buttonPin);
      if(buttonState==LOW)
      {
         for(int j=i;j>i-3;j--)
        {
          Serial.println(j);
          lcd.setCursor(7,1);
          lcd.print("");
          lcd.setCursor(7,0);
          lcd.print("P");
          lcd.setCursor(j,1);
          lcd.print("o");
          delay(100-(score/10)*5);
          lcd.clear();
        }
        i-=3;
        //key=' ';
        lcd.setCursor(i,1);
        lcd.print("o");
      }
      else
      {
        lcd.setCursor(7,0);
        lcd.print("");
        lcd.setCursor(7,1);
        lcd.print("P");
        lcd.setCursor(i,1);
        lcd.print("o");
        if(i==7)
        {
          gameover=0;
          gg_init=1;
          break;
        }
      }
      delay(100-(score/10)*5);
      lcd.clear();
    }
    score++;
  }
  else
  {
    if(gg_init)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("-gameover-");
      delay(300);
      lcd.setCursor(0,1);
      lcd.print("Score:");
      lcd.setCursor(6,1);
      lcd.print(--score);
      delay(500);
      if(score>best_score)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("New high score");
        lcd.setCursor(0,1);
        lcd.print("score:");
        lcd.setCursor(6,1);
        lcd.print(score);
        best_score=score;
      }
      gg_init=0;
    }
    int buttonState;
    buttonState=digitalRead(buttonPin);
    if(buttonState==LOW)
    {
      w_init=1;
      w_display=1;
    }
  }
}
