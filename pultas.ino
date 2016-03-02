#include <MemoryFree.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // For V1.0 comment the other threshold and use the one below:
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;


  return btnNONE;  // when all others fail, return this...
}

const int sensorTpin = 22;  //Top sensor
const int sensorBLpin = 30; //Bottom left sensor
const int sensorBRpin = 26; //Bottor right sensor
const int sensorLpin = 34; //Left end sensor
const int sensorRpin = 38; //Right end sensor
const int MovVpin = 42; //Vertical movement control
const int MovHpin = 46; //Horizontal movement control
const int Butpin = 53; //Pedal

int mode = 4;//default mode
int modeA = 4;


void setup() {
 Serial.begin(115200);
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Rezimas"); // Translation 'mode'

  pinMode(MovVpin, OUTPUT);
  pinMode(MovHpin, OUTPUT);
  pinMode(sensorTpin, INPUT);
  pinMode(sensorBLpin, INPUT);
  pinMode(sensorBRpin, INPUT);
  pinMode(sensorLpin, INPUT);
  pinMode(sensorRpin, INPUT);
  pinMode(Butpin, INPUT);
  digitalWrite(MovHpin, LOW);
  digitalWrite(MovVpin, HIGH);
}

void loop() {
  //Serial.println(str);
 // Serial.println("freeMemory()=");
  lcd.setCursor(0, 1);           // move to the begining of the second line
  lcd_key = read_LCD_buttons();  // read the buttons

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
        if (mode == 4) {
          mode = 1;
        }
        else {
          mode = mode + 1;
        }
        break;
      }
    case btnLEFT:
      {
        if (mode == 1) {
          mode = 4;
        }
        else {
          mode = mode - 1;
        }
        break;
      }
    case btnSELECT: // confirm mode
      {
        modeA = mode;
        break;
      }
  }
  switch (mode) { //Selecting mode
    case 1:
      {
        lcd.print("Klise      ");
        delay(400);
        break;
      }
    case 2:
      {
        lcd.print("Daiktas     ");
        delay(400);
        break;
      }
    case 3:
      {
        lcd.print("Dazai     ");
        delay(400);
        break;
      }
    case 4:
      {
        lcd.print("Ciklas     ");
        delay(400);
        break;
      }
  }
  switch (modeA) {
    case 1: // Vertical movement in the left position
      {
        digitalWrite(MovHpin, LOW);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorBLpin) != HIGH) {
            digitalWrite(MovVpin, LOW);
          }
          digitalWrite(MovVpin, HIGH);
        }
        break;
      }
    case 2: // Vertical movement in the right position
      {
        digitalWrite(MovHpin, HIGH);
        digitalWrite(MovVpin, HIGH);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorBLpin) != HIGH) {
            digitalWrite(MovVpin, LOW);
          }
          digitalWrite(MovVpin, HIGH);

        }
        break;
      }
    case 3: //Horizontal movement
      {
        digitalWrite(MovHpin, HIGH);
        digitalWrite(MovVpin, HIGH);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorLpin) != HIGH) {
            digitalWrite(MovHpin, LOW);
          }
            delay(200);
          while (digitalRead(sensorRpin) != HIGH) {
            digitalWrite(MovHpin, HIGH+);
          }
          delay(200);
        }
        break;
      }
    case 4: //Full working cycle
      {
        digitalWrite(MovHpin, HIGH);
        digitalWrite(MovVpin, HIGH);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorLpin) != HIGH) { //1 zingsnis
            digitalWrite(MovHpin, LOW);
          }
          delay(200);
          while (digitalRead(sensorBLpin) != HIGH) { //2 zingsins
            digitalWrite(MovVpin, LOW);
          }
          //3 zingsnis
          digitalWrite(MovVpin, HIGH);
          delay(400);
          while (digitalRead(sensorRpin) != HIGH) { //4 zingsnis
            digitalWrite(MovHpin, HIGH);
          }
          delay(200);
          while (digitalRead(sensorBRpin) != HIGH) { //5 zingsnis
            digitalWrite(MovVpin, LOW);
          }//6 zingsnis
          digitalWrite(MovVpin, HIGH);
          delay(200);
        }
        break;
      }
  }
}



