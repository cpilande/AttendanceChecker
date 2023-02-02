#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLrUSbH7yN"
#define BLYNK_DEVICE_NAME "Card Reader"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#include "BlynkEdgent.h"

#define SS_PIN 5
#define RST_PIN 22
#define redLed 33
#define greenLed 32
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

String idList[3] = {"0A A5 66 AD","6C 75 C6 33", "15 3A 79 8A 9E 5C 80"};
String studentNames[3] = {"Student 1", "Student 2", "Student 3"};
int checkedInList[3] = {0,0,0};
int t1,t2;

//creating timer object//
BlynkTimer timer;


//#define BLYNK_DEBUG

#define APP_DEBUG

int firstCard = 0;
 
void setup() 
{                                               
  Serial.begin(115200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //initializes student table to all absent every hour//
  timer.setInterval(1UL*60UL*1000UL,initializeTable);
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  BlynkEdgent.begin();

  myservo.attach(26);  // attaches the servo on pin 9 to the servo object

}
void loop() 
{
  
  BlynkEdgent.run();
  //Serial.println("-------");

  //Resets the students' attendance after 1 minute 
   t2 = millis();

  if(t2-t1 > 60000){
    firstCard = 0;
    t1 = 0;
    t2 = 0;
    
    checkedInList[0] = 0; 
    checkedInList[1] = 0; 
    checkedInList[2] = 0;
    
    initializeTable(); //Makes all students absent
  }

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
  
  if(firstCard == 0){
    t1 = millis();
    firstCard=1;
  }
  

  
  //Show UID on serial monitor
  Serial.print("\n");
  Serial.println("xxxx");
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
  bool isCheckedIn = false;
  
  //If card scanned is a student...
  
  for(int i = 0; i < 3; i++)
  {
    if(content.substring(1) == idList[i])
    {
      //Turn the servo motor to open the door
      for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      }

       //Update the student's status in the Blynk App to Present
      if (checkedInList[i] == 0)
      {
      isCheckedIn = true;
      checkedInList[i] = 1;
      
        if(i==0)
        {
          Blynk.virtualWrite(V0,"Present");
          Blynk.virtualWrite(V3,1);
        }
        else if (i==1)
        {
            Blynk.virtualWrite(V1,"Present");
            Blynk.virtualWrite(V4,1);
        }
        else if(i==2)
        {
         Blynk.virtualWrite(V2,"Present");
        Blynk.virtualWrite(V5,1);
        }

        //Print that the student is checked in
        Serial.print(studentNames[i]);
        Serial.println(" checked in");

        //Turn the red LED off and the green LED on
        digitalWrite(redLed,LOW);
        digitalWrite(greenLed,HIGH);
        delay(3000);

              //Close the door after the student enters
        for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
        }
      
        
        break;
      }

      //Output if the student has already been checked in
      else
      {
        isCheckedIn = true;
        Serial.print(studentNames[i]);
        Serial.println(" already checked in");

        digitalWrite(redLed,LOW);
        digitalWrite(greenLed,HIGH);
        delay(3000);

              //Close the door after the student enters
        for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
        }
      
      }


    }
  }
  
  //If the card scanned is not a student in the class, output that access is denied
  if(isCheckedIn == false){
    Serial.println("Access Denied");
    delay(3000);
  }
  //---------------
  //Reset red LED to turn on and green LED to turn off
  digitalWrite(redLed, HIGH); 
  digitalWrite(greenLed, LOW);
  delay(2000);

Serial.println("xxxx");

} 

void initializeTable() //Resets the table to absent
{
    Blynk.virtualWrite(V0,"Absent");
    Blynk.virtualWrite(V1,"Absent");
    Blynk.virtualWrite(V2,"Absent");  

    Blynk.virtualWrite(V3,0);
    Blynk.virtualWrite(V4,0);
    Blynk.virtualWrite(V5,0);
}
