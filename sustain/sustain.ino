#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// the setup routine runs once when you press reset:
void setup() {
  MIDI.begin();
}

// the loop routine runs over and over again forever:
bool sustain = false;
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  if (voltage >= 3.1 && sustain == false) {
    MIDI.sendNoteOn(66, 127, 1);
    sustain = true;
  }
  if (voltage != 3.1 && sustain == true) {
    MIDI.sendNoteOn(66, 0, 1);
    sustain = false;
  }
}
