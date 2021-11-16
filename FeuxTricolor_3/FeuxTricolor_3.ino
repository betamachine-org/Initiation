/***************************************
   Feu tricolore 3
   Sequencement de 2 x 3 leds Rouge Orange Verte pour simuler deux feux tricolores en alternat
   programation sequentielle classique

   fonctionnement identique a Feu tricolore 2 ou 2b 
   avec un poussoir pour passer immédiatement en "orange cligotant"

   (C) 2021 betamachine www.betamachine.fr
   net234@frdev.com
*/
#include <Arduino.h>

// Constantes modifiable pour les durées en millisecondes
const int delaiFeuOrange = 2000;
const int delaiFeuVert   = 5000;
const int delaiSecurite  = 3000; // pause avec les deux feux au rouge
const int delaiClignotant= 1000;

// Numéro des pin hardware pour le bouton
const int pinBouton1 = 5;

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
typedef enum { rouge, orange, vert, off } tCouleur;


void setup() {

  // Initialisation du bouton
  pinMode(pinBouton1, INPUT_PULLUP);
  
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
// avec gestion d'un pousoir pour clignoter orange
void loop() {
  // le "do" (se prononce "dou") permet de sortir du bloc "do { ... } while" avec un "break"
  do {
    setFeuTricolor1(vert);
    if (boutonOuAttente(delaiFeuVert)) break; // si le bouton est enfoncé on vas directement apres le while
    setFeuTricolor1(orange);
    if (boutonOuAttente(delaiFeuOrange)) break;
    setFeuTricolor1(rouge);
    if (boutonOuAttente(delaiSecurite)) break;
    setFeuTricolor2(vert);
    if (boutonOuAttente(delaiFeuVert)) break;
    setFeuTricolor2(orange);
    if (boutonOuAttente(delaiFeuOrange)) break;
    setFeuTricolor2(rouge);
    if (boutonOuAttente(delaiSecurite)) break;
  } while (false);
  
  // tant que le bouton est enfoncé on clignote orange
  while ( boutonEnfonce() ) {
    // clignotement 
    setFeuTricolor1(orange);
    setFeuTricolor2(orange);
    delay(delaiClignotant);
    setFeuTricolor1(off);
    setFeuTricolor2(off);
    delay(delaiClignotant);

    // sortie du clignotement ?
    if ( not boutonEnfonce() ) {
      // le bouton est relaché on passe au rouge
      setFeuTricolor1(rouge);
      setFeuTricolor2(rouge);
      delay(delaiSecurite);
    }
    
  }
}


// ---------------  fonctions  ------------------------------------------------

// si le bouton n'est pas enfoncé on attends le delai demandé et on retourne false
// si le bouton est enfoncé on retourne immédiatement true
// le bouton est testé 10 x par secondes pour repondre rapidement mais eviter les rebonds
bool boutonOuAttente(int unDelais) {
  while (unDelais > 0) {
    if ( boutonEnfonce() ) return (true);
    delay(100);
    unDelais = unDelais - 100;
  };
  return (false); // false car le bouton n'est pas enfoncé
}


// gestion du bouton
// renvois true si le bouton est enfoncé
bool boutonEnfonce() {
  return ( digitalRead(pinBouton1) == LOW );
}


// gestion du feu N° 1
// ajuste toutes les leds du feu n°1 suivant la couleur choisie
void setFeuTricolor1(tCouleur couleur) {
  digitalWrite(pinLedVerte1, (couleur == vert)   ? ledOn : ledOff);
  digitalWrite(pinLedOrange1, (couleur == orange) ? ledOn : ledOff);
  digitalWrite(pinLedRouge1, (couleur == rouge)  ? ledOn : ledOff);
}

// gestion du feu N° 2
// ajuste toutes les leds du feu n°2 suivant la couleur choisie
void setFeuTricolor2(tCouleur couleur) {
  digitalWrite(pinLedVerte2, (couleur == vert)   ? ledOn : ledOff);
  digitalWrite(pinLedOrange2, (couleur == orange) ? ledOn : ledOff);
  digitalWrite(pinLedRouge2, (couleur == rouge)  ? ledOn : ledOff);
}
