/************************************
RFID Door Lock v1.0
by Judhi Prasetyo
The Assembly
January 2019
Get the RFID library from: 
http://dev.gulfware.com/rfid.zip
************************************/
#include <RFID.h>
#include <SPI.h>
#include <Servo.h>
RFID rfid(10, 9); // SS, RST PIN
Servo myServo; 
int serNum[5];
int RedLED = 6;
int GreenLED = 5;
int ServoPin = 3; 
String cardno;
// change below numbers to your card number later
char *mycards[] = {"22841931649","0000","13646335144"}; 

void setup() {
  pinMode(RedLED, OUTPUT); pinMode(GreenLED, OUTPUT); pinMode(ServoPin, OUTPUT);
  myServo.attach(ServoPin);
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}
void loop() {
  myServo.write(0);
  digitalWrite(RedLED, LOW); digitalWrite(GreenLED, LOW);
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      cardno = "";
      for (int i=0; i<5; i++) {
        cardno +=  String(rfid.serNum[i]);
      }
      Serial.print("Card detected: #"); 
      Serial.println(cardno);
    }
    int access = 0;
    for (int i=0; i<sizeof(mycards); i=i+1) {
      if (cardno == mycards[i]) {
         access = 1;
      } 
    }
    if (access == 1) {
        accessGranted();
    } else {
        accessDenied();
    }
  }
  rfid.halt();
  delay(1000);
}

void accessGranted() {
      Serial.println("Access Granted!");
      digitalWrite(RedLED, LOW); digitalWrite(GreenLED, HIGH); 
      myServo.write(120);
      delay(2000);
      myServo.write(0);
}

void accessDenied() {
      Serial.println("Access Denied!");
      digitalWrite(RedLED, HIGH); digitalWrite(GreenLED, LOW); 
}
