/***************************************
 * Feu tricolore 1
 * Sequencement de 3 leds Rouge Orange Verte pour simuler un feu tricolore 
 * programation sequentielle classique 
 * 
 * (C) 2021 betamachine www.betamachine.fr
 * net234@frdev.com
 */
 
#include <Arduino.h>

// Constantes modifiable pour les durées en millisecondes
const int delaiFeuRouge  = 5000;
const int delaiFeuOrange = 2000;
const int delaiFeuVert   = 5000;

// Numéro des pin hardware pour les leds
const int pinLedRouge1  = 2;
const int pinLedOrange1 = 3;
const int pinLedVerte1  = 4;

// Type de cablage des leds
const bool ledOn  = LOW;
const bool ledOff = !ledOn;


void setup() {
  // Initialisation et feu au rouge
  pinMode(pinLedRouge1, OUTPUT);
  pinMode(pinLedOrange1, OUTPUT);
  pinMode(pinLedVerte1, OUTPUT);
  // feux au rouge par securité
  digitalWrite(pinLedRouge1, ledOn);
  digitalWrite(pinLedOrange1, ledOff);
  digitalWrite(pinLedVerte1, ledOff);
}

// boucle sequentielle rouge vert orange
void loop() {
  // feu au rouge
  digitalWrite(pinLedRouge1, ledOn);
  delay(delaiFeuRouge);
  digitalWrite(pinLedRouge1, ledOff);

  // feu au vert
  digitalWrite(pinLedVerte1, ledOn);
  delay(delaiFeuVert);
  digitalWrite(pinLedVerte1, ledOff);

  // feu a l'orange
  digitalWrite(pinLedOrange1, ledOn);
  delay(delaiFeuOrange);
  digitalWrite(pinLedOrange1, ledOff);
}
