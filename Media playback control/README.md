# Media PlayBack Control

This code configures the ESP32 as a Bluetooth keyboard. In this case, the ESP32 will act as a media controller, sending the commands to play the next or previous track. 

This is possible due to the widely implemented HID protocol that is used to interface devices used by humans, such as keyboards,
mice, and joysticks with a computer system.

The ESP32 will be connected to two buttons, one to play the next track and the other to play the previous track. The ESP32 will be connected to the computer or phone via Bluetooth, and the commands will be sent to the computer as if they were coming from a keyboard.

Here is a link I used to learn about this functionality of the esp32:
[link](https://www.hackster.io/user0448083246/esp32-ble-hid-keyboard-37a103)