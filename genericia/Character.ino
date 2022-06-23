#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int potPin1 = 17;
int potPin2 = 16;
int potPin3 = 15;
int potPin4 = 20;
int potPin5 = 21;

int analogValue1 = 0;
int analogValue2 = 0;
int analogValue3 = 0;
int analogValue4 = 0;
int analogValue5 = 0;
int roll1 = 0;
int roll2 = 0;
int rollFlag = 0;
int deathFlag = 0;

int menuVert = 1;
int menuHorz = 1;
int menuSelect = 1;

char charName[16] = "Bilbo Baggins";
char type[16] = "Rogue";
char weapons[16] = "Twin daggers";
char armor[16] = "Leather armor";
char lightAtt[16] = "Stabby";
char heavyAtt[16] = "Extra Stabby";
char support[16] = "*POOF*";

int atk = 10;
int dfd = 10;
int sup = 10;
int gold = 250;
int lightDam = 1;
int lightCost = 1;
int heavyDam = 3;
int heavyCost = 5;
int supportCost = 3;
int weaponDam = 2;
int armorProtect = 2;
int maxHP;
int currentHP;
int maxMana;
int currentMana;
int foeAtk;
int foeDfd;
int foeSup;
int foeHP;
int foeMana;
int foeWeapon;
int foeArmor;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(14));
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setBacklight(WHITE);

  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);
  pinMode(potPin4, INPUT);
  pinMode(potPin5, INPUT);

  maxHP = dfd * 5;
  currentHP = maxHP;
  maxMana = sup * 5;
  currentMana = maxMana;
}

void loop() {
  uint8_t buttons = lcd.readButtons();
  
  analogValue1 = analogRead(potPin1);
  analogValue2 = analogRead(potPin2);
  analogValue3 = analogRead(potPin3);
  analogValue4 = analogRead(potPin4);
  analogValue5 = analogRead(potPin5);

  if(currentHP > 0){
    buttonPress(buttons);
    show(analogValue1, analogValue2, analogValue3, analogValue4, analogValue5);
  }

  else{
    if(deathFlag == 0){
      lcd.setBacklight(RED);
      lcd.setCursor(0, 0); lcd.print("You have");
      lcd.setCursor(0, 1); lcd.print("died.");
    }

    else{
      lcd.clear();
      deathFlag = 0;
    }
  }
}

int buttonPress(int b){
  if (b){
    if (b & BUTTON_UP){
      lcd.clear();
      menuHorz = 1;
      if(menuSelect == 2){
        menuSelect = 1;
      }
      
      if(menuVert == 1){
        menuVert = 4;
      }

      else{
        menuVert --;
      }
    }

    if(b & BUTTON_DOWN){
      lcd.clear();
      menuHorz = 1;
      if(menuSelect == 2){
        menuSelect = 1;
      }

      if(menuVert == 4){
        menuVert = 1;
      }

      else{
        menuVert ++;
      }
    }

    if(b & BUTTON_LEFT){
      lcd.clear();
      if(menuSelect == 2){
        menuSelect = 1;
      }

      if(menuHorz == 1){
        menuHorz = 4;
      }

      else{
        menuHorz --;
      }
    }

    if(b & BUTTON_RIGHT){
      lcd.clear();
      if(menuSelect == 2){
        menuSelect = 1;
      }

      if(menuHorz == 4){
        menuHorz = 1;
      }

      else{
        menuHorz ++;
      }
    }

    if(b & BUTTON_SELECT){
      lcd.clear();
      menuSelect = 2;
      roll1 = random(25);
      roll2 = random(25);
      rollFlag = 1;
    }
  }

  delay(250);
}

