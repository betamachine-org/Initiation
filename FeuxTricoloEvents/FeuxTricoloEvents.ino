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
  evLedRouge1,
  evLedOrange1,
  evLedVerte1,
  evLedRouge2,
  evLedOrange2,
  evLedVerte2,

  evStartFeu1,         // debut de sequence Vert Orange Rouge Feu N°1
  evStartFeu2,         // debut de sequence Vert Orange Rouge Feu N°2

  // evenement action
  doReset,
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

#include <BetaEvents.h>

// Gestionaires de leds specifique a ce projet

// Feu N°1
evHandlerLed  ledRouge1(evLedRouge1, pinLedRouge1, ledOn);
evHandlerLed  ledOrange1(evLedOrange1, pinLedOrange1, ledOn);
evHandlerLed  ledVerte1(evLedVerte1, pinLedVerte1, ledOn);

// Feu N°2
evHandlerLed  ledRouge2(evLedRouge2, pinLedRouge2, ledOn);
evHandlerLed  ledOrange2(evLedOrange2, pinLedOrange2, ledOn);
evHandlerLed  ledVerte2(evLedVerte2, pinLedVerte2, ledOn);



int  multi = 0; // nombre de clic rapide


void setup() {

  // Start instance`
  // will setup Serial speed at 115200 by default
  Events.begin();
  Serial.println(F("\r\n\n" APP_NAME));
  Serial.println("Bonjour ....");
}

byte BP0Multi = 0;  // detection de click rapide sur le poussoir
bool sleepOk = true;

void loop() {

  Events.get(sleepOk);  // generation du prochain evenement
  Events.handle();      // passage de l'evenement au systeme
  if (Events.code > evLed0) {
    D_println(Events.code);
    D_println(Events.ext);
  }
  switch (Events.code)  // gestion de l'evenement
  {
    case evInit: {
        Serial.println("Init");
        setFeuTricolor1(vert);
        setFeuTricolor2(rouge);
      }
      break;

    //    case evLedVerte1: {
    //        if (Events.ext == evxLedOff) {
    //          setFeuTricolor1(orange);
    //        }
    //      }
    //      break;
    //
    //    case evLedOrange1: {
    //        if (Events.ext == evxLedOff) {
    //          setFeuTricolor1(rouge);
    //          Events.delayedPush(delaiSecurite, evStartFeu1);
    //        }
    //      }
    //      break;
    //






    // Evenement pousoir
    case evBP0:
      switch (Events.ext) {
        case evxBPDown:                           // push button 0 went down
          Led0.setMillisec(500, 50);              // set led fast blink
          BP0Multi++;                             // count multi push
          Serial.println(F("BP0 Down"));          // warn user on console
          if (BP0Multi > 1) {                     // if more than 1 multi push
            Serial.print(F("BP0 Multi ="));       //   warn user
            Serial.println(BP0Multi);
          }
          break;

        case evxBPUp:                             // push button 0 went up
          Led0.setMillisec(1000, 10);             // set led slow blink
          Serial.println(F("BP0 Up"));            // warn user
          break;

        case evxBPLongDown:                       // push button is down for a long time (1.5 sec)

          // if you click fast 5 times then hold down button a reset will be done
          if (BP0Multi == 5) {                    // if multi is 5
            Serial.println(F("RESET"));           //   do a reset
            Events.push(doReset);
          }

          Serial.println(F("BP0 Long Down"));     // warn user
          break;

        case evxBPLongUp:                         // push button is up for a long time (1.5 sec)
          BP0Multi = 0;                           // raz multi who count number of fast click
          Serial.println(F("BP0 Long Up"));       // warn user
          break;

      }
      break;

    case doReset:
      helperReset();
      break;


    case evInString:
      if (Debug.trackTime < 2) {
        D_println(Keyboard.inputString);
      }
      if (Keyboard.inputString.equals("RESET")) {
        Serial.println(F("RESET"));
        Events.push(doReset);
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
// ajuste toutes les leds du feu n°1 suivant la couleur choisie pour la durée adaptée
// le rouge reste indefiniment il sera eteint par un debut de cycle (evStartFeu1)
void setFeuTricolor1(tCouleur couleur) {
  D_println(couleur + (0 * 1));
  if (couleur == vert) ledVerte1.pulse(delaiFeuVert); else ledVerte1.setOn(false);
  if (couleur == orange) ledOrange1.pulse(delaiFeuOrange); else ledOrange1.setOn(false);
  ledRouge1.setOn( couleur == rouge);
}

void setFeuTricolor2(tCouleur couleur) {

  D_println(couleur + (0 * 2));
  if (couleur == vert) ledVerte2.pulse(delaiFeuVert); else ledVerte2.setOn(false);
  if (couleur == orange) ledOrange2.pulse(delaiFeuOrange); else ledOrange2.setOn(false);
  ledRouge2.setOn( couleur == rouge);
}
