This project is based in the devebox stm32h743vti board (https://www.aliexpress.com/item/1005001683272407.html)
This is still much in the works, no UI yet...
The code uploaded runs by default as a 512KB REU.

Current Pinout:
E0-E15 : Address bus A0-A15
A0-A7  :  Data bus D0-D7 

Expansion port Control pins:
PD0	: IRQ	
PD1	: R/W	
PD3	: IO1
PD4	: GAME
PD5	: EXROM
PD6	: IO/2
PD7	: ROML	
PD8	: BA
PD9	: DMA
PD10 :ROMH
PD13 : RESET	
PD14 : NMI	

Extra pins:
PB6	: power (5V)
PB9	: debug	line (to pin header)
PC0	: button1 (planned)
PC1	: button2 (planned)

SPI interfaces:
PB3 SCK
PB4 MISO
PB5 MOSI
PC4 CS1

PB13: SCK
PB14: MISO
PB15: MOSI
PC5 CS2
