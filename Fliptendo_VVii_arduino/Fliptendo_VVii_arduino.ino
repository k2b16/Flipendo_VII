
/* YBG Fliptendo VVii */
const int USER_LED = 20;
const int UP = 19;
const int DOWN = 6;
const int LEFT = 5;
const int RIGHT = 7;
const int JS_SW = 42;
const int JS_RY = 1;
const int JS_RX = 2;
const int COL_1 = 39;

unsigned long lastTime = 0;
uint userLedState = 1;

void setup() {
  pinMode(USER_LED, OUTPUT);
  pinMode(COL_1, OUTPUT);
  pinMode(UP, INPUT_PULLDOWN);
  pinMode(DOWN, INPUT_PULLDOWN);
  pinMode(LEFT, INPUT_PULLDOWN);
  pinMode(RIGHT, INPUT_PULLDOWN);
  pinMode(JS_SW, INPUT_PULLDOWN);

  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32-S3 started");
}

void loop() {
  if (millis() - lastTime >= 1000) {
    lastTime = millis();

    if (userLedState == 1){
      digitalWrite(USER_LED, HIGH);
      digitalWrite(COL_1, HIGH);
      userLedState = 0;
      
    } else {
      digitalWrite(USER_LED, LOW);
      digitalWrite(COL_1, LOW);
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

  state = digitalRead(JS_SW);
  if (state == HIGH) {
    Serial.println("Joystick switch pressed");
  }

  int rx = 0, ry = 0;
  rx = analogRead(JS_RX);
  ry = analogRead(JS_RY);
  Serial.printf("RX: %d, RY: %d \n", rx, ry);

  delay(200);
}
