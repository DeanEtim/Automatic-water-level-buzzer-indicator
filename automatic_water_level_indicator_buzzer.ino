// connections
const int buzzer = 5;
const int trig = 8;
const int echo = 9;
const int pump = 7;
const int button = 10;

// Variables
float distance1 = 0.0;
float duration1 = 0.0;
bool buttonState = 0;

void setup() {
  // initialize monitor
  Serial.begin(9600);

  // set pin modes
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(button, INPUT_PULLUP);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}  // end setup

void loop() {
  // Pump water when the button is pressed
  buttonState = digitalRead(button);
  if (buttonState == LOW) {
    digitalWrite(pump, HIGH);
  } else {
    digitalWrite(pump, LOW);
  }  // end

  // Send ultrasonic pulse with sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Receive the echo
  duration1 = pulseIn(echo, HIGH);

  // Calculate and print the distance
  float factor = 0.0171;
  distance1 = factor * duration1;
  Serial.println(distance1);

  // Control buzzer behavior based on water level
  if (distance1 <= 5) {
    Serial.println("FULL Tank!");
    // Full tank - fast beeping
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  }

  else if (distance1 >= 12) {
    // Empty tank - slow beeping
    Serial.println("EMPTY Tank!");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(300);
  }

  else {
    // Normal water level - no beeping
    digitalWrite(buzzer, LOW);
  }
  delay(100);
}  // end main loop
