BOARD_TAG := uno
AVR_TOOLS_PATH := /usr/local/Cellar/avr-gcc49/4.9.3/bin
AVR_BINTOOLS_PATH := /usr/local/Cellar/avr-binutils/2.25/bin
ARDMK_DIR := /usr/local/Cellar/arduino-mk/1.5.1
ARDUINO_LIBS := SPI MD_MAX72XX MD_Parola
MONITOR_PORT := /dev/tty.wchusbserial1420
AVRDUDE := /usr/local/Cellar/avrdude/6.3/bin/avrdude
AVRDUDE_CONF := /usr/local/Cellar/avrdude/6.3/etc/avrdude.conf
include /usr/local/Cellar/arduino-mk/1.5.1/Arduino.mk
