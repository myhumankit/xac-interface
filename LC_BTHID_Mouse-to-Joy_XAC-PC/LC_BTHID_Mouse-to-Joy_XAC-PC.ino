/*
Arduino 189/TeensyDuino 1.46 
HID Bluetooth library - developed by Kristian Lauszus.
 For more information visit the blog: http://blog.tkjelectronics.dk/ .
Also see for other library : 
https://github.com/felis/USB_Host_Shield_2.0
and
https://github.com/gdsports/xac-mouse2joy/blob/master/joystick_teensy_20181205.zip
 
****************
Le développement de ce code a été modifié par Christian Fromentin MHK Rennes.
Dernière modification par Florian Armange lors du Fabrikarium (projet Magic Joystick) 
*/


#include <BTHID.h>
#include <usbhub.h>
#include "MouseParser.h"


// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
// This will start an inquiry and then pair with your device - you only have to do this once
// If you are using a Bluetooth keyboard, then you should type in the password on the keypad and then press enter
BTHID bthid(&Btd, PAIR, "0000");

// After that you can simply create the instance like so and then press any button on the device
//BTHID bthid(&Btd);

MouseRptParser mousePrs;
const int bt_status_led_pin = 7;

void setup() {
  Usb.Init();
  bthid.SetReportParser(MOUSE_PARSER_ID, &mousePrs);

  // If "Boot Protocol Mode" does not work, then try "Report Protocol Mode"
  // If that does not work either, then uncomment PRINTREPORT in BTHID.cpp to see the raw report
  bthid.setProtocolMode(USB_HID_BOOT_PROTOCOL); // Boot Protocol Mode
  //bthid.setProtocolMode(HID_RPT_PROTOCOL); // Report Protocol Mode
  
  // setup status led 
  pinMode(bt_status_led_pin, OUTPUT);
}
void loop() {
  Usb.Task();
  if(bthid.connected)
  {
    digitalWrite(bt_status_led_pin, HIGH);  
  }
  else
  {
    digitalWrite(bt_status_led_pin, LOW);      
  }
}
