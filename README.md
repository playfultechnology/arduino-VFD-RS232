# arduino-VFD
Interfacing a Vacuum Fluorescent Diplay (VFD) with RS-232 interface and ESC/POS command set to Arduino

I acquired an Epson DM-D110 VFD display, sold for use as a till display. https://www.epson.eu/products/sd/pos-display/epson-dm-d110-series
It's a 12V device that uses a simple serial interface to display text and numbers, except rather than being based on the 0V-5V TTL serial signals that most modern microprocessors use, it uses that older RS232 serial interface standard, which uses voltages between +15V - -15V. 
Therefore, I'm using a MAX232 chip to convert from TTL to RS232, and a separate 12V DC supply. 
![](https://raw.githubusercontent.com/playfultechnology/arduino-VFD/main/Arduino%20VFD_bb.jpg)

The ![Technical Reference Document](https://github.com/playfultechnology/arduino-VFD-RS232/blob/main/UA0-DM-D110_TechRef.pdf) is surprisingly clear and well laid-out, and explains the full pinout in more detail (including optional connection through to thermal receipt printers etc.), though I'll be using just the minimum pins required to use the display to show text output from the Arduino, which requires GND (Pin 8), +12V (Pin 7), and the Tx output from the MAX232 connected to the Rx input of the display (Pin 3). The RS-232 standard also defines lines that indicate whether the receiving device is ready etc., but I won't be using them.
