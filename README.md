# MedConnect: A Compact and Efficient Pill Organizer for Seniors

## Introduction

The purpose of this project is to design and build a set of devices that solve various compounding problems faced by older generations - those being the consumption of prescribed medication in a timely manner, and also frequent isolation from loved ones.

This project serves different purposes for each user. For the patient and their device, it serves as a central device to organize their medication, as well as a reminder to take their medication. For the relative or carer and their device, it provides the knowledge that your loved one or patient is taking their medication properly, or serves as a means to remind them to do so if they forget. For both groups, it provides comfort and connection, illustrating that your loved ones are there for you even when they're physically absent.

The main features of this project are specific to each device. With their device, the patient has the ability to organize a week's worth of medication into daily boxes and, by the act of taking their medication, notify their relative of carer that they have done this. It also has the ability to receive notifications from the relative or carer device and use a buzzer to notify the patient if they have not taken their medication. The relative or carer device has the ability to recieve notifications from the patient device once medication has been taken, as well as remind the patient to take their medication through the push of a button.


## Second Midterm Critique

The feedback our team recieved in our second midterm critique is as follows:
- Change the way the pill boxess will be detected - turning them into the equivilant of a switch, this allowed our team to use a digital pin each for the 7 pill boxes instead of having to split anolog pins between 2 pill boxes in our previous design. 
-  Add communication button to the relative device in order to nudge the user to take medication if they haven't, also lets the user know they're relative or carer is thinking baout them.
- Add rails to the pill box and daily boxes so they fit together correctly.

## Prototyping

MedConnect was created to provide seniors with an effective solution to manage their medication needs, while also providing peace of mind to their family members. Initially, we implemented bare conductive sensors to detect pressure on pill boxes, but we found that they were not accurate enough. We then tried using a 1kg load cell, but it proved to be difficult to measure milligrams precisely. Eventually, we decided to use copper foil to detect each daily pill box. Our original plan involved sliding pill boxes and displaying medication reminders on an LCD screen.

During the development of the first printing, we made several iterations to improve its design and functionality. We received feedback about the initial size and material waste of the first printing, which prompted us to make adjustments to reduce the size of the box while still maintaining ergonomic and practical considerations. The second version of the box was successfully resized to fit comfortably in the hand and allowed for efficient storage of pills, while also being proportional to the copper foils and electrical wires. The third and final version addressed concerns about copper foil damage and the need for sufficient space for magnets to secure the small boxes. These modifications made the box more user-friendly, with improved circuit stability and a secure magnet system. The overall result is a compact and efficient pill organizer that is easy to use and troubleshoot.

Below are images showing the development process of MedConnect from its initial prototype to the final product:

### Drawing of the Pill Organizer
![Drawing of the Pill Organizer](/Prototype%20to%20End%20result/Drawing%20pill%20organiser.png)

### First Prototype - Bare Conductive Sensors
![First Prototype - Bare Conductive Sensors](/Prototype%20to%20End%20result/First%20Prototype%20BARE%20CONDUCTIVE.png)

### Second Prototype - Copper Foil
![Second Prototype - Copper Foil](/Prototype%20to%20End%20result/First%20Prototype%20Copper%20foil.png)

### First 3D Printed Prototype
![First 3D Printing Prototype](/Prototype%20to%20End%20result/First%203D%20printing%20prototype.png)

### Second 3D Printed Prototype
![Second 3D Printing Prototype](/Prototype%20to%20End%20result/Second%203D%20Printing.png)

### The Platform for the Circuit
![The Platform for the Circuit](/Prototype%20to%20End%20result/The%20Platform%20for%20the%20circuit.png)

### PCB Blueprint
![PCB Blueprint](/Prototype%20to%20End%20result/PCB%20Blueprint.png)

### End Result - 3D Printed Pill Organizer
![End Result - 3D Printed Pill Organizer](/Prototype%20to%20End%20result/End%20result%203D%20Printing.png)

