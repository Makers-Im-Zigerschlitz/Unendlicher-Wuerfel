#include <FastLED.h>
#define LED_PIN 5
#define NUM_LEDS 144  // 3*4*12=144
CRGB leds[NUM_LEDS];
int currentProgram = 1;
int buttonDebounce = 1000;

void setup() {  // void setup() Geben Sie hier Ihren Setup-Code ein, um ihn einmal auszuführen: "Aufstellung" wird beim Start einmal durchlaufen, Geschweifte Klammer ({): start der Anweisung(en)
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));  // Fülle alles schwarz
  FastLED.show();
  Serial.begin(115200);
}

void loop() {  // void loop() Geben Sie hier Ihren Hauptcode ein, um ihn wiederholt auszuführen: { Hauptprogramm als Endlosschlaufe
  switch (currentProgram) {
    case 0:
      Serial.println("Programm 0 läuft");
      onesnake(10000);  // Programm_1 > eine Schlange
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case 1:
      Serial.println("Programm 1 läuft");
      fadeFromCenter(10000);  // Programm_2 > Ausblenden von der Mitte
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case 2:
      Serial.println("Programm 2 läuft");
      rainbow(10000);  // Programm_3 > Regenbogen
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case 3:
      Serial.println("Programm 3 läuft");
      sparkles(10000);  // Programm_4 > fest füllen
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    case 4:
      Serial.println("Programm 4 läuft");
      loopThroughColors(10000);  // Programm_5 > Schleife durch Farben
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      break;
    default:
      // Statement(s)
      break;  // Wird nicht benötigt, wenn Statement(s) vorhanden sind
  }
}
// *************************************************************************
// Programm OneSnake
// *************************************************************************

void onesnake(int duration) {  // Programm_1
  unsigned long startTime;
  startTime = millis();
  int location = 1;  // Der int "Integer" ist für ein 16-bit ganzzahliger Wert. Der Wert kann von -32767 bis +32768 sein
  int nextpath = 1;
  int corners[8][3] = { { -7, 8, 1 }, { -1, 2, 3 }, { -3, 4, 5 }, { -5, 6, 7 }, { -8, -12, 9 }, { -2, -9, 10 }, { -4, -10, 11 }, { -6, -11, 12 } };
  int ledsInSnake[48];
  int color = 0;
  for (int i = 0; i < 48; i++) {  // i wird als Integer definiert. i++ bedeutet: i=i+1, Die Anweisungen werden 48 mal abgearbeitet.
    ledsInSnake[i] = 0;
  }
  while (startTime + duration > millis()) {
    // "while" Diese Schlaufe wird solange ausgeführt, wie die Bedingung erfüllt ist.
    if (location > 0) {               // Eine if-Abfrage testet eine Bedingung am Anfang der Schlaufe. Ist der Wert zutreffend, so wird die nachfolgende Anweisung ausgeführt. (falls Standort>0 dann folge der Anweisung(en)
      for (int i = 0; i < 12; i++) {  // für (
        color = (color + 5) % 2550;
        leds[ledsInSnake[0]] = CHSV(255, 255, 0);
        for (int j = 0; j < 48; j++) {
          if (j != 0) {
            leds[ledsInSnake[j]] = CHSV(color / 10, 255, (j * 255) / 48);
            ledsInSnake[j - 1] = ledsInSnake[j];
          }
        }
        ledsInSnake[47] = (location - 1) * 12 + i;
        leds[ledsInSnake[47]] = CHSV(color / 10, 255, 255);
        FastLED.show();
        delay(20);  // Programm wartet 20 msec.
      }
    }
    if (location < 0) {
      for (int i = 0; i < 12; i++) {
        color = (color + 5) % 2550;
        leds[ledsInSnake[0]] = CHSV(255, 255, 0);
        for (int j = 0; j < 48; j++) {
          if (j != 0) {
            leds[ledsInSnake[j]] = CHSV(color / 10, 255, (j * 255) / 48);
            ledsInSnake[j - 1] = ledsInSnake[j];
          }
        }
        ledsInSnake[47] = (location + 1) * -12 + 11 - i;
        leds[ledsInSnake[47]] = CHSV(color / 10, 255, 255);
        FastLED.show();
        delay(20);  // Programm wartet 20 msec.
      }
    }
    nextpath = random(0, 2);
    for (int i = 0; i < 8; i++) {  //differen 8
      if (corners[i][0] == -location || corners[i][1] == -location || corners[i][2] == -location) {
        if (corners[i][nextpath] != -location) {
          location = corners[i][nextpath];
        } else {  // falls obige Bedingung nicht stimmt, so mache folgendes....
          location = corners[i][nextpath + 1];
        }
        break;  // Mit break "ausbrechen" kann man aus jeder Schlaufe an jeder Position aussteigen.
      }
    }

    FastLED.show();
    delay(20);  // Programm wartet 20 msec.
    if (checkPoint()) { break; }
  }
}
// *************************************************************************
// Programm FadeFromCenter
// *************************************************************************
void fadeFromCenter(int duration) {  // Programm_2
  unsigned long startTime;
  startTime = millis();
  int counter = 0;
  while (startTime + duration > millis()) {
    counter = (counter + 1) % 255;
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 6; j++) {
        leds[i * 12 + j] = CHSV((counter + j * 15) % 255, 255, 255);
        leds[i * 12 + 11 - j] = CHSV((counter + j * 15) % 255, 255, 255);
      }
    }
    FastLED.show();
    delay(20);
    if (checkPoint()) { break; }
  }
}

