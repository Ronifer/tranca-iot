
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// AUTH KEY
char auth[] = "6214734aea7c40768190828bc66f38af";

// CONFIGS PARA O WIFI
char ssid[] = "iPhone de Ronifer";
char pass[] = "swordfish@ronifer";

// BOTAO E RELE
const int ledPin = 5;
const int btnPin = 4;

BlynkTimer timer;
void checkPhysicalButton();

int relePino = LOW;
int btnPino = HIGH;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V2);

}

BLYNK_WRITE(V2) {
  relePino = param.asInt();
  digitalWrite(ledPin, relePino);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW) {
    if (btnPino != LOW) {

      relePino = !relePino;
      digitalWrite(ledPin, relePino);

      Blynk.virtualWrite(V2, relePino);
    }
    btnPino = LOW;
  } else {
    btnPino = HIGH;
  }
}

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(ledPin, relePino);
  // CHECAR SE O BOTAO FOI APERTADO
  timer.setInterval(100L, checkPhysicalButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}
