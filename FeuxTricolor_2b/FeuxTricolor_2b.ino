/***************************************
   Feu tricolore 2b
   Sequencement de 2 x 3 leds Rouge Orange Verte pour simuler deux feux tricolores en alternat
   programation sequentielle classique

   fonctionnement identique a Feu tricolore 2 mais ajout de fonctions 'setFeuTricolor'
   pour une meilleur lisibilité du code dans la partie Loop()

   (C) 2021 betamachine www.betamachine.fr
   net234@frdev.com
*/
#include <Arduino.h>

// Constantes modifiable pour les durées en millisecondes
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

// liste des couleurs possibles pour les fonctions "setFeuTricolor"
typedef enum { rouge, orange, vert } tCouleur;


void setup() {
  // Initialisation et les feux au rouge

  // feu N°1 rouge
  pinMode(pinLedRouge1, OUTPUT);
  pinMode(pinLedOrange1, OUTPUT);
  pinMode(pinLedVerte1, OUTPUT);
  setFeuTricolor1(rouge);

  // feu N°2 rouge
  pinMode(pinLedRouge2, OUTPUT);
  pinMode(pinLedOrange2, OUTPUT);
  pinMode(pinLedVerte2, OUTPUT);
  setFeuTricolor2(rouge);
}

// boucle sequentielle rouge vert orange pour le feu n°1 puis idem pour le feu n°2
// le code est plus claire que la version "FeuxTricolore2"

void loop() {
  setFeuTricolor1(vert);
  delay(delaiFeuVert);

  setFeuTricolor1(orange);
  delay(delaiFeuOrange);

  setFeuTricolor1(rouge);
  delay(delaiSecurite);

  setFeuTricolor2(vert);
  delay(delaiFeuVert);

  setFeuTricolor2(orange);
  delay(delaiFeuOrange);

  setFeuTricolor2(rouge);
  delay(delaiSecurite);
}

// gestion du feu N° 1
// ajuste toutes les leds du feu n°1 suivant la couleur choisie
void setFeuTricolor1(tCouleur couleur) {
  if (couleur == vert) {
    digitalWrite(pinLedVerte1, ledOn);
  } else {
    digitalWrite(pinLedVerte1, ledOff);
  }
  if (couleur == rouge) {
    digitalWrite(pinLedRouge1, ledOn);
  } else {
    digitalWrite(pinLedRouge1, ledOff);
  }
  if (couleur == orange) {
    digitalWrite(pinLedOrange1, ledOn);
  } else {
    digitalWrite(pinLedOrange1, ledOff);
  }
}

// pour les habitué du code il est possible de remplacer
//  if (couleur == vert) {
//    digitalWrite(pinLedVerte1, ledOn);
//  } else {
//    digitalWrite(pinLedVerte1, ledOff);
//  }

// par
//  digitalWrite(pinLedVerte1, (couleur == vert)   ? ledOn : ledOff);

// voir meme pour logiciens :)
//  digitalWrite(pinLedVerte1, (couleur == vert) xor ledOff);



// gestion du feu N° 2
// ajuste toutes les leds du feu n°2 suivant la couleur choisie
void setFeuTricolor2(tCouleur couleur) {
  digitalWrite(pinLedVerte2,  (couleur == vert)   ? ledOn : ledOff);
  digitalWrite(pinLedOrange2, (couleur == orange) ? ledOn : ledOff);
  digitalWrite(pinLedRouge2,  (couleur == rouge)  ? ledOn : ledOff);
}
