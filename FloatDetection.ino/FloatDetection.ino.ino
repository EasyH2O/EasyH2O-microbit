#define totalFloats 5

#include <Adafruit_Microbit.h>

Adafruit_Microbit_Matrix microbit;

int dataPoints[totalFloats]; // Stores the latest data values.
int floatPins[] = { 2, 13, 14, 15, 16 }; // We use 5 digital only pins on the micro:bit

const int buttonPin = 11;     // The number of the pushbutton pin
const int pumpPin =  3;      // The number of the pump
int buttonState = 0;         // Variable for reading the pushbutton status
boolean buttonPressed = false;         // Variable for showig the pushbutton status
int pumpState = 0;         // Variable for reading the pump status

const int button2Pin = 5;     // The number of the second pushbutton pin
int button2State = 0;         // Variable for reading the second pushbutton status
boolean button2Pressed = false;         // Variable for showig the second pushbutton status
const int float1 = 2;
int floatState1 = 0;
const int float2 = 13;
int floatState2 = 0;
const int float3 = 14;
int floatState3 = 0;
const int float4 = 15;
int floatState4 = 0;
const int float5 = 16;
int floatState5 = 0;


void setup() {
//  Prep Serial
  Serial.begin(9600);
  Serial.setTimeout(20);


//  Prep float pins
  for (int i = 0; i < totalFloats; i++) {
    pinMode(floatPins[i], INPUT_PULLUP);
  }

  // initialize the pump pin as an output:
  pinMode(pumpPin, OUTPUT);
  // initialize the pushbuttons as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  microbit.begin();

  while (!Serial) {
    // Wait for Serial to connect
  }
}

// Main program loop
void loop() {
  // read the state of the pushbuttons values:
  buttonState = digitalRead(buttonPin);
  button2State = digitalRead(button2Pin);

//  If we have a change, report this back over serial.
  if (floatChanged()) {
    sendFloats();
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    buttonPressed = true;
  }
  if (buttonState == HIGH && buttonPressed == true){
    switchPump();
    buttonPressed = false;
    }


  if (button2State == LOW) {
    button2Pressed = true;
  }
  if (button2State == HIGH && button2Pressed == true){
    givePercentage();
    button2Pressed = false;
    }


//  Check for inputs from Serial.
    String command = Serial.readStringUntil(';'); // We read from the serial port, commands are ended with a semicolon, so that is our trigger.

//  Check against know command codes.
    if (command == "RF") sendFloats(); // When to command is RF (Read Floats) we send the float data.
    if (command == "SP") switchPump(); // When to command is SP (Switch Pump) we switch the pump.
    if (command == "PS") sendPump(); // When to command is PS (Pump State) we send the status of the pump.
    if (command == "GP") givePercentage(); // When to command is Pump we switch the pump.
}

// We read the serial command
void sendFloats() {
  //    We print the FloatChange code.
    Serial.print("FC");

//    We send the float values separated by commas.
    for (int i = 0; i < totalFloats; i++) {
      Serial.print(',');
      Serial.print(dataPoints[i]);
    }

    //    We end with a semicolon to indicate the end of this event.
    Serial.print(';');
}

boolean floatChanged() {
  boolean hasChanged = false;

//  Loop through all pins
  for (int i = 0; i < totalFloats; i++) {
//    Define the val variable, this is where we store the date we get from digitalRead.
    int val = 1;

//    Read the value from the pin.
    val = digitalRead(floatPins[i]);

//    If the value doesn't match our registered value, we set hasChanged to true. This will make this function return true. We also update the registerd value so we are ready for the next check.
    if (val != dataPoints[i]) {
      dataPoints[i] = val;
      hasChanged = true;
    }
  }

  return hasChanged;
}

void switchPump() {
  if (pumpState == 1) {
      // turn pump off:
      digitalWrite(pumpPin, LOW);
      pumpState = 0;
      Serial.print("PV,0;");
      microbit.print("PUMP OFF");
    }
    else {
      //  pump on:
      digitalWrite(pumpPin, HIGH);
      pumpState = 1;
      Serial.print("PV,1;");
      microbit.print("PUMP ON");
    }
}

void sendPump() {
  // Send Pump state formatted as output.
  Serial.print("PV,");
  Serial.print(pumpState);
  Serial.print(';');
}

void givePercentage(){
  floatState1 = digitalRead(float1);
  floatState2 = digitalRead(float2);
  floatState3 = digitalRead(float3);
  floatState4 = digitalRead(float4);
  floatState5 = digitalRead(float5);

  if (floatState1 == 1 && floatState2 == 1 && floatState3 == 1 && floatState4 == 1 && floatState5 == 1) {
    microbit.print("0% ");
  }
  else if (floatState1 == 1 && floatState2 == 1 && floatState3 == 1 && floatState4 == 1 && floatState5 != 1){
    microbit.print("20% ");
  }
  else if (floatState1 == 1 && floatState2 == 1 && floatState3 == 1 && floatState4 != 1 && floatState5 != 1){
    microbit.print("40% ");
  }
  else if (floatState1 == 1 && floatState2 == 1 && floatState3 != 1 && floatState4 != 1 && floatState5 != 1){
    microbit.print("60% ");
  }
  else if (floatState1 == 1 && floatState2 != 1 && floatState3 != 1 && floatState4 != 1 && floatState5 != 1){
    microbit.print("80% ");
  }
  else if (floatState1 != 1 && floatState2 != 1 && floatState3 != 1 && floatState4 != 1 && floatState5 != 1){
    microbit.print("100%");
  }
  else {
    microbit.print("error");
    }
}