void show(int ana1, int ana2, int ana3, int ana4, int ana5){
  //the great menu display of all the lovely info.
  if(menuSelect == 2){
    actions();
    return;
  }

  switch(menuVert){
    case 1:
    if(menuHorz == 1){
      lcd.setBacklight(WHITE);
      lcd.setCursor(0, 0); lcd.print("Character");
    }

    else if(menuHorz == 2){
      lcd.setCursor(0, 0); lcd.print(charName);
      lcd.setCursor(0, 1); lcd.print(type);
    }

    else if(menuHorz == 3){
      lcd.setCursor(0, 0); lcd.print("ATK   DFD   SUP");
      lcd.setCursor(0, 1); lcd.print(atk);
      lcd.setCursor(6, 1); lcd.print(dfd);
      lcd.setCursor(12, 1); lcd.print(sup);
    }

    else if(menuHorz == 4){
      lcd.setCursor(0, 0); lcd.print("HP");
      lcd.setCursor(8, 0); lcd.print("Mana");
      
      if(maxHP < 10){
        lcd.setCursor(0, 1); lcd.print(currentHP);
        lcd.setCursor(1, 1); lcd.print("/");
        lcd.setCursor(2, 1); lcd.print(maxHP);
      }

      else if(maxHP < 100){
        if(currentHP < 10){
          lcd.setCursor(0, 1); lcd.print(currentHP);
          lcd.setCursor(1, 1); lcd.print("/");
          lcd.setCursor(2, 1); lcd.print(maxHP);
        }

        else{
          lcd.setCursor(0, 1); lcd.print(currentHP);
          lcd.setCursor(2, 1); lcd.print("/");
          lcd.setCursor(3, 1); lcd.print(maxHP);
        }
      }

      else{
        if(currentHP < 10){
          lcd.setCursor(0, 1); lcd.print(currentHP);
          lcd.setCursor(1, 1); lcd.print("/");
          lcd.setCursor(2, 1); lcd.print(maxHP);
        }

        else if(currentHP < 100){
          lcd.setCursor(0, 1); lcd.print(currentHP);
          lcd.setCursor(2, 1); lcd.print("/");
          lcd.setCursor(3, 1); lcd.print(maxHP);
        }

        else{
          lcd.setCursor(0, 1); lcd.print(currentHP);
          lcd.setCursor(3, 1); lcd.print("/");
          lcd.setCursor(4, 1); lcd.print(maxHP);
        }
      }

      
      if(maxMana < 10){
        lcd.setCursor(8, 1); lcd.print(currentMana);
        lcd.setCursor(9, 1); lcd.print("/");
        lcd.setCursor(10, 1); lcd.print(maxMana);
      }

      else if(maxMana < 100){
        if(currentMana < 10){
          lcd.setCursor(8, 1); lcd.print(currentMana);
          lcd.setCursor(9, 1); lcd.print("/");
          lcd.setCursor(10, 1); lcd.print(maxMana);
        }

        else{
          lcd.setCursor(8, 1); lcd.print(currentMana);
          lcd.setCursor(10, 1); lcd.print("/");
          lcd.setCursor(11, 1); lcd.print(maxMana);
        }
      }

      else{
        if(currentMana < 10){
          lcd.setCursor(8, 1); lcd.print(currentMana);
          lcd.setCursor(9, 1); lcd.print("/");
          lcd.setCursor(10, 1); lcd.print(maxMana);
        }

        else if(currentMana < 100){
          lcd.setCursor(8, 1); lcd.print(currentMana);
          lcd.setCursor(10, 1); lcd.print("/");
          lcd.setCursor(11, 1); lcd.print(maxMana);
        }

        else{
          lcd.setCursor(8, 1); lcd.print(currentMana);
          lcd.setCursor(11, 1); lcd.print("/");
          lcd.setCursor(12, 1); lcd.print(maxMana);
        }
      }
    }

    break;

    case 2:
    lcd.setBacklight(GREEN);
    if(menuHorz == 1){
      lcd.setCursor(0, 0); lcd.print("Items");
    }

    else if(menuHorz == 2){
      lcd.setCursor(0, 0); lcd.print(weapons);
      lcd.setCursor(0, 1); lcd.print("Damage");
      if(weaponDam < 10){
        lcd.setCursor(15, 1); lcd.print(weaponDam);
      }

      else{
        lcd.setCursor(14, 1); lcd.print(weaponDam);
      }
    }

    else if(menuHorz == 3){
      lcd.setCursor(0, 0); lcd.print(armor);
      lcd.setCursor(0, 1); lcd.print("Protection");
      if(armorProtect < 10){
        lcd.setCursor(15, 1); lcd.print(armorProtect);
      }

      else{
        lcd.setCursor(14, 1); lcd.print(armorProtect);
      }
    }

    else if(menuHorz == 4){
      lcd.setCursor(0, 0); lcd.print(gold);
      lcd.setCursor(12, 1); lcd.print("Gold");
    }

    break;

    case 3:
    lcd.setBacklight(BLUE);
    if(menuHorz == 1){
      lcd.setCursor(0, 0); lcd.print("Actions");
    }

    else if(menuHorz == 2){
      lcd.setCursor(0, 0); lcd.print(lightAtt);
      lcd.setCursor(0, 1); lcd.print(lightDam);
      lcd.setCursor(11, 1); lcd.print("Mana");
      lcd.setCursor(9, 1); lcd.print(lightCost);
    }

    else if(menuHorz == 3){
      lcd.setCursor(0, 0); lcd.print(heavyAtt);
      lcd.setCursor(0, 1); lcd.print(heavyDam);
      lcd.setCursor(11, 1); lcd.print("Mana");
      lcd.setCursor(9, 1); lcd.print(heavyCost);
    }

    else if(menuHorz == 4){
      lcd.setCursor(0, 0); lcd.print(support);
      lcd.setCursor(11, 1); lcd.print("Mana");
      lcd.setCursor(9, 1); lcd.print(supportCost);
    }

    break;

    case 4:
    lcd.setBacklight(RED);
    foe(ana1, ana2, ana3, ana4, ana5);
    
    if(menuHorz == 1){
      lcd.setCursor(0, 0); lcd.print("Foe");
    }

    if(menuHorz == 2){
      lcd.setCursor(0, 0); lcd.print("ATK   DFD   SUP");
      lcd.setCursor(0, 1); lcd.print(foeAtk);
      lcd.setCursor(6, 1); lcd.print(foeDfd);
      lcd.setCursor(12, 1); lcd.print(foeSup);
    }

    else if(menuHorz == 3){
      lcd.setCursor(0, 0); lcd.print("Weapon");
      lcd.setCursor(0, 1); lcd.print("Armor");
      if(foeWeapon < 10){
        lcd.setCursor(15, 0); lcd.print(foeWeapon);     
      }

      else{
        lcd.setCursor(14, 0); lcd.print(foeWeapon);
      }

      if(foeArmor < 10){
        lcd.setCursor(15, 1); lcd.print(foeArmor);
      }

      else{
        lcd.setCursor(14, 1); lcd.print(foeArmor);        
      }
    }

    else if(menuHorz == 4){
      lcd.setCursor(0, 0); lcd.print("Get attacked?");
    }

    break;
  }
}