### Drawing of the Relative Device
![Drawing of the relative device](https://github.com/Gil-ADDA/MedConnect/blob/main/images/First%20draft.png)

### Laser Cut design - Relative Device 
![Laser cut design](https://github.com/Gil-ADDA/MedConnect/blob/main/images/laser%20cut%20design.png)

### End Result - Relative Device
![Relative device](https://github.com/Gil-ADDA/MedConnect/blob/main/images/Relative%20device.jpeg)

## Hardware and Software Components
A list of the hardware and software components used in the project, including microcontrollers, sensors, and libraries.

### Pill Organizer

**Hardware**
- Adafruit Feather Huzzah ESP8266
- Piezo Buzzer 
- Copper wire
- Copper foil
- Magnets
- USB power cord
- PLA filament
- Acrylic sheet

**Software**
- ezTime library
- PubSubClient library
- ArduinoJson library
- ESP8266 Wi-Fi library

### Relative Device

**Hardware**
- Adafruit Feather Huzzah ESP8266
- PLA filament
- LCD screen
- Servo motor
- USB power cord
- Copper wire
- Wooden materials

**Software**
- ezTime library
- PubSubClient library
- ArduinoJson library
- ESP8266 Wi-Fi library
- String library
- Wire library
- Servo library
- LiquidCrystal_I2C library

## Design & 3D Models

### Patient Device
![medconnect model](https://user-images.githubusercontent.com/33913141/233387985-61384345-0943-4d70-8fae-fab121c7a6e4.png)

### Relative Device
![Relative device model](https://github.com/Gil-ADDA/MedConnect/blob/main/images/Relative%20device%20model.png)

## Usage:

### Pill Organizer
Plug in the smart medicine box to a power source using the provided cable.
Fill the compartments with the necessary medication for each day of the week.
The smart medicine box will keep track of the medication schedule and send notifications to the relative device whenever pills are taken or missed.
Receiving Notifications and Sending Reminders
The Medconnect pill organizer is designed to send notifications to the relative device whenever the senior user takes their pills or if they miss their medication. If the senior user misses their medication, the relative device can send a notification to remind them to take their pills. Additionally, the relative device can send a notification to the smart medicine box by pressing a button on the device, activating the buzzer on the smart medicine box to remind the senior user to take their pills.

### Relative Device
The 3D doctor model on the relative device is designed to provide emotional engagement and accountability for the senior user's medication adherence. By default, the doctor has a sad face, but when the senior user takes their pills, the doctor's face turns to a happy expression.There is an lcd screen that can be used to show how much unused medicine is left in the box. Every midnight, the doctor's face returns to the default sad face.

## Specific Features and Functions
The Medconnect pill organizer has several specific features and functions that you may find useful:

- Medication Schedule: The smart medicine box is divided into different compartments for each day of the week, but there are no specific times for taking the medication.
- Notification and Alerts: The smart medicine box is designed to send notifications to the relative device whenever the senior user takes their pills or if they miss their medication. The relative device can also send a notification to remind the senior user to take their pills by activating the buzzer on the smart medicine box.
- Emotional Engagement: The 3D doctor model provides emotional engagement and accountability, strengthening the bond between patients and their families. By default, the doctor has a sad face, but when the senior user takes their pills, the doctor's face turns to a happy expression. Every midnight, the doctor's face returns to the default sad face.
- Easy to Use: The Medconnect pill organizer is designed to be easy to use, with clearly labeled compartments and a simple interface.
- Compact Size: The smart medicine box is compact and can be easily stored on a shelf or countertop.

## Troubleshooting
Information on how to troubleshoot common issues or errors that may occur while using the device.

 ### Pill Orgnanizer
 - One issue someone may face with with the pill organizer is the detection of an open circuit even when a daily box has been placed back into it's slot. This is is due to insufficient contact between the box and the main body of the device. To remedy this, simple adjust the box so it sits flush against its base and give it a slight push down into its correct position.
 
 ### Relative Device
 - A problem someone may face is that after pressing a button, that device does not capture the moment of the button press, so it may result in no feedback from the corresponding device even though the user pressed the button. To solve this problem, try pressing the button a few more times to be able to ensure that the message is definitely received.

## Future work

### Pill Organiser
In the future work, our team would like to add a temperature and humidity sensor to the pill organiser. This addition will help to ensure that the patient is keeping their medication in an ideal environment to maintain its effectiveness. Temperature and humidity information will be displayed on an attached LCD screen for convenient viewing. Our team would also like to include more inclusive means of reminding patients to take their medicine, including a flashing light or possibly push notifications to a patient’s smart device.

### Relative Device
In the future, the use of messaging could be used to enable more to be passed between the two devices than just the alert. More contents could also be added to the LCD display.

Currently, most parts of the family's device are made up of 3D printed materials due to technical limitations, which also leads to high manufacturing costs and the inability to recycle. In the future, recyclable materials could be used instead of 3D printed materials, which would reduce costs and be environmentally friendly at the same time.

## Contributors:

| Product/Responsibility | Members             | Activities                                                 |
|------------------------|---------------------|------------------------------------------------------------|
| Pill organiser          | Gil Adda, André Bourgeois | Prototyping, writing the code for MQTT, buzzer, 7 input pins, design the pill organiser 3D model (fusion), 3D printing (Prusa and Ultimaker), design the circuit and soldering |
| Relative device         | Shiqu Gao, Qishu Qian   | Writing the code, design 3D model (fusion), 3D printing (Prusa and Ultimaker), laser cutting (fusion), design the circuit and soldering |

## License
This project is licensed under the MIT License.

## References:
A list of any sources or references used in the project.(harvard referneces)

Medication reminder GlowCap goes direct-to-consumer (2009). Available at: https://www.mobihealthnews.com/3888/medication-reminder-glowcap-goes-direct-to-consumer.

EllieGrid (no date) The Smart Pill Organizer with Brains & Beauty. Available at: https://elliegrid.com/.

Sagely (2018b) Daily Pill Organizers and Pill Reminder App | Sagely. Available at: https://www.livesagely.com/.

Abdul Minaam, D.S. and Abd-ELfattah, M. (2018). Smart drugs:Improving healthcare using Smart Pill Box for Medicine Reminder and Monitoring System. Future Computing and Informatics Journal, 3(2), pp.443–456. doi:10.1016/j.fcij.2018.11.008.

Good Night Lamp, Source: https://www.designswarm.com/good-night-lamp/ (Retrieved on 23/01/2023)

Rosli, E. and Husaini, Y. (2018). Design and Development of Smart Medicine Box. IOP Conference Series: Materials Science and Engineering, 341, p.012004. doi:10.1088/1757-899x/341/1/012004.

Ughade, S.M. (2021). Low Powered IOT Enable Smart Medicine Pill Box Using ESP 8266. International Journal for Research in Applied Science and Engineering Technology, 9(VII), pp.3804–3808. doi:10.22214/ijraset.2021.36930.

