/*
 * 
 * Contrary to my personal and professional beliefs, this is being posted without being fully tested.
 * My HC-06 refuses to change baud rate, even though several forums and walk-throughs tell me
 * it should work.  I also don't have a HC-05 or similar device to test.
 * 
 * Maybe one of you can tell me what's wrong, or just fix it in a pull request.  Thank you in 
 * advance if you help me out here!
 * 
 * This was designed to reset my BlueTooth device to a baud rate I knew, without guessing
 * at what rate it already was.
 * 
 * The BlueTooth module needs to be hooked up to pins 2 and 3 (RX, TX), or change the pin 
 * numbers for the SoftwareSerial variable below to meet your needs.
 * 
 * If the BlueTooth device isn't connected to a remote device, it should reset to 
 * whatever baud rate (baudRate) you want (see list of baud rates).
 * 
 * If the BlueTooth device is already connected, it'll at least tell you what it's
 * already set to, by sending the value to the receiving device.  The one that looks like
 * English will be your baud rate.
 * 
 * I included code to allow you to test your conntection.  Just send it a string over
 * serial, and it should pass it to the computer Serial Monitor window.
 * 
 * BTW, your BlueTooth module will need to be set to the AT command mode.  The HC-06 I  
 * used didn't need anything to be in AT command mode except for it to not be connected 
 * to a remote device.  HC-05 and others have a pin/trigger, so Google that for your 
 * sanity.
 * 
 * I am releasing this under the MIT license, ie: "not my responsibility if you use it",
 * as it is just a simple script to do some testing with.  If you hack the heck out if it, 
 * make it into a production app, and it breaks sh-tuff: not my responsibility.
 * 
 *  BTW, you will need ArduinoJson.h from : https://github.com/bblanchon/ArduinoJson/
 *  https://bblanchon.github.io/ArduinoJson/
 *
 *  The license for ArduinoJson.h is also the MIT license.
 *  
 */

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX


//  HC-06 setup
//  Comment this section out and uncomment the HC-05 section for use with that  and similar devices

String baudRate = "7";
String command = "BAUD";
String connectionBits = "";


//  HC-05 or BC417 setup
//String baudRate = "57600";
//String command = "UART=";
//String connectionBits = ",0,0";
// int atModePin = 4;  //  assumes your AT Mode pin is connected to digital pin 4

String fullCommand = command + baudRate + connectionBits;

String message;
long newBaudRate;

void setup() {
  //  uncomment the next few lines to use with a HC-05 or BC417
  /*  
   pinMode(atModePin, OUTPUT); 
   digitalWrite(ledPin, HIGH);
   */
  
  //1=1200, 2=2400, 3=4800, 4=9600 (default), 5=19200, 6=38400, 7=57600, 8=115200, 9=230400, A=460800, B=921600, C=1382400 //  all standard serial connection speeds
  BTSerial.begin(1200);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("1200");
  
  BTSerial.begin(2400);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("2400");
  
  BTSerial.begin(4800);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("4800");
  
  BTSerial.begin(9600);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("9600");
  
  BTSerial.begin(19200);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("19200");
  
  BTSerial.begin(38400);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("38400");
  
  BTSerial.begin(57600);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("57600");
  
  BTSerial.begin(115200);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("115200");
  
  BTSerial.begin(230400);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("230400");
  
  BTSerial.begin(460800);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("460800");
  
  BTSerial.begin(921600);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("921600");
  
  BTSerial.begin(1382400);
  waitForConnection();
  BTSerial.print("AT+" + fullCommand);
  BTSerial.println("1382400");

//1=1200, 2=2400, 3=4800, 4=9600 (default), 5=19200, 6=38400, 7=57600, 8=115200, 9=230400, A=460800, B=921600, C=1382400 
//  all standard serial connection speeds
  if (baudRate == "1"){
    newBaudRate = 1200;
  } else if (baudRate == "2") {
    newBaudRate = 2400;
  } else if (baudRate == "3") {
    newBaudRate = 4800;
  } else if (baudRate == "4") {
    newBaudRate = 9600;
  } else if (baudRate == "5") {
    newBaudRate = 19200;
  } else if (baudRate == "6") {
    newBaudRate = 38400;
  } else if (baudRate == "7") {
    newBaudRate = 57600;
  } else if (baudRate == "8") {
    newBaudRate = 115200;
  } else if (baudRate == "9") {
    newBaudRate = 230400;
  } else if (baudRate == "A") {
    newBaudRate = 460800;
  } else if (baudRate == "B") {
    newBaudRate = 921600;
  } else if (baudRate == "C") {
    newBaudRate = 1382400;
  } else {
    newBaudRate = baudRate.toInt();
  }
  

  BTSerial.begin(newBaudRate);
  waitForConnection();
  
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to initialize
  }
  Serial.println("Done");
}

void waitForConnection(){
  while (!BTSerial) {
    ;  // wait for serial port to initialize
  }
}

void loop() {
  if (BTSerial.available()) {  //  looks for a string from the device to send back to the computer
    message = BTSerial.readString();
    Serial.println(message);
  }
}
