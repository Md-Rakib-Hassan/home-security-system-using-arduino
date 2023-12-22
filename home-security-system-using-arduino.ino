//#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int motion_pin_in = 8;
int bazzar = 13;
int gas_pin_in = 10;
int dhtpin = 9;
char data = '1';
DHT dht(dhtpin, DHT11);
// int rxpin=11;
// int txpin=12;
// SoftwareSerial BT(txpin,rxpin);
//int blu_out=10;

void all_lcd() {
  char* lt = "                Md. Rakib Hassan, Shakibul Islam, Mahmuda Akter Mumu, Md. Hasan                ";
  int lm = strlen(lt);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Welcome to...");
  delay(1000);
  lcd.clear();
  lcd.print(" Home Security");
  lcd.setCursor(0, 1);
  lcd.print("    System");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Created by:");

  for (int j = 0; j + 16 < lm; j++) {
    for (int i = 0; i < 16; i++) {
      lcd.setCursor(i, 1);
      lcd.print(lt[i + j]);
    }
    delay(150);
  }
}



void all_dht() {
  int humidty = dht.readHumidity();
  int temp = ceil(dht.readTemperature());
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(humidty);
  lcd.print("%    T:");
  lcd.print(temp);
  lcd.print("C");
  delay(1000);
  lcd.clear();
}



void all_theif() {
  delay(500);
  int motion_detact = digitalRead(motion_pin_in);

  if (motion_detact == HIGH) {
    digitalWrite(bazzar, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Theif Detacted");
    delay(500);
    digitalWrite(bazzar, LOW);
    lcd.clear();
  }
}


void all_blu() {
  if (Serial.available()) {
    data = Serial.read();
  }
}

void all_gas() {
  if (digitalRead(gas_pin_in) == LOW) {
    digitalWrite(bazzar, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Gas Lekage Found");
    delay(500);
    digitalWrite(bazzar, LOW);
    lcd.clear();
  }
}





void setup() {
  all_lcd();
  dht.begin();
  //pinMode(txpin,INPUT);
  //pinMode(rxpin,OUTPUT);
  //BT.begin(9600);
  Serial.begin(9600);
  pinMode(gas_pin_in, INPUT);
  pinMode(motion_pin_in, INPUT);
  pinMode(bazzar, OUTPUT);
  lcd.clear();
}



void loop() {
  all_dht();
  all_blu();
  all_gas();
  if (data == '0') {
    all_theif();
  }
}