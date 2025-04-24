int button = 7;
int redLED = 13;
int greenLED = 12;

bool status = false;       
bool lastButtonState = HIGH;   
bool lastStatusSent = false;   

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT_PULLUP); 
  Serial.begin(9600);

  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}

void loop() {
  bool currentButtonState = digitalRead(button);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    status = !status; // Toggle the state
    delay(150);       // Debounce
  }
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
