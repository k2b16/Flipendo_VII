
/* YBG Fliptendo VVii */
const int USER_LED = 20;
const int UP = 19;
const int DOWN = 6;
const int LEFT = 5;
const int RIGHT = 7;

unsigned long lastTime = 0;
uint userLedState = 1;

void setup() {
  pinMode(USER_LED, OUTPUT);
  pinMode(UP, INPUT_PULLDOWN);
  pinMode(DOWN, INPUT_PULLDOWN);
  pinMode(LEFT, INPUT_PULLDOWN);
  pinMode(RIGHT, INPUT_PULLDOWN);

  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32-S3 started");
}

void loop() {
  if (millis() - lastTime >= 1000) {
    lastTime = millis();

    if (userLedState == 1){
      digitalWrite(USER_LED, HIGH);
      userLedState = 0;
    } else {
      digitalWrite(USER_LED, LOW);
      userLedState = 1;
    }
  }

  int state = 0;

  state = digitalRead(UP);
  if (state == HIGH) {
    Serial.println("up pressed");
  }

  state = digitalRead(DOWN);
    if (state == HIGH) {
    Serial.println("down pressed");
  }

  state = digitalRead(LEFT);
  if (state == HIGH) {
    Serial.println("left pressed");
  }

  state = digitalRead(RIGHT);
  if (state == HIGH) {
    Serial.println("right pressed");
  }
}
