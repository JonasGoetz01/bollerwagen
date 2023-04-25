#include <Arduino.h>
#include "../variables.h"
#include "pitches.h"
#include "buzzer.h"

void Buzzer::initialize() {
  ledcSetup(0, 1000, 1);
}

void Buzzer::startSound() {
  //Melodie definieren
  int melody[] = {
    NOTE_C5, NOTE_G5, NOTE_C6, NOTE_G5,
    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_C5,
    NOTE_D5, NOTE_G5, NOTE_B5, NOTE_G5,
    NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
  int noteDurations[] = {
    8, 8, 8, 8,
    8, 8, 8, 8,
    8, 8, 8, 8,
    4, 4, 4, 4
  };

  //Startsound spielen
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}