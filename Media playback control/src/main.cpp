/**
 * By Mwangi Gregory 
 * 
 * This code configures the ESP32 as a Bluetooth keyboard. In this case, the
 * ESP32 will act as a media controller, sending the commands to play the next
 * or previous track. This is possible due to the widely implemented HID 
 * protocol that is used to interface devices used by humans, such as keyboards,
 * mice, and joysticks with a computer system.
 * The ESP32 will be connected to two buttons, one to play the next track and
 * the other to play the previous track.
 * The ESP32 will be connected to the computer or phone via Bluetooth, and the 
 * commands will be sent to the computer as if they were coming from a keyboard.
 * 
*/
#include <Arduino.h>
#include <BleKeyboard.h>
#define BTN_NEXT 22
#define BTN_PREV 23

byte playNextPrevState = 1;
byte playPreviousPrevState = 1;
byte playNextState = 1;
byte playPrevState = 1;

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
}

void loop() {
  playNextState = digitalRead(BTN_NEXT);
  playPrevState = digitalRead(BTN_PREV);

  if (playNextState == LOW) {
    if (playNextState == LOW && playNextPrevState == HIGH) { // debounce
      if (bleKeyboard.isConnected()) {
        Serial.println("Play next");
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
      } else {
        Serial.println("Bluetooth not connected...");
      }
      playNextPrevState = playNextState;
    }
  } else {
    playNextPrevState = playNextState;
  }

  if (playPrevState == LOW) {
    if (playPrevState == LOW && playPreviousPrevState == HIGH) { // debounce
      if (bleKeyboard.isConnected()) {
        Serial.println("Play previous");
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
      } else {
        Serial.println("Bluetooth not connected...");
      }
      playPreviousPrevState = playPrevState;
    }
  } else {
    playPreviousPrevState = playPrevState;
  }

}
