
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
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  /*
    if (adc_key_in < 50)   return btnRIGHT;
    if (adc_key_in < 250)  return btnUP;
    if (adc_key_in < 450)  return btnDOWN;
    if (adc_key_in < 650)  return btnLEFT;
    if (adc_key_in < 850)  return btnSELECT;
  */
  // For V1.0 comment the other threshold and use the one below:
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;


  return btnNONE;  // when all others fail, return this...
}

const int sensorTpin = 22;  //virsaus sensorius
const int sensorBLpin = 30; //apatines kaires padeties sensorius
const int sensorBRpin = 26; //apatines desines padeties sensorius
const int sensorLpin = 34; //kaires puses sensorius
const int sensorRpin = 38; //desines puses sensorius
const int MovVpin = 42; //vertikalaus cilindro valdymas
const int MovHpin = 46; //horizontalaus cilindro valdymas
const int Butpin = 53; //pedalas

int mode = 4;//mygtuku pradines pozicijos
int modeA = 4;
int but = 0;
int ped = 0;
int sensT = 0;
int sensBL = 0;
int sensBR = 0;
int sensL = 0;
int sensR = 0;

void setup() {  

  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Rezimas"); // print a simple message

  pinMode(MovVpin, OUTPUT);
  pinMode(MovHpin, OUTPUT);
  pinMode(sensorTpin, INPUT);
  pinMode(sensorBLpin, INPUT);
  pinMode(sensorBRpin, INPUT);
  pinMode(sensorLpin, INPUT);
  pinMode(sensorRpin, INPUT);
  pinMode(Butpin, INPUT);
  // put your setup code here, to run once:
  digitalWrite(MovHpin, LOW);
  digitalWrite(MovVpin, HIGH);
}

void loop() {
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
    case btnSELECT:
      {
        modeA = mode;
        break;
      }
  }
  switch (mode) {
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
    case 1:
      {
        digitalWrite(MovHpin, LOW);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorBLpin) != HIGH) {
            digitalWrite(MovVpin, LOW);
            sensT = digitalRead(sensorTpin);
          }
          digitalWrite(MovVpin, HIGH);
        }
        break;
      }
    case 2:
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
    case 3:
      {
        digitalWrite(MovHpin, HIGH);
        digitalWrite(MovVpin, HIGH);
        while (digitalRead(Butpin) == HIGH) {
          ;
          if (digitalRead(sensorLpin) == HIGH) {
            digitalWrite(MovHpin, HIGH);
          }
          if (digitalRead(sensorRpin) == HIGH) {
            digitalWrite(MovHpin, LOW);
          }
        }
        break;
      }
    case 4:
      {
        digitalWrite(MovHpin, HIGH);
        digitalWrite(MovVpin, HIGH);
        if (digitalRead(Butpin) == HIGH) {
          while (digitalRead(sensorLpin) != HIGH) { //1 zingsnis
            digitalWrite(MovHpin, LOW);
          }
          while (digitalRead(sensorBLpin) != HIGH) { //2 zingsins
            digitalWrite(MovVpin, LOW);
          }
          //3 zingsnis
          digitalWrite(MovVpin, HIGH);
          while (digitalRead(sensorRpin) != HIGH) { //4 zingsnis
            digitalWrite(MovHpin, HIGH);
          }
          while (digitalRead(sensorBRpin) != HIGH) { //5 zingsnis
            digitalWrite(MovVpin, LOW);
          } //6 zingsnis
          digitalWrite(MovVpin, HIGH);

        }
        break;
      }
  }
}
// put your main code here, to run repeatedly:

