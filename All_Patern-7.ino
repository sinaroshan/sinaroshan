char CharSerialPort;

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 10;

int cunter = 0;
int NUM_pin = 0;
int pot_cunter;
int pinBright = 10;
int pot_bright;
byte NUM_pin_prev = 0;
byte patern_num = 0;
byte patern_var = 0;

void setup() {
  Serial.begin(115200);
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  ResetAll();
}

void loop() {
  if (Serial.available() > 0) {
    CharSerialPort = Serial.read();
  }

  pot_cunter = analogRead(A0);
  pot_cunter = map(pot_cunter, 0, 1023, 50, 1000);

  pot_bright = analogRead(A1);
  pot_bright = map(pot_bright, 0, 1023, 0, 255);

  //Serial.println(CharSerialPort);
  // Serial.println(patern_num);

  analogWrite(10, pot_bright);  //pin 12 for PWM Brightness

  switch (CharSerialPort)  // تنظیمات اولیه پترن ها
  {
    case '1':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 2;
      patern_num = 1;
      break;
    case '2':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 3;
      patern_num = 2;
      break;
    case '3':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 2;
      patern_num = 3;
      patern_var = 2;
      break;
    case '4':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);  // Flasher all
      //NUM_pin =  3;
      patern_num = 4;
      patern_var = 1;
      break;
    case '5':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 1;
      patern_num = 5;
      patern_var = 0;
      break;
    case '6':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 1;
      patern_num = 6;
      patern_var = 0;
      break;
    case '7':
      CharSerialPort = 0;
      ResetAll();
      Serial.print("patern_num: ");
      Serial.println(CharSerialPort);
      NUM_pin = 0;
      patern_num = 7;
      patern_var = 0;
      break;
  }

  switch (patern_num)  // فراخانی ووید پترن مورد نظر
  {
    case 1:
      patern_1();
      break;
    case 2:
      patern_2();
      break;
    case 3:
      patern_3();
      break;
    case 4:
      patern_4();
      break;
    case 5:
      patern_5();
      break;
    case 6:
      patern_6();
      break;
    case 7:
      patern_7();
      break;
  }
}  // END void loop
////////////////////////////////////  patern 1
void patern_1() {
  const long interval = pot_cunter;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    NUM_pin = NUM_pin + 1;

    digitalWrite(NUM_pin - 1, LOW);

    if (NUM_pin > 9) {
      NUM_pin = 2;
    }
  }
  digitalWrite(NUM_pin, HIGH);
}  //END Patern_1

////////////////////////////////////  patern 2
void patern_2() {

  const long interval = pot_cunter;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    NUM_pin_prev = NUM_pin;
    NUM_pin = NUM_pin - 1;
    digitalWrite(NUM_pin_prev, LOW);
    digitalWrite(9 - NUM_pin_prev + 2, LOW);

    if (NUM_pin < 2) {
      NUM_pin = 5;
    }
  }

  digitalWrite(NUM_pin, HIGH);
  digitalWrite(9 - NUM_pin + 2, HIGH);

}  //END Patern_2

////////////////////////////////////  patern 3
void patern_3() {
  //cunter = cunter + 1;

  const long interval = pot_cunter;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    NUM_pin += 1;
    patern_var += 1;
    if (NUM_pin > 9) {
      NUM_pin = 2;
    }
  }  // if (currentMillis - previousMillis >= interval)

  if (patern_var < 10) {
    digitalWrite(NUM_pin, HIGH);
  }
  if (patern_var > 9) {
    digitalWrite(NUM_pin, LOW);
  }
  if (patern_var == 18) {
    patern_var = 2;
  }

}  //END Patern_3

////////////////////////////////////  patern 4
void patern_4() {


  const long interval = pot_cunter;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  cunter = 0;
  for (int i = 2; i < 10; i++) {
    digitalWrite(i, ledState);
  }
}  //END Patern_5

void patern_5() {
  //cunter = cunter + 1;

  const long interval = pot_cunter;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (NUM_pin < 10 && patern_var < 9) {
      NUM_pin += 1;
      patern_var += 1;
      digitalWrite(NUM_pin, HIGH);
    } else {
      NUM_pin -= 1;
      digitalWrite(NUM_pin, LOW);
    }
  }

  if (NUM_pin == 1 && patern_var == 9) {
    patern_var = 0;
  }

}  //END Patern_5

////////////////////////////////////  patern 6
void patern_6() {
  const long interval = pot_cunter;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    NUM_pin += 1;
    for (int i = NUM_pin; i < NUM_pin + 3; ++i) {
      digitalWrite(i, HIGH);
    }

    digitalWrite(NUM_pin - 1, LOW);

    if (NUM_pin > 7) {
      for (int i = NUM_pin; i < NUM_pin + 3; ++i) {
        digitalWrite(i, LOW);
      }
      NUM_pin = 1;

      for (int i = NUM_pin; i < NUM_pin + 4; ++i) {
        digitalWrite(i, HIGH);
      }
      NUM_pin = 2;
    }
  }

}  //END Patern_6

////////////////////////////////////  patern 7
void patern_7() {
  const long interval = pot_cunter;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    NUM_pin += 1;
    if (NUM_pin < 3) {
      for (int i = NUM_pin; i < 11; i += 2) {

        digitalWrite(i, HIGH);
        int j = i - 1;
        digitalWrite(j, LOW);
      }
    }
    if (NUM_pin == 2) {
      NUM_pin = 0;
    }
  }
}

//END Patern_7

////////////////////////////////// Reset All
void ResetAll() {
  for (int i = 2; i < 10; i++) {
    digitalWrite(i, LOW);
  }
}
