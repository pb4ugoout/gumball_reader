This project has several goals:

1.) Allow RFID card access to a gumball machine via a relay
2.) Allow for RFID card numbers to be saved
3.) Known card numbers will trip the relay and flash the neopixel ring green.
4.) Unknown card numbers will only flash the ring red.
5.) The save process is initiated via a button press and lasts for a predetermined amount of time.
6.) During this window a neopixel ring will also run through a color wheel program.

Problems:

1.) Currently the button press initiates the color wheel function for a set number of cycles of the wheel using delays.
Delays cannot be used for this sketch as they halt all other processing and do not allow the reader to learn card numbers
2.) There is currently no method for saving/storing card numbers so that they can be called and match by the card read function
An external SD card reader may be needed to save the data

Working:

1.) The sketch will successfully read any RFID card and trigger the relay which in turn simulates a coin drop in the gumball machine
2.) Card numbers are viewable via the serial monitor and the wiegand library is working as it should
3.) A press of the button will cause the neopixel ring to run through the color wheel function