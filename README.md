# ArduinoLibrary

This .ino file shows the basic operation of how to use the ads7138 when using an arduino.
For this project i used the Arduino Mega and Adafruit_I2CDevice library (can be installed directly from arduino)

There are 2 functions:
1.
void I2C_SendData(uint8_t device_address, uint8_t byte1, uint8_t byte2, uint8_t byte3) //Send one byte at a time
device_address -> the device address 
byte1 -> opcode (write single byte, write multiple bytes .. etc) in this function should be single wrtie i.e 0x08;
byte2 -> Register adress
byte3 -> register data 

2.
uint8_t I2C_WriteThenRead(uint8_t device_address, uint8_t registeraddress)  //read one register at a time
the way to read is to first write the opcode and the register adress and then we perfrom the read hence
why we call it a write read.
device_address -> the device address
registeraddress -> the register to read
