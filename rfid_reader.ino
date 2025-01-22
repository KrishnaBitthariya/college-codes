
//card -> UID tag : 7D C4 DE 00
//keychain -> UID tag : 09 76 02 01
// roll no. - 2 Krishna Bitthariya
// roll no. - 6 Haniraj Gupta
// roll no. - 9 Prineet Jain
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

int led_pin; 
#define SS_PIN 10
#define RST_PIN 9
#define red_led 6
#define yellow_led 7
MFRC522 mfrc522(SS_PIN, RST_PIN);   
Servo myServo;



void led(int pin) { 
  digitalWrite(pin, HIGH); 
  delay(500);             
  digitalWrite(pin, LOW);  
  delay(500);            
}


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Place your card to the reader...");
  Serial.println();
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  myServo.attach(4); 
  myServo.write(0);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  // if (content.substring(1) == "7D C4 DE 00" or content.substring(1) =="09 76 02 01") 
  if (content.substring(1) =="C3 0D DE 00") 
  {
    Serial.println("Authorized access");
    Serial.println();
    led(yellow_led);
    myServo.write(180);
    delay(3000);
    myServo.write(0);
    
  }
 
 else   {
    Serial.println(" Access denied");
    led(red_led);
    delay(1000);
  }
} 