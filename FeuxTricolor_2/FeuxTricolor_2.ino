/***************************************
 * Feu tricolore 2
 * Sequencement de 2 x 3 leds Rouge Orange Verte pour simuler deux feux tricolores en alternat 
 * programation sequentielle classique 
 * 
 * (C) 2021 betamachine www.betamachine.fr
 * net234@frdev.com
 */
#include <Arduino.h>

// Constantes modifiable pour les durées en millisecondes
//const int delaiFeuRouge  = 5000;
const int delaiFeuOrange = 2000;
const int delaiFeuVert   = 5000;
const int delaiSecurite  = 3000; // pause avec les deux feux au rouge

// Numéro des pin hardware pour les leds
//feu n°1
const int pinLedRouge1  = 2;
const int pinLedOrange1 = 3;
const int pinLedVerte1  = 4;
//feu n°2
const int pinLedRouge2  = 10;
const int pinLedOrange2 = 11;
const int pinLedVerte2  = 12;

// Type de cablage des leds
const bool ledOn  = LOW;
const bool ledOff = not ledOn;

void setup() {
  // Initialisation et les feux au rouge

  // feu N°1 rouge
  pinMode(pinLedRouge1, OUTPUT);
  pinMode(pinLedOrange1, OUTPUT);
  pinMode(pinLedVerte1, OUTPUT);
  digitalWrite(pinLedRouge1,ledOn);
  digitalWrite(pinLedOrange1,ledOff);
  digitalWrite(pinLedVerte1,ledOff);

  // feu N°2 rouge  
  pinMode(pinLedRouge2, OUTPUT);
  pinMode(pinLedOrange2, OUTPUT);
  pinMode(pinLedVerte2, OUTPUT);
  digitalWrite(pinLedRouge2,ledOn);
  digitalWrite(pinLedOrange2,ledOff);
  digitalWrite(pinLedVerte2,ledOff);
}

// boucle sequentielle rouge vert orange pour le feu n°1 puis idem pour le feu n°2
void loop() {
  // feu N°1 passe du rouge au vert (on suppose les 2 feux au rouge)
 digitalWrite(pinLedRouge1,ledOff);
 digitalWrite(pinLedVerte1,ledOn);
 delay(delaiFeuVert);

  // feu N°1 passe du vert à l'orange  
  digitalWrite(pinLedVerte1,ledOff);
  digitalWrite(pinLedOrange1,ledOn);
  delay(delaiFeuOrange);
 
  // feu N°1 passe de l'orange au rouge  
  digitalWrite(pinLedOrange1,ledOff);
  digitalWrite(pinLedRouge1,ledOn);
  delay(delaiSecurite);  // les 2 feux sont rouge

  // feu n°2 passe du rouge au  vert
  digitalWrite(pinLedRouge2,ledOff);
  digitalWrite(pinLedVerte2,ledOn);
  delay(delaiFeuVert);

  // feu N°2 passe du vert à l'orange  
  digitalWrite(pinLedVerte2,ledOff);
  digitalWrite(pinLedOrange2,ledOn);
  delay(delaiFeuOrange);
  
  // feu N°2 passe de l'orange au rouge  
  digitalWrite(pinLedOrange2,ledOff);
  digitalWrite(pinLedRouge2,ledOn);
  delay(delaiSecurite);  // les 2 feux sont rouges
}
