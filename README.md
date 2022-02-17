### MuskCartridge
This project is based in the devebox stm32h743vti board (https://www.aliexpress.com/item/1005001683272407.html) This is still much in the works, no UI yet... 
The code uploaded runs by default as a 512KB REU.

###Pinout
####Expansion port:
Stm32  | Expansion port name | Expansion port pin
------------- | -------------|-------------
PE0-PE15 | Address bus A0-A15| Y - F
PA0-PA7  |  Data bus D0-D7 | 21 - 14
PA8 | Phi2 | E
PD0	| IRQ | 4
PD1	| R/W | 5
PD3	| IO1 | 7
PD4	| GAME | 8
PD5	| EXROM | 9
PD6	| IO/2 | 10
PD7	| ROML | 11
PD8	| BA | 12
PD9	| DMA | 13
PD10|ROMH | B
PD13 | RESET | C
PD14 | NMI | D
PB6 | 5V | 2
Ground| Ground|1

####Control pins
| Pin  | Description  |
| ------------- | ------------- |
|PB9	| debug	line (to pin header)|
|PC0	| button1 (planned)|
|PC1	| button2 (planned)|
|PB3 |SCK SPI 1
|PB4 |MISO SPI 1
|PB5| MOSI SPI 1
|PC4 |CS1 SPI 1
|PB13| SCK SPI 2|
|PB14| MISO SPI 2|
|PB15| MOSI SPI 2|
|PC5| CS2 SPI 2|
