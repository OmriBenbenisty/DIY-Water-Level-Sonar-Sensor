// Define pins
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 32

int delaySec = 1; // in seconds

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
//  pinMode(LED_PIN, OUTPUT);
  ledcAttachPin(LED_PIN, 0);
  ledcSetup(0, 4000, 8);

}

void loop() {
  // Get distance from the sonar
  long distance = getDistance();

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Turn the LED on if distance > 20cm, otherwise turn it off
  if (distance > 18) {  // empty 
//    digitalWrite(LED_PIN, 255);  // for arduino
     ledcWrite(0, 255);

  }
  else if (distance > 14) {
    ledcWrite(0, 128);
//    digitalWrite(LED_PIN, 128);
  }
  else{
    ledcWrite(0, 0);
//    digitalWrite(LED_PIN, 0);
  }

  // Small delay before the next reading
  delay(delaySec * 1000);
}

// Function to calculate the distance
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin and calculate the distance in cm
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}
