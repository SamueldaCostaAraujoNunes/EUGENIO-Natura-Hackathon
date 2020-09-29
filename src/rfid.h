#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);
int statuss = 0;
int out = 0;
String oldResult = "";

void setupRFID() 
{
  SPI.begin();
  mfrc522.PCD_Init();
}

String getRFID(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return "";
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return "";
  }

  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  return content.substring(1);
}