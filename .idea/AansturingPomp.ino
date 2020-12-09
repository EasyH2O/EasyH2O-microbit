#define totalFloats 5

int Pins[] = { 1 }; // We use 5 digital only pins on the micro:bit

void setup() {
    Serial.begin(9600);

    pinMode(pins [0], OUTPUT);
    digitalWrite(pins [0], LOW);
    pinMode(LED, OUTPUT);

    if (input){
        digitalWrite(LED, HIGH);
    }

    if (!input){
        digitalWrite(LED, LOW);
    }
