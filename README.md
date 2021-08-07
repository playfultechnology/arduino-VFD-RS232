# arduino-VFD
Interfacing a Vacuum Fluorescent Diplay (VFD) to Arduino

I acquired an Epson DM-D110 VFD display, sold for use as a till display. https://www.epson.eu/products/sd/pos-display/epson-dm-d110-series
It's a 12V device that uses a simple serial interface to display text and numbers, except rather than being based on the 0V-5V TTL serial signals that the Arduino uses, it uses that older RS232 serial interface standard, which uses voltages between +15V - -15V. 
Therefore, I'm using a MAX232 chip to convert from TTL to RS232, and a separate 12V DC supply. 
![](https://raw.githubusercontent.com/playfultechnology/arduino-VFD/main/Arduino%20VFD_bb.jpg)
