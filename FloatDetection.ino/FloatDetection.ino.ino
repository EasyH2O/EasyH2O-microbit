#define totalFloats 5

int dataPoints[totalFloats]; // Stores the latest data values.
int floatPins[] = { 5, 6, 7, 8, 9 }; // We use 5 digital only pins on the micro:bit
const int buttonPin = 11;     // The number of the pushbutton pin
const int pumpPin =  3;      // The number of the pump
int buttonState = 0;         // Variable for reading the pushbutton status
boolean buttonPressed = false;         // Variable for showig the pushbutton status
int pumpState = 0;         // Variable for reading the pump status

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
  // initialize the pushbutton as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  while (!Serial) {
    // Wait for Serial to connect
  }
}

// Main program loop
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

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


//  Check for inputs from Serial.
    String command = Serial.readStringUntil(';'); // We read from the serial port, commands are ended with a semicolon, so that is our trigger.

//  Check against know command codes.
    if (command == "RF") sendFloats(); // When to command is RF (Read Floats) we send the float data.
    if (command == "SP") switchPump(); // When to command is SP (Switch Pump) we switch the pump.
    if (command == "PS") sendPump(); // When to command is PS (Pump State) we send the status of the pump.
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
    }
    else {
      //  pump on:
      digitalWrite(pumpPin, HIGH);
      pumpState = 1;
      Serial.print("PV,1;");
    }
}

void sendPump() {
  // Send Pump state formatted as output.
  Serial.print("PV,");
  Serial.print(pumpState);
  Serial.print(';');
}
