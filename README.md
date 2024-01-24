## SmartSpot

# Problem Statement 

**SMART IN-CAMPUS CAR PARKING SYSTEM**

Due to the increase in traffic on the national highway, it is difficult to reach the campus on time, and finding the nearest parking space for four-wheeler parking is tedious. Develop an intelligent application that provides a real-time parking slot within the campus as soon as the car enters the main gate. The empty parking space should be messaged to the user’s mobile whenever a person enters through the main entrance. Nowadays, traffic inside the campus has increased due to the hassle of four-wheeler vehicles. The increased traffic delays the work of people running on time. So usually, people park their vehicles in any undesirable slot blocking the road, which creates problems for other students and professors. This can also cause unwanted accidents inside a campus. The parking slots are not well used i.e. some parking areas are overfilled while others are still vacant. Mismanagement of the slots can also cause parking of vehicles on the roads as their desired parking place is full.

# Introduction 
Looking into the problems, we have decided to build an application SLIDe which will help to manage parking slots and save everyone’s time. For now, we are considering only the area of our campus, NIT Rourkela. 
<br>1. We start by issuing a tag to every registered vehicle on the campus. Every time that vehicle enters through the gate we scan it using an RFID reader installed at the security gate which gathers information from the issued tag.
<br>2. We fetch the details from the tag and then pop a message to the owner’s cellphone to select a destination inside the campus. The application allows him a parking slot based on his destination and directs him to the place showing him the shortest path.
<br>3. The shortest path will also be updated every minute. The device will contain a NodeMCU ESP32 microcontroller Board which will be used as the principal processing unit and a NEO-6M GPS Module to get the exact location of the vehicle on the campus.
<br>4. Whenever he leaves the parking place, we pop him a message about whether he wants to go to any other place or leave. if he wants to go to another place, we will redirect him the same way by assigning a slot.
<br>5. We will also provide the user the flexibility to book a slot from home for 30 minutes and also to set a default destination which will always allot him a slot as soon as he enters the campus.

# Added Features 
<br>1. As soon as the user enters the entrance of campus by any of the 3 gates, our application pops up a notification asking him his desired location and then assigning him the slot with the shortest route to it.
<br>2. We even track if the vehicle is parked or not and give him his weekly report of timings which can help him to know how much time he saves and how much time is required to reach.
<br>3. As soon as the vehicle starts again, our IoT device recognizes and then the application sends a notification asking him whether he wants to go to any other location on the campus or wants to leave from the main gate. If he selects any other location again a drop-down appears about destinations and again the slots are assigned assisting him to the slot by the shortest route.
<br>4. We have a parking database grouped sector-wise and each sector has departments that have several parking slots which show the users which slots are vacant and they can pre-book their slots from their homes for 30 minutes. 

# Flowchart 

