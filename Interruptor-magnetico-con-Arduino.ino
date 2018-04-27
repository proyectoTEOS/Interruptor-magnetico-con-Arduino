/*
  Created by TEOS
  Domotic with Arduino https://goo.gl/btZpjs
  YouTube https://goo.gl/k7TUSZ
  Instagram https://goo.gl/zEIjia
  Facebook https://goo.gl/eivraR
  Twitter https://goo.gl/du5Wgn
  Github https://goo.gl/Xl5IiS
  Google Plus https://goo.gl/gBnUdh
  WEB https://goo.gl/jtiYJy
*/

const int sensorPinT = 2;
int statusSensorT = HIGH;
boolean triggerT = false;

const long permanenceT = 500;
const long intervalT = 1000;
unsigned long initialTimeT = 0;
unsigned long previousMillisT = 0;
int outsetT, durationT;
String incomingT = "Switch cerrado";

void setup () {
  Serial.begin(9600);
  pinMode (sensorPinT, INPUT) ;
}

void loop () {
  unsigned long currentMillisT = millis();
  statusSensorT = digitalRead (sensorPinT) ;
  if (statusSensorT == HIGH) {
    incomingT = "Switch abierto";
    initialTimeT = millis();
    if (!triggerT) {
      Serial.println("Cambio detectado, inicia conteo");
      outsetT = initialTimeT / 1000;
      triggerT = true;
    }
  }
  else {
    if ( (millis() - initialTimeT) > permanenceT && triggerT) {
      incomingT = "Switch cerrado";
      durationT = ((millis() / 1000) - outsetT);
      Serial.println("La apertura duro: " + String (durationT) + " segundos");
      triggerT = false;
    }
  }
  if (currentMillisT - previousMillisT >= intervalT) {
    previousMillisT = currentMillisT;
    Serial.println("Estado actual: " + String (incomingT));
  }
}
