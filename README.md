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

1. Once the application is launched on our device we have to register in case of a new user or login in case of a previous user. In the case of registering, we ask the user to enter their ID number(roll number, employee number), Vehicle Number, Phone Number, Default Sector, etc.
<br>2. On clicking register, these details are sent to the backend server using a register API and saved to the database created on MongoDB. On successful
registration, a user is forwarded to the dashboard. In login, the user is asked for their ID number and the password which is then verified with the database using the backend API of login which uses a hash. On successful login, the user is forwarded to the dashboard.
<br>3. Here the user can book a parking spot for 30 minutes. The user enters their gate of entry and chooses between the default sector or any other sector they may be going to. Then using the free_space and nearest_park API we find the nearest free parking space and show it to the user. Then the user may choose the parking space and book it for 30 minutes after which it will be unbooked.
<br>4. When the user enters the campus, the RFID Scanner sends an API request enter_campus to the backend along with the vehicle number, which in return checks whether the vehicle already has a booked parking spot or not. In case, it does not have one, it creates a new instance of the vehicle in the backend, and with the help of the free_space and nearest_park, it gets the nearest parking and assigns it.
<br>5. Then using the location of the device the user is shown the way to the parking spot on its device application.
<br>6. The problem may arise when the user doesn't park the vehicle at the instructed slot. This problem will be solved with the help of an IoT device kept inside the car. The device will contain a NodeMCU ESP32 microcontroller Board which will be used as the principal processing unit and a NEO-6M GPS Module to get the exact location of the vehicle on the campus.
<br>7. The device starts once the vehicle enters the campus. It stores the exact location of the car till it is moving. Once the detected change in location is zero(0) for 15 minutes, it assumes the vehicle is stopped (parked) and sends the last location stored to the server. Which confirms that the vehicle is parked at the suggested location.
<br>8. Next, when the user starts moving again from the parking spot it checks if the user has another booked parking spot. If not then it asks the user if he/she wants to go to another sector or out of campus. If the sector is changed it finds another spot and the cycle starts again. If not the instance of the vehicle is removed from the current environment and the spot is marked free.

# Code Explanation 