// *************************************************************************
// Programm LoopThroughColors
// *************************************************************************
void loopThroughColors(int duration) {
  unsigned long startTime;
  startTime = millis();
  int counter = 0;
  while (startTime + duration > millis()) {
    counter = (counter + 1) % 255;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(counter, 255, 255);
    }
    FastLED.show();
    if (checkPoint()) { break; }
    delay(20);  // Programm wartet 20 msec.
  }
}
// *************************************************************************
// Programm Rainbow
// *************************************************************************
void rainbow(int duration) {  // Programm_3
  unsigned long startTime;
  startTime = millis();
  int counter = 0;
  while (startTime + duration > millis()) {  // während
    counter = (counter + 1) % 255;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV((i * 5 + counter) % 255, 255, 255);
    }
    FastLED.show();
    if (checkPoint()) { break; }
    delay(20);  // Programm wartet 20 msec.
  }
}
// *************************************************************************
// Programm Sparkles
// *************************************************************************
void sparkles(int duration) {  // Programm_4
  unsigned long startTime;     // Long ist ein erweiterter 32-bit Integer. Sein Wert ist von -2'147'483’648 bis + 2’147’483’647
  startTime = millis();
  int LENGTH = 40;  // int LENGTH = 40; Integer Länge = 40
  int blink[LENGTH];
  int color = 0;
  for (int i = 0; i < LENGTH; i++) {
    blink[i] = random(0, NUM_LEDS);
  }

  while (startTime + duration > millis()) {  // während
    color = (color + 5) % 2550;
    leds[blink[0]] = CHSV(255, 255, 0);
    for (int i = 0; i < LENGTH; i++) {
      if (i != 0) {
        leds[blink[i]] = CHSV(color / 10, 255, (i * 255) / LENGTH);
        blink[i - 1] = blink[i];
      }
    }
    blink[LENGTH - 1] = random(0, NUM_LEDS);
    FastLED.show();
    if (checkPoint()) { break; }
    delay(50);  // Programm wartet 50 msec.
  }
}

bool checkPoint() {
  if (digitalRead(3) == HIGH) {
    Serial.println("Ich gspiiire de Chnopf!");
    currentProgram += 1;
    if (currentProgram > 4) { currentProgram = 0; }
    Serial.print("Das aktuelle Programm ist nun ");
    Serial.println(currentProgram);
    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    FastLED.show();
    delay(buttonDebounce);
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
    FastLED.show();
    delay(20);
    return true;
  } else {
    return false;
  }
}