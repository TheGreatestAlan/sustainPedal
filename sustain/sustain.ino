#include <MIDI.h>

struct MySettings : public midi::DefaultSettings
{
    static const long BaudRate = 115200;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

// the setup routine runs once when you press reset:
void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
}

// the loop routine runs over and over again forever:
bool sustain = false;
void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage= sensorValue * (5.0 / 1023.0);
  //Serial.println(voltage);

  // print out the value you read:
  if (voltage >= 3.31 && sustain == false) {
    MIDI.sendControlChange(64, 127, 1);
    sustain = true;
    //Serial.println(voltage);

    //Serial.println("Pedal down");
  }else if (voltage < 3.2 && sustain == true) {
    MIDI.sendControlChange(64, 1, 1);
    sustain = false;
    //Serial.println(voltage);

    //Serial.println("Pedal up");
  }
}