![image](https://github.com/PriyanshaNayak/SmartSpot/assets/87187181/1dfb470a-32a0-4a81-adc7-16fd5d9ef9cb)

<br>1. Once the application is launched on our device we have to register in case of a new user or login in case of a previous user. In the case of registering, we ask the user to enter their ID number(roll number, employee number), Vehicle Number, Phone Number, Default Sector, etc.

<br>2. On clicking register, these details are sent to the backend server using a register API and saved to the database created on MongoDB. On successful
registration, a user is forwarded to the dashboard. In login, the user is asked for their ID number and the password which is then verified with the database using the backend API of login which uses a hash. On successful login, the user is forwarded to the dashboard.

<br>3. Here the user can book a parking spot for 30 minutes. The user enters their gate of entry and chooses between the default sector or any other sector they may be going to. Then using the free_space and nearest_park API we find the nearest free parking space and show it to the user. Then the user may choose the parking space and book it for 30 minutes after which it will be unbooked.

<br>4. When the user enters the campus, the RFID Scanner sends an API request enter_campus to the backend along with the vehicle number, which in return checks whether the vehicle already has a booked parking spot or not. In case, it does not have one, it creates a new instance of the vehicle in the backend, and with the help of the free_space and nearest_park, it gets the nearest parking and assigns it.

<br>5. Then using the location of the device the user is shown the way to the parking spot on its device application.

<br>6. The problem may arise when the user doesn't park the vehicle at the instructed slot. This problem will be solved with the help of an IoT device kept inside the car. The device will contain a NodeMCU ESP32 microcontroller Board which will be used as the principal processing unit and a NEO-6M GPS Module to get the exact location of the vehicle on the campus.

<br>7. The device starts once the vehicle enters the campus. It stores the exact location of the car till it is moving. Once the detected change in location is zero(0) for 15 minutes, it assumes the vehicle is stopped (parked) and sends the last location stored to the server. Which confirms that the vehicle is parked at the suggested location.

<br>8. Next, when the user starts moving again from the parking spot it checks if the user has another booked parking spot. If not then it asks the user if he/she wants to go to another sector or out of campus. If the sector is changed it finds another spot and the cycle starts again. If not the instance of the vehicle is removed from the current environment and the spot is marked free.

# Code Explanation 

**1. The following shows the explanation of the code for integrating IR sensors. Here's a breakdown of how the code works:**

**Variable Declarations:**
ir1, ir2, ir3, and ir4 are defined as integers with specific values corresponding to the Arduino pins to which the IR sensors are connected (12, 14, 27, and 26, respectively).

**Setup Function:**
void setup(): This function runs once when the Arduino is powered up or reset.

pinMode(ir1, INPUT), pinMode(ir2, INPUT), pinMode(ir3, INPUT), and pinMode(ir4, INPUT) set the specified pins as input, indicating that these pins will be used to read digital signals.

Serial.begin(9600): Initializes the serial communication at a baud rate of 9600. This is commonly used for communication between the Arduino and an external device, such as a computer. It allows you to monitor and debug the program using the Arduino IDE's serial monitor.

**Loop Function:**
void loop(): This function runs repeatedly after the setup() function.

int data1 = digitalRead(ir1), int data2 = digitalRead(ir2), int data3 = digitalRead(ir3), int data4 = digitalRead(ir4): Reads the digital signal from each of the four IR sensors and stores the results in variables data1, data2, data3, and data4.

Serial.print(data1), Serial.print(data2), Serial.print(data3), Serial.println(data4): Prints the values of data1, data2, data3, and data4 to the serial monitor. The Serial.println at the end adds a newline character, making each set of readings appear on a new line in the serial monitor.

**Working of the Code:**
<br>1. The IR sensors are used to detect the presence of vehicles or objects at specific points in a traffic management system.
<br>2. The loop continuously reads the digital signals from the four IR sensors.
<br>3. The readings are then printed to the serial monitor, which can be monitored through the Arduino IDE or other serial communication tools.
<br>4. The values printed will be either 0 or 1, representing the absence (0) or presence (1) of a vehicle or object at each sensor location.
<br>5. In a practical scenario, you would typically use these sensor readings to make decisions or control other components of a traffic management system, such as traffic lights or barriers. For example, if a sensor detects a vehicle, it could trigger a specific action to manage traffic flow.

**2. The 2nd Arduino code is for an RFID-based smart vehicle traffic management system. It uses an MFRC522 RFID module to read RFID cards and obtain their unique identification numbers (UIDs). Below is an explanation of the key parts of the code:**

**Libraries:**
#include <SPI.h>: This library is for the Serial Peripheral Interface (SPI) communication, which is used for communication between the Arduino and the RFID module.
<br>#include <MFRC522.h>: This library is for interfacing with the MFRC522 RFID module.

**Constants:**
#define SS_PIN 5: Defines the Slave Select (SS) pin for SPI communication.
<br>#define RST_PIN 22: Defines the Reset (RST) pin for the RFID module.

**Parameters:**
const int ipaddress[4] = {103, 97, 67, 25};: An array representing an IP address. However, it seems unused in the provided code.

**Variables:**
byte nuidPICC[4]: An array to store the UID (Unique Identifier) of the RFID card.
<br>MFRC522::MIFARE_Key key: An object representing the MIFARE key used for authentication.
<br>MFRC522 rfid = MFRC522(SS_PIN, RST_PIN): An instance of the MFRC522 class, initialized with the SS and RST pins.

**Setup Function:**
void setup(): Initializes the system.
<br>Serial.begin(4800): Initializes serial communication with a baud rate of 4800.
<br>Initializes the RFID module using SPI.begin() and rfid.PCD_Init().
<br>Prints the RFID module version to the serial monitor.

**Loop Function:**
void loop(): Calls the readRFID() function repeatedly.

**readRFID Function:**
void readRFID(): Reads the RFID card when a new card is present.
<br>Initializes an array key with default values.
<br>Checks if a new RFID card is present using rfid.PICC_IsNewCardPresent().
<br>Reads the card's serial number using rfid.PICC_ReadCardSerial().
<br>Stores the UID in the nuidPICC array.
<br>Prints the UID in both decimal and hexadecimal formats to the serial monitor.
<br>Halts the PICC (Proximity Integrated Circuit Card) and stops encryption.

**Helper Functions:**
printHex(byte *buffer, byte bufferSize): Prints a byte array in hexadecimal format to the serial monitor.
<br>printDec(byte *buffer, byte bufferSize): Prints a byte array in decimal format to the serial monitor.

In a smart vehicle traffic management system, this code could be part of a larger system where RFID cards are associated with vehicles. When a vehicle with an RFID card approaches a certain point (e.g., a toll booth or parking entrance), the RFID module reads the card's UID, and the system can then take actions based on that information, such as opening a gate or deducting toll fees. The IP address parameter suggests a network-related functionality, but its purpose is not evident in the provided code.






