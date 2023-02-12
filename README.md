# Attendance Checker

## Project Description
This project was created in collaboration with the Engaging Girls in Ubiquitous Intelligence and Computing (GUIC) Summer Camp initiative as part of the National Scientist Foundation-funded University of Nevada, Las Vegas ITEST project. 
http://nsil.sites.unlv.edu/ITEST.html

**Objective**: Students will make an attendance checking system using Arduino to efficiently take attendance in a SMART classroom.

**Applications**: Traditional attendance can be time-consuming, with teachers roll calling or using
a seating chart to ensure students are present. This process is known to shift the focus and
learning in the classroom. An automatic attendance checker is not time-demanding and allows
teachers to focus on instruction. The automatic attendance checker allows for a smooth learning
process and greater security in the classroom.

## Prerequisites

**Materials Needed**

- ESP32 Microcontroller
- MFRC522 Module
- 2 LED’s, 1 green and 1 red
- Servo Motor
- Breadboard
- Wires (Male to female)
- USB Cable
- Computer

**Important Arduino Installations**

Boards (found in “Board Manager” tab)
- ESP32

Libraries (found in “Manage Libraries” tab)
- Blynk
- ESP32Servo
- MFRC522

## Set-Up

**Servo Motor Connection**
- Red Wire connects to 5V pin
- Brown Wire connects to GND pin
- Yellow Wire connects to digital pin

<img width="262" alt="Screenshot 2023-02-12 at 11 54 26 AM" src="https://user-images.githubusercontent.com/120698868/218333781-6aabccbb-a74b-4742-a404-65cd9a30d1c2.png">

**RFID Reader & ESP32 Connection**

<img width="194" alt="Screenshot 2023-02-12 at 11 54 53 AM" src="https://user-images.githubusercontent.com/120698868/218333812-0b9a7e8e-8f6f-47cf-9b19-9921cc2a215a.png">

**Blynk App - Mobile Dashboard Template**
- Components
  - Student names with corresponding strings, stating "Absent" or "Present"
  - 3 LED's connected to corresponding students (use for testing purposes) 

<img width="335" alt="Screenshot 2023-02-12 at 11 55 18 AM" src="https://user-images.githubusercontent.com/120698868/218333834-3cd7bad3-b63c-4f2e-ab61-08a02022f616.png">

**Blynk App - Datastreams Template**
- Components
   - 3 student names with string data types
   - 3 virtual pins with integer data types (for testing purposes) 
<img width="522" alt="Screenshot 2023-02-12 at 11 55 56 AM" src="https://user-images.githubusercontent.com/120698868/218333868-5b347ce9-693c-4340-b18d-dde8e023f0da.png">

## Running the tests
1. Tap the card on the RF module.
2. If the UID of the card matches the one stored in the Blynk table...
    - In the Blynk table, the student’s status changes from “Absent” to “Present.”
    - Output to the serial monitor that the student has been checked in.
    - The green LED lights up, and the red LED turns off.
    - The servo motor moves in order to open the door.
3. If the UID of the card does not match the one stored in the Blynk table...
    - Output to the serial monitor that access has been denied.
    - Nothing changes in the Blynk Table.
4. If the student was already checked in...
    - The servo motor moves to open the door.
    - The green LED lights up, and the red LED turns off.
    - Nothing changes in the Blynk Table.
5. The class’s attendance should reset to “Absent” for all students after a certain period of time. This simulates a class period.
a. Use a time period of 1 minute in order to test that this works.

## Suggested Resources
ESP32: How to read RFID tags with a RFID Reader
https://www.youtube.com/watch?v=pJLjFm4Ipro&t=297s

## Built with
- Arduino
- Blynk App


