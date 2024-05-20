const int pinLed1 = 2;
const int pinBouton1 = 3;
int varBouton1 = 0;
const int pinLed2 = 4;
const int pinBouton2 = 5;
int varBouton2 = 0;
unsigned long currentTime = 0;
unsigned long previousTime = 0;
bool ledState1 = LOW;
bool ledState2 = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  //Serial.begin(116000);
  Serial.println("Initialisation...");
  pinMode(pinLed1, OUTPUT);
  pinMode(pinBouton1, INPUT_PULLUP);  //pinMode(pinBouton1, INPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinBouton2, INPUT_PULLUP);  //pinMode(pinBouton2, INPUT);
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  Serial.println("...Fin de l'initialisation");
}

void loop() {
  // put your main code here, to run repeatedly:
  varBouton1 = digitalRead(pinBouton1);
  varBouton2 = digitalRead(pinBouton2);
  currentTime = millis();
  while (varBouton1 == HIGH && varBouton2 == HIGH) {
    currentTime = millis();
    if ((currentTime - previousTime) > 500) {
      previousTime = currentTime;
      ledState1 = !ledState1;
      ledState2 = !ledState2;
      digitalWrite(pinLed1, !ledState1);
      digitalWrite(pinLed2, !ledState2);
    }
  }
  while (varBouton1 == LOW && varBouton2 == LOW) {
    currentTime = millis();
    if ((currentTime - previousTime) > 1000) {
      previousTime = currentTime;
      ledState1 = !ledState1;
      ledState2 = !ledState2;
      digitalWrite(pinLed1, !ledState1);
      digitalWrite(pinLed2, !ledState2);
    }
  }
  while (varBouton1 == HIGH) {
    currentTime = millis();
    if ((currentTime - previousTime) > 500) {
      previousTime = currentTime;
      ledState1 = !ledState1;
      digitalWrite(pinLed1, !ledState1);
    }
  }
  while (varBouton1 == LOW) {
    currentTime = millis();
    if ((currentTime - previousTime) > 1000) {
      previousTime = currentTime;
      ledState1 = !ledState1;
      digitalWrite(pinLed1, !ledState1);
    }
  }
  while (varBouton2 == HIGH) {
    currentTime = millis();
    if ((currentTime - previousTime) > 500) {
      previousTime = currentTime;
      ledState2 = !ledState2;
      digitalWrite(pinLed2, !ledState2);
    }
  }
  while (varBouton2 == LOW) {
    currentTime = millis();
    if ((currentTime - previousTime) > 500) {
      previousTime = currentTime;
      ledState2 = !ledState2;
      digitalWrite(pinLed2, !ledState2);
    }
  }
}
