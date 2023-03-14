 #include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         46
#define SS_PIN          53

int UID[4], i;

int ID1[4] = {234, 95, 235, 173 }; //Thẻ bật tắt đèn
int sang = 30;

int dem = 0;
 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{

    Serial.begin(9600);   

    pinMode(sang, OUTPUT);
    digitalWrite(sang, LOW);
    
    SPI.begin();    
    mfrc522.PCD_Init();

}

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
  
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
  }

  Serial.println("   ");
  
  if (UID[i] == ID1[i])
  {
    dem ++;
    Serial.print("Biến Đếm: ");
    Serial.println(dem);
    
      if ( (dem % 2) == 1) //Số lẻ đèn ON
      {
        digitalWrite(sang, HIGH);
        Serial.println("ĐÈN ON");    
      }
      else
      {
        digitalWrite(sang, LOW);
        Serial.println("ĐÈN OFF");       
      }
  }
  
  else
  {
    Serial.println("SAI THẺ........");
  }

  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();

}
