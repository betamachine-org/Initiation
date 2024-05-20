const int pinLed1 = 2;
const int pinBouton1 = 3;
int delayLed1 = 500;
const int pinLed2 = 4;
const int pinBouton2 = 5;
int delayLed2 = 500;
bool ledState1 = LOW;
bool ledState2 = LOW;
bool bp0Stat = HIGH;
bool bp1Stat = HIGH;

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

uint32_t milli1 = millis();  // heure du dernier 10Hz obtenus
uint32_t milliLed1 = millis();  // heure du dernier changement led 1
uint32_t milliLed2 = millis();  // heure du dernier changement led 2


void loop() {

    // detection de 100milliseconde pour btenir du 10Hz
  uint16_t delta = millis() - milli1;
  if (  delta >= 100 ) {
    milli1 += 100;
    // 10 Hz lecture des boutons 
  // bouton1
   if ( digitalRead(pinBouton1)  != bp0Stat ) {
    bp1Stat = !bp1Stat;
    if (bp1Stat) {
      delayLed1 = 500;
    } else {
      delayLed1 = 250;  
    }

  // bouton2
   if ( digitalRead(pinBouton1)  != bp2Stat ) {
    bp2Stat = !bp2Stat;
    if (bp2Stat) {
      delayLed2 =  500;
    } else {
      delayLed2 = 333;  
    }

  }
  // gestion des led
  if (delta > 1) {
    milliLed1 -= 1:
    if (milliLed1 <= 0) {
      
    }
 
  }
  delay(1);
}
