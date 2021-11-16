/*************************************************
 *************************************************

  Sequencement de 2 x 3 leds Rouge Orange Verte pour simuler deux feux tricolores en alternat
  programation evenementielle avec la lib BetaEvents (EventsManager) Betamachine

  Sketch FeuTricoloreEvents.ino   validation of lib betaEvents to deal nicely with events programing with Arduino
  Copyright 2020 Pierre HENRY net23@frdev.com All - right reserved.



  This file is part of betaEvents.

    betaEvents is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    betaEvents is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with betaEvents.  If not, see <https://www.gnu.org/licenses/lglp.txt>.



 *************************************************/

#define APP_NAME "FeuTricoloreEvents V1.0"

// Constantes modifiable pour les durées en millisecondes
const int delaiFeuOrange = 2000;
const int delaiFeuVert   = 5000;
const int delaiSecurite  = 3000; // pause avec les deux feux au rouge
const int delaiClignotant = 1000;

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



/* Evenements du Manager (voir EventsManager.h)
  evNill = 0,      // No event  about 1 every milisecond but do not use them for delay Use pushDelayEvent(delay,event)
  ev100Hz,         // tick 100HZ    non cumulative (see betaEvent.h)
  ev10Hz,          // tick 10HZ     non cumulative (see betaEvent.h)
  ev1Hz,           // un tick 1HZ   cumulative (see betaEvent.h)
  ev24H,           // 24H when timestamp pass over 24H
  evInit,
  evInChar,
  evInString,
*/

// Liste des evenements specifique a ce projet
enum tUserEventCode {
  // evenement utilisateurs
  evBP0 = 100,        //pousoir D5  (passage en mode clignotant)
  evLed0,             //Led de vie clignotante (LED_BUILTIN)
  evSetFeu1,         // gestion sequence Vert Orange Rouge Feu N°1
  evSetFeu2,         // gestion sequence Vert Orange Rouge Feu N°2
  evFeuxClignotants,  // gestion clignotement feux 1 et 2

};


//  betaEvent.h est une aide pour construire les elements de base d'une programation evenementiel

//  une instance "Events" avec un poussoir "BP0" une LED "Led0" un clavier "Keyboard"
//  BP0 genere un evenement evBP0 a chaque pression le poussoir connecté sur BP0_PIN
//  Led0 genere un evenement evLed0 a chaque clignotement de la led precablée sur la platine LED_BUILTIN
//  Keyboard genere un evenement evChar a char caractere recu et un evenement evString a chaque ligne recue
//  Debug permet sur reception d'un "T" sur l'entrée Serial d'afficher les infos de charge du CPU

//#define BP0_PIN   5                //   Par defaut BP0 est sur D5
//#define Led0_PIN  LED_BUILTIN      //   Par defaut Led0 est sur LED_BUILTIN
//#define SERIAL_SPEED 115200        //   Default at 115200
//#define NO_SERIAL                  //   Par defaut Serial est actif : enlevez le commentaire si vous n'en souhaitez pas (economie de memoire)
//#define NO_DEBUG                   //   Par defaut EventDebug est actif : enlevez le commentaire si vous n'en souhaitez pas (economie de memoire)

#include <BetaEvents.h>


void setup() {

  // Start instance`
  // will setup Serial speed at 115200 by default
  Events.begin();
  Serial.println(F("\r\n\n" APP_NAME));

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

  Serial.println("Bonjour ....");
}

bool sleepOk = true;

void loop() {

  Events.get(sleepOk);  // generation du prochain evenement
  Events.handle();      // passage de l'evenement au systeme
  //  if (Events.code > evLed0) {
  //    D_println(Events.code);
  //    D_println(Events.ext);
  //  }
  switch (Events.code)  // gestion de l'evenement
  {
    case evInit: {
        Serial.println("Init");
        Events.push(evSetFeu1, vert); // Debut de sequence Vert Orange Rouge Feu n° 1
      }
      break;

    // Gestion sequence Vert Orange Rouge Feu n° 1
    case evSetFeu1: {
        tCouleur couleur = (tCouleur)Events.ext;
        setFeuTricolor1(couleur);
        switch (couleur) {
          case vert: Events.delayedPush(delaiFeuVert, evSetFeu1, orange); break;
          case orange: Events.delayedPush(delaiFeuOrange, evSetFeu1, rouge); break;
          case rouge: Events.delayedPush(delaiSecurite, evSetFeu2, vert); break;
        }
      }
      break;

    // Gestion sequence Vert Orange Rouge Feu n° 1
    case evSetFeu2: {
        tCouleur couleur = (tCouleur)Events.ext;
        setFeuTricolor2(couleur);
        switch (couleur) {
          case vert: Events.delayedPush(delaiFeuVert, evSetFeu2, orange); break;
          case orange: Events.delayedPush(delaiFeuOrange, evSetFeu2, rouge); break;
          case rouge: Events.delayedPush(delaiSecurite, evSetFeu1, vert); break;
        }
      }
      break;

     // Gestion Clignotement
    case evFeuxClignotants: {
        tCouleur couleur = (tCouleur)Events.ext;
        setFeuTricolor1(couleur);
        setFeuTricolor2(couleur);
        switch (couleur) {
          case off: Events.delayedPush(delaiClignotant, evFeuxClignotants, orange); break;
          case orange: Events.delayedPush(delaiClignotant, evFeuxClignotants, off); break;
        }
      }
      break;




    // Evenement pousoir
    case evBP0:
      switch (Events.ext) {
        case evxBPDown:                           // push button 0 went down
          Led0.setMillisec(500, 50);              // set led fast blink
          Serial.println(F("BP0 Down"));          // warn user on console
          // Feu en orange clignotant
          Events.removeDelayEvent(evSetFeu1);
          Events.removeDelayEvent(evSetFeu2);
          Events.push(evFeuxClignotants, orange); break;
          break;

        case evxBPUp:                             // push button 0 went up
          Led0.setMillisec(1000, 10);             // set led slow blink
          Serial.println(F("BP0 Up"));            // warn user
          Events.removeDelayEvent(evFeuxClignotants);
          setFeuTricolor1(rouge);
          setFeuTricolor2(rouge);
          Events.delayedPush(delaiSecurite,evSetFeu1, vert); break;
          break;


      }
      break;


    case evInString:
      if (Debug.trackTime < 2) {
        D_println(Keyboard.inputString);
      }
      if (Keyboard.inputString.equals("S")) {
        //            if (Events.aStringPtr->equals("S")) {

        sleepOk = !sleepOk;
        D_println(sleepOk);
      }

      break;

  }
}

// gestion du feu N° 1
// ajuste toutes les leds du feu n°1 suivant la couleur choisie
void setFeuTricolor1(tCouleur couleur) {
  digitalWrite(pinLedVerte1,  (couleur == vert)   ? ledOn : ledOff);
  digitalWrite(pinLedOrange1, (couleur == orange) ? ledOn : ledOff);
  digitalWrite(pinLedRouge1,  (couleur == rouge)  ? ledOn : ledOff);
}

// gestion du feu N° 2
// ajuste toutes les leds du feu n°2 suivant la couleur choisie
void setFeuTricolor2(tCouleur couleur) {
  digitalWrite(pinLedVerte2,  (couleur == vert)   ? ledOn : ledOff);
  digitalWrite(pinLedOrange2, (couleur == orange) ? ledOn : ledOff);
  digitalWrite(pinLedRouge2,  (couleur == rouge)  ? ledOn : ledOff);
}
