
/* YBG Fliptendo VVii */

/* data structs */
typedef struct {
  uint rx;
  uint ry;
  uint sw;
} joystick_st;

typedef struct {
  int up;
  int down;
  int left;
  int right;
} buttons_st;

/* pins */
const int UP = 4; // UP = 19 (old pin)
const int DOWN = 6;
const int LEFT = 7;
const int RIGHT = 5;

const int JS_SW = 42;
const int JS_RY = 1;
const int JS_RX = 2;

const int USER_LED = 20;

const int COL_1 = 39;
const int COL_2 = 38;
const int COL_3 = 45;
const int COL_4 = 48;
const int COL_5 = 47;
const int COL_6 = 21;
const int COL_7 = 14;
const int COL_8 = 13;
const int COL_9 = 12;
const int COL_10 = 11;
const int COL_11 = 10;
const int COL_12 = 9;
const int COL_13 = 46;
const int COL_14 = 3;

const int not_OE = 8;
const int STCP = 18;
const int SHCP = 17;
const int not_MR = 16;
const int DS = 15;

const int BUZZER = 41;

/* variables */
unsigned long lastTime = 0;
uint userLedState = 1;
int rows[] = {
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
  HIGH,
};

/* custom functions */
void setup_pins(void){
  pinMode(USER_LED, OUTPUT);
  
  pinMode(COL_1, OUTPUT);
  pinMode(COL_2, OUTPUT);
  pinMode(COL_3, OUTPUT);
  pinMode(COL_4, OUTPUT);
  pinMode(COL_5, OUTPUT);
  pinMode(COL_6, OUTPUT);
  pinMode(COL_7, OUTPUT);
  pinMode(COL_8, OUTPUT);
  pinMode(COL_9, OUTPUT);
  pinMode(COL_10, OUTPUT);
  pinMode(COL_11, OUTPUT);
  pinMode(COL_12, OUTPUT);
  pinMode(COL_13, OUTPUT);
  pinMode(COL_14, OUTPUT);

  pinMode(not_OE, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(not_MR, OUTPUT);
  pinMode(DS, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(JS_SW, INPUT_PULLUP);
}

void user_led_blink(void){
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
}

void read_buttons(buttons_st* buttons){
  int state;

  state = digitalRead(UP);
  buttons->up = state;
  if (state == LOW) {
    Serial.println("up pressed");
  }

  state = digitalRead(DOWN);
  buttons->down = state;
  if (state == LOW) {
    Serial.println("down pressed");
  }

  state = digitalRead(LEFT);
  buttons->left = state;
  if (state == LOW) {
    Serial.println("left pressed");
  }

  state = digitalRead(RIGHT);
  buttons->right = state;
  if (state == LOW) {
    Serial.println("right pressed");
  }
}

void read_joystick(void){
  joystick_st joystick;
  joystick.rx = analogRead(JS_RX);
  joystick.ry = analogRead(JS_RY);
  Serial.printf("RX: %d, RY: %d \n", joystick.rx, joystick.ry);

  int state = digitalRead(JS_SW);
  if (state == LOW) {
    Serial.println("joystick switch pressed");
  }
}

void shift_out(int rows[]){
  int shift_reg_delay = 1;
  // set everything default
  digitalWrite(SHCP, LOW);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(not_MR, HIGH);
  digitalWrite(not_OE, LOW);
  delay(shift_reg_delay);
  digitalWrite(SHCP, HIGH);
  delay(shift_reg_delay);
  
  // master reset
  digitalWrite(not_MR, LOW);
  digitalWrite(SHCP, LOW);
  delay(shift_reg_delay);
  digitalWrite(SHCP, HIGH);
  delay(shift_reg_delay);
  digitalWrite(not_MR, HIGH);
  digitalWrite(SHCP, LOW);
  delay(shift_reg_delay);
  digitalWrite(SHCP, HIGH);
  delay(shift_reg_delay);

  // shift out rows data
  for (uint8_t i=0; i<16; i++){
    digitalWrite(DS, rows[i]);

    digitalWrite(SHCP, LOW);
    digitalWrite(STCP, HIGH);
    delay(shift_reg_delay);
    digitalWrite(SHCP, HIGH);
    digitalWrite(STCP, LOW);
    delay(shift_reg_delay);
  }

  digitalWrite(SHCP, LOW);
  digitalWrite(STCP, HIGH);
  delay(shift_reg_delay);
  digitalWrite(SHCP, HIGH);
  digitalWrite(STCP, LOW);
  delay(shift_reg_delay);
}

/* main functions */
void setup() {
  setup_pins();
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32-S3 started");
  shift_out(rows);
}

void loop() {
  user_led_blink();

  buttons_st buttons;
  read_buttons(&buttons);
  if (LOW == buttons.up){
    rows[0] = HIGH;
    rows[1] = HIGH;
    rows[2] = HIGH;
    rows[3] = HIGH;
    rows[4] = HIGH;
    rows[5] = HIGH;
    rows[6] = HIGH;
    rows[7] = HIGH;
    rows[8] = HIGH;
    rows[9] = HIGH;
    rows[10] = HIGH;
    rows[11] = HIGH;
    rows[12] = HIGH;
    rows[13] = HIGH;
    rows[14] = HIGH;
    rows[15] = HIGH;
    shift_out(rows);
  }
  if (LOW == buttons.down){
    rows[0] = LOW;
    rows[1] = LOW;
    rows[2] = LOW;
    rows[3] = LOW;
    rows[4] = LOW;
    rows[5] = LOW;
    rows[6] = LOW;
    rows[7] = LOW;
    rows[8] = LOW;
    rows[9] = LOW;
    rows[10] = LOW;
    rows[11] = LOW;
    rows[12] = LOW;
    rows[13] = LOW;
    rows[14] = LOW;
    rows[15] = LOW;
    shift_out(rows);
  }
  if (LOW == buttons.left){
    rows[0] = HIGH;
    rows[1] = LOW;
    rows[2] = HIGH;
    rows[3] = LOW;
    rows[4] = HIGH;
    rows[5] = LOW;
    rows[6] = HIGH;
    rows[7] = LOW;
    rows[8] = HIGH;
    rows[9] = LOW;
    rows[10] = HIGH;
    rows[11] = LOW;
    rows[12] = HIGH;
    rows[13] = LOW;
    rows[14] = HIGH;
    rows[15] = LOW;
    shift_out(rows);
  }
  if (LOW == buttons.right){
    rows[0] = LOW;
    rows[1] = LOW;
    rows[2] = LOW;
    rows[3] = LOW;
    rows[4] = LOW;
    rows[5] = LOW;
    rows[6] = LOW;
    rows[7] = LOW;
    rows[8] = HIGH;
    rows[9] = HIGH;
    rows[10] = HIGH;
    rows[11] = HIGH;
    rows[12] = HIGH;
    rows[13] = HIGH;
    rows[14] = HIGH;
    rows[15] = HIGH;
    shift_out(rows);
  }

  //read_joystick();
  delay(200);
}
