int button = 7;
int redLED = 13;
int greenLED = 12;

bool status = false;           // false = not occupied
bool lastButtonState = HIGH;   // pull-up logic: HIGH = not pressed
bool lastStatusSent = false;   // used to track what was last sent

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT_PULLUP); // button connected to GND
  Serial.begin(9600);

  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}

void loop() {
  bool currentButtonState = digitalRead(button);

  // Detect falling edge (button just pressed)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    status = !status; // Toggle the state
    delay(150);       // Debounce
  }

  // Only update outputs and serial if state changed
  if (status != lastStatusSent) {
    if (status) {
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      Serial.println(1); // Occupied
    } else {
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      Serial.println(0); // Not Occupied
    }
    lastStatusSent = status;
  }

  lastButtonState = currentButtonState;
}
