#include <MIDI.h>

struct MySettings : public midi::DefaultSettings
{
    static const long BaudRate = 115200;
};

bool serial = false; // this is a debug flag to do prints and read from serial, to play midi set this to false
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

// the setup routine runs once when you press reset:
void setup() {
  if(serial){
    Serial.begin(115200);
  }else{
    MIDI.begin(MIDI_CHANNEL_OMNI);
  }
}

// the loop routine runs over and over again forever:
bool sustain = false;
int actualChangeDown = 0;

void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage= sensorValue * (5.0 / 1023.0);
  
  if( sustain == false ) {
    if ((voltage >= 3.30 && voltage < 3.32)) {
      actualChangeDown = actualChangeDown + 1;
      if( actualChangeDown >= 10){
        if(serial){
          Serial.println(voltage);
          Serial.println(sustain);
          Serial.println("Pedal changing down");
        }else{
          MIDI.sendControlChange(64, 127, 1);
        }
        sustain = true;
        actualChangeDown = 0;
      }
    } else {
      actualChangeDown = 0;
            //Serial.println("Pedal held up");

    }
  } else{
      if (voltage < 3.20 || voltage > 3.4) {
      sustain = false;
      if(serial){
        Serial.println(voltage);   
        Serial.println(sustain);
        Serial.println("Pedal changing up");
      }else{
        MIDI.sendControlChange(64, 1, 1);

      }
  
    } else{
      if(serial){
        //Serial.println("Pedal held down");
      }
  
    }
  }
}
