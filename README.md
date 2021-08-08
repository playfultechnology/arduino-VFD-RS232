# arduino-VFD
Interfacing a Vacuum Fluorescent Diplay (VFD) with RS-232 interface and ESC/POS command set to Arduino

I acquired an Epson DM-D110 VFD display, sold for use as a till display. https://www.epson.eu/products/sd/pos-display/epson-dm-d110-series
It's a 12V device that uses a simple serial interface to display text and numbers, except rather than being based on the 0V-5V TTL serial signals that most modern microprocessors use, it uses that older RS232 serial interface standard, which uses voltages between +15V - -15V. 
Therefore, I'm using a MAX232 chip to convert from TTL to RS232, and a separate 12V DC supply. 
![](https://raw.githubusercontent.com/playfultechnology/arduino-VFD/main/Arduino%20VFD_bb.jpg)

The ![Technical Reference Document](https://github.com/playfultechnology/arduino-VFD-RS232/blob/main/UA0-DM-D110_TechRef.pdf) is surprisingly clear and well laid-out, and explains the full pinout in more detail (including optional connection through to thermal receipt printers etc.), though I'll be using just the minimum pins required to use the display to show text output from the Arduino, which requires GND (Pin 8), +12V (Pin 7), and the Tx output from the MAX232 connected to the Rx input of the display (Pin 3). The RS-232 standard also defines lines that indicate whether the receiving device is ready etc., but I won't be using them.

To send characters to the display, you simply issue a print() command via the AltSoftSerial library, with the char string you want to print. To send other commands, such as moving the cursor, making the display blink, altering the brightness etc., you send the bytes corresdponding to the desired ESC/POS command as defined in the ![ESC/POS CmdSet document](https://github.com/playfultechnology/arduino-VFD-RS232/blob/main/EpsonCmdSet.pdf). 

In either case, this causes the AltSoftSerial to generate a (0-5V) TTL serial output on Pin 9, which the Max232 chip then inverts and adjusts to the -15V - +15V range and delivers to the Rx pin of the display. 
