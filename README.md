# EasyH2O-microbit
Software writen for the microbit in Arduino IDE

This software make use of the Microbit serial communication. It listens for commands end sends change events.\


# Here is how to connect:
## Properties
- Baud Rate: 9600
- Port (COM): PC Dependent

## Commands
- Send: `RF;` (RF: `Command`, `;`: Delimiter)\
Response: `FC,1,1,1,1,1;` (`FC`: ReponseText, `1,1,1,1,1` digial values for all floats, 1 = high, 0 = low, `;`: Delimiter)

## Events
- When the Microbit detects a change in float values, the sendFloats event is executed. This will send the following:\
Response: `FC,1,1,1,1,1;` (`FC`: ReponseText, `1,1,1,1,1` digial values for all floats, 1 = high, 0 = low, `;`: Delimiter)