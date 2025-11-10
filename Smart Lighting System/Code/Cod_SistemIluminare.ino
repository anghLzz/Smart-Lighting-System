#include <DS1302.h>

#define MOSFET1_PIN 27  
#define MOSFET2_PIN 26  
#define PIR_PIN     35
#define MICROFON_PIN 25
#define FOTO_PIN     34

DS1302 rtc(5, 19, 18); // RST, DAT, CLK

unsigned long ultimaAprindere = 0;
bool luminaAmbientalaAprinsa = false;
const int pragSunet = 600;

const int boostAmbiental = 50; 
const int boostPrincipal = 30;  

void setup() {
  Serial.begin(115200);

  pinMode(MOSFET1_PIN, OUTPUT);
  pinMode(MOSFET2_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(MICROFON_PIN, INPUT);
  pinMode(FOTO_PIN, INPUT);

  ledcAttachPin(MOSFET1_PIN, 0);
  ledcSetup(0, 5000, 8);

  ledcAttachPin(MOSFET2_PIN, 1);
  ledcSetup(1, 5000, 8);

  rtc.halt(false);
  rtc.writeProtect(false);

}

void afiseazaOra(Time t) {
  Serial.print("Ora: ");
  if (t.hr < 10) Serial.print('0');
  Serial.print(t.hr);
  Serial.print(":");
  if (t.min < 10) Serial.print('0');
  Serial.print(t.min);
  Serial.print(":");
  if (t.sec < 10) Serial.print('0');
  Serial.print(t.sec);
}

void loop() {
  Time t = rtc.time();

  int miscare = digitalRead(PIR_PIN);
  int valoareSunet = analogRead(MICROFON_PIN);
  int luminaExterioara = analogRead(FOTO_PIN);

 
  int intensitateLumina = map(luminaExterioara, 100, 1023, 255, 0);
  intensitateLumina = constrain(intensitateLumina, 0, 255);

  afiseazaOra(t);
  Serial.print(" | Miscare: "); Serial.print(miscare);
  Serial.print(" | Sunet: "); Serial.print(valoareSunet);
  Serial.print(" | Lumina RAW: "); Serial.print(luminaExterioara);
  Serial.print(" | Intensitate Lumina: "); Serial.println(intensitateLumina);


  int intensitatePrincipala = 0;
  if (t.hr >= 6 && t.hr < 10) {
    intensitatePrincipala = 100;
  } else if (t.hr >= 10 && t.hr < 18) {
    intensitatePrincipala = 0;
  } else if (t.hr >= 18 && t.hr <= 22) {
    intensitatePrincipala = 255;
  } else {
    intensitatePrincipala = 0;
  }

  if (miscare == HIGH) {
    int valoareFinala = intensitatePrincipala + boostPrincipal + intensitateLumina;
    if (valoareFinala > 255) valoareFinala = 255;
    ledcWrite(0, valoareFinala);
  } else {
    ledcWrite(0, 0);
  }


  if (valoareSunet > pragSunet) {
    luminaAmbientalaAprinsa = true;
    ultimaAprindere = millis();
    Serial.println("➡️  Sunet detectat. Lumina ambientala aprinsa.");
  }

  if (luminaAmbientalaAprinsa) {
    int intensitateFinala = intensitateLumina + boostAmbiental;
    if (intensitateFinala > 255) intensitateFinala = 255;
    ledcWrite(1, intensitateFinala);

    if (millis() - ultimaAprindere > 5000) {
      ledcWrite(1, 0);
      luminaAmbientalaAprinsa = false;
      Serial.println("⏹️  Lumina ambientala oprita.");
    }
  } else {
    ledcWrite(1, 0);
  }

  delay(1000); 
}