void foe(int a1, int a2, int a3, int a4, int a5){
  for(int a = 1; a < 22; a ++){
    if(a1 < (a * 45)){
      foeAtk = a;
      break; 
    }
  }

  for(int b = 1; b < 22; b ++){
    if(a2 < (b *45)){
      foeDfd = b;
      break;
    }
  }

  for(int c = 1; c < 22; c ++){
    if(a3 < (c * 45)){
      foeSup = c;
      break;
    }
  }

  for(int d = 1; d < 22; d ++){
    if(a4 < (d * 45)){
      foeWeapon = d;
      break;
    }
  }

  for(int e = 1; e < 22; e ++){
    if(a5 < (e * 45)){
      foeArmor = e;
      break;
    }
  }

  foeHP = foeDfd * 5;
  foeMana = foeSup * 5;
}

void actions(){
  if(rollFlag == 1){
    if(menuVert == 3){
      if(menuHorz == 2){
        if(currentMana >= lightCost){
          currentMana = currentMana - lightCost;
          if(roll1 < atk){
            if(roll2 > foeDfd){
              lcd.setCursor(0, 0); lcd.print("Light hit");
              lcd.setCursor(0, 1); lcd.print("Damage = ");
              lcd.setCursor(9, 1); lcd.print(atk + weaponDam);
            }

            else{
              lcd.setCursor(0, 0); lcd.print("Glancing blow");
            }
          }

          else{
            lcd.setCursor(0, 0); lcd.print("Miss");
          }
        }

        else{
          lcd.setCursor(0, 0); lcd.print("Not enough");
          lcd.setCursor(0, 1); lcd.print("mana");
        }
      }

      else if(menuHorz ==3){
        if(currentMana >= heavyCost){
          currentMana = currentMana - heavyCost;
          if(roll1 < atk){
            if(roll2 > foeDfd){
              lcd.setCursor(0, 0); lcd.print("Heavy hit");
              lcd.setCursor(0, 1); lcd.print("Damage = ");
              lcd.setCursor(9, 1); lcd.print((atk + weaponDam) * 2);
            }

            else{
              lcd.setCursor(0, 0); lcd.print("Glancing blow");
            }
          }

          else{
            lcd.setCursor(0, 0); lcd.print("Miss");
          }
        }

        else{
          lcd.setCursor(0, 0); lcd.print("Not enough");
          lcd.setCursor(0, 1); lcd.print("mana");
        }
      }

      else if(menuHorz == 4){
        if(currentMana >= supportCost){
          currentMana = currentMana - heavyCost;
          lcd.setCursor(0, 0); lcd.print("You disapear");
          lcd.setCursor(0, 1); lcd.print("*poof*");          
        }
          
        else{
          lcd.setCursor(0, 0); lcd.print("Not enough");
          lcd.setCursor(0, 1); lcd.print("mana");
        }
      }

      else{
        menuSelect = 1;
      }
    }

    else if(menuVert == 4){
      if(menuHorz == 4){
        if(roll1 < foeAtk){
          if(roll2 < dfd){
            lcd.setCursor(0, 0); lcd.print("You're hit for");
            lcd.setCursor(0, 1); lcd.print(foeWeapon + foeAtk);
            currentHP = currentHP - (foeWeapon + foeAtk);

            if(currentHP < 0){
              deathFlag = 1;
            }
          }

          else{
            lcd.setCursor(0, 0); lcd.print("Glancing blow");
          }
        }

        else{
          lcd.setCursor(0, 0); lcd.print("Miss");
        }
      }

      else{
        menuSelect = 1;
      }
    }

    else{
      menuSelect = 1;
    }
    rollFlag = 0;
  }
}
