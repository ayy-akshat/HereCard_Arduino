#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#include <LiquidCrystal.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup()
{
  lcd.begin(16, 2);
  lcd.print("Please tap ID");
 
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(8, OUTPUT);
}
boolean prompt = true;
void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String content="";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  prompt = false;
  lcd.clear();
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("ID: " + content);
  Serial.println(content);
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(50);
  digitalWrite(8, HIGH);
  delay(50);
  digitalWrite(8, LOW);
  delay(800);
  lcd.clear();
  lcd.print("Please tap ID");
  delay(100);
}