/**
 * Code to control an Epson DM-D110 Vacuum Fluorescent Display (VFD),
 * as often used as till displays and other Point-Of-Sale devices.
 * 
 * This is a 12V, 20 character x 2 line display, that uses the RS232 serial interface
 * Datasheet can be found at https://files.support.epson.com/pdf/pos/bulk/d110u_e_3.pdf
 * 
 * Sending data over RS-232 interface is somewhat similar to Serial connection used by  
 * Arduino, but has inverted logic, and biased to voltages between -5 and -15V (Logic "1", or "Mark")
 * and between +5V and +15V (Logic "0", or "Space").
 * Thus, some additional hardware is required to convert the serial output from the Arduino GPIO pins
 * One example is shown here: https://sites.google.com/site/whitej/arduinoextras
 * However, a muxh simpler solution is to use an RS232-TTl convertor based on the MAX3232 chip, such as 
 * https://www.ebay.co.uk/itm/264813352756
 * 
 * The pinout of the D110 is exposed via an RJ45 connector, with pinout as follows:
 * 1 FG - Frame ground 
 * 2 TXD - Output
 * 3 RXD - Input Receives data from the computer.
 * 4 DSR - Input Indicates whether the computer/TM printer is ready to receive data (SPACE = Ready, MARK = Not Ready)
 * 5 RTS - Output This indicates whether the display is ready to receive data. *2
 * 6 SG - Signal GND 
 * 7 PS - Power supply terminal
 * 8 PG - Return wire for power
 * 
 * Pin1, 6 and 8 should be connected to GND, Pin7 to +12V, and Pin 3 to the output from the MAX3232. 
 * 
 * */

// INCLUDES
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#include <AltSoftSerial.h>

// GLOBALS
// AltSoftSerial constructor takes no parameters, and always uses these pins:
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12
AltSoftSerial altSerial;


// HELPER FUNCTIONS
// These are ESC/POS commands as defined in https://sites.google.com/site/whitej/EpsonCmdSet.pdf
/*
 * Moves cursor to specified position
 * Note that values are 1-indexed, not 0-indexed, so first character of bottom row is (1,2)
 */
void SetCursor(byte column, byte row){
  altSerial.write(0x1F);
  altSerial.write(0x24);
  altSerial.write(column);
  altSerial.write(row);
}

void Clear(){
  altSerial.write(0x0C);
}

void ClearCursorLine(){
  altSerial.write(0x18);
}

void CursorOn() {
  altSerial.write(0x1F);
  altSerial.write(0x43);
  altSerial.write(0x01);
}

void CursorOff() {
  altSerial.write(0x1F);
  altSerial.write(0x43);
  altSerial.write((byte)0x00);
}

void CursorHome() {
  altSerial.write(0x0B);
}


void setup() {
  // Serial connection to PC
  Serial.begin(9600);
  Serial.println(__FILE__ __DATE__);

  // Initialise pins used for connection to VFD (via Max3232)
  pinMode(8, INPUT); // Rx (not used)
  pinMode(9, OUTPUT); // Tx 

  // Start the software serial emulation on the pins above
  altSerial.begin(9600);

  // Initialise the display
  altSerial.write(0x1B);
  altSerial.write(0x40);

  // This clears the screen
  altSerial.write(0x0C);
  delay(100);
  
  // Move the cursor to home position
  altSerial.write(0x0B);
  
  delay(100);
  
  altSerial.write("Well, this is a");
  SetCursor(1,2);
  altSerial.write("surprise!");
  
  CursorOff();
  // Executes self-test
  /*
  altSerial.write(0x1F);
  altSerial.write(0x40);
  */

  /*
  // This displays the time!
  // From p.36 of http://support.j2rs.com/Documents/OldDocs/VFD%20Pole%20Display.pdf
  altSerial.write(0x1F);
  altSerial.write(0x55);

  // This clears the screen
  altSerial.write(0x0C);
  // Move the cursor to home position
  altSerial.write(0x0B);
  */
}

unsigned long lastWriteTime = 0;

void loop() {
/*
  unsigned long now = millis();
  
  if(now - lastWriteTime > 3000){
    CursorHome();
    ClearCursorLine();
    char buffer[20];
    sprintf(buffer, "Time Elapsed: %ds", (millis()/1000));
    altSerial.write(buffer);
    lastWriteTime = now;
  }
*/
  // Pass through any data typed via the serial monitor
  if(Serial.available() > 0) {
    byte c = Serial.read();
    if(c == 0x0A || c == 0x0D) { // 0x0A = \n (newline), 0x0D = \r (Carriage Return)
      CursorHome();
    }
    else {
      altSerial.write(c);
    }
  }
}
