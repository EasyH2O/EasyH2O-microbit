#define totalFloats 5

int dataPoints[totalFloats]; // Stores the latest data values.
int floatPins[] = { 5, 6, 7, 8, 9 }; // We use 5 digital only pins on the micro:bit

pinMode(1, OUTPUT);
digitalWrite(1, LOW);

void setup() {
//  Prep Serial
  Serial.begin(9600);


//  Prep float pins
  for (int i = 0; i < totalFloats; i++) {
    pinMode(floatPins[i], INPUT_PULLUP);
  }
  
  while (!Serial) {
    // Wait for Serial to connect
  }
}

// Main program loop
void loop() {
//  If we have a change, report this back over serial.
  if (floatChanged()) {
    sendFloats();
  }

  if (InputPump()) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }

//  Check for inputs from Serial.
    String command = Serial.readStringUntil(';'); // We read from the serial port, commands are ended with a semicolon, so that is our trigger.

//  Check against know command codes.
    if (command == "RF") sendFloats(); // When to command is RF (Read Floats) we send the float data.
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