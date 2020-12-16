# EasyH2O-microbit
Software writen for the microbit in Arduino IDE

This software make use of the Microbit serial communication. It listens for commands end sends change events.\


# Here is how to connect:
## Properties
- Baud Rate: 9600
- Port (COM): PC Dependent

## Commands
- Send: `RF;` (RF: `Command`, `;`: Delimiter) **Read Floats**\
Response: `FC,1,1,1,1,1;` (`FC`: ReponseText, `1,1,1,1,1` digial values for all floats, 1 = high, 0 = low, `;`: Delimiter)

- Send: `SP;` (SP: `Command`, `;`: Delimiter) **Switch Pump**\
Response: `PF,1;` (ReponseText, `1` digial value for the pump, 1 = on, 0 = off)

- Send: `PS;` (SP: `Command`, `;`: Delimiter) **Pump Sate**\
Response: `PF,1;` (ReponseText, `1` digial value for the pump, 1 = on, 0 = off)

## Events
- When the Microbit detects a change in float values, the sendFloats event is executed. This will send the following:\
Response: `FC,1,1,1,1,1;` (`FC`: ReponseText, `1,1,1,1,1` digial values for all floats, 1 = high, 0 = low, `;`: Delimiter)
