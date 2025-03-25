#include <Adafruit_I2CDevice.h>
#include <Wire.h>

#define I2C_ADDRESS 0x17
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);

void I2C_SendData(uint8_t device_address, uint8_t registeraddess, uint8_t registerdata) //Send one byte at a time
{
    Wire.beginTransmission(device_address);  // Start communication with the device
    Wire.write(0x08);  // Send opcode (single write)
    Wire.write(registeraddess);  // Send second byte
    Wire.write(registerdata);  // Send third byte
    Wire.endTransmission();  // Stop communication
}

uint8_t I2C_WriteThenRead(uint8_t device_address, uint8_t registeraddress)
{
    uint8_t buffer[2] = {0x10, registeraddress}; // Prepare write buffer
    uint8_t readBuffer = 0; // Variable to store read byte

    // Begin transmission and send two bytes
    Wire.beginTransmission(device_address);
    Wire.write(buffer, 2);
    Wire.endTransmission(false); // Send STOP condition only if needed

    // Request 1 byte from the device
    Wire.requestFrom(device_address, (uint8_t)1);

    if (Wire.available()) 
    {
        readBuffer = Wire.read(); // Read and store the byte
    }

    return readBuffer; // Return the read byte
}




void setup() {
  while (!Serial) {
    delay(10);
  }

  Serial.begin(9600);
  Serial.println("I2C device read and write test");

  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1)
      ;
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);
  
 //UNCOMMENT TO SEND SINGLE DATA
  I2C_SendData(0x17, 0x30, 0xA0);
  I2C_SendData(0x17, 0x34, 0xA1);
  I2C_SendData(0x17, 0x38, 0xA2);
  I2C_SendData(0x17, 0x3C, 0xA3);


//READING SINGLE REGISTERS
  uint8_t receivedByte1 = I2C_WriteThenRead(0x17, 0x30); // Pass only buffer[1] (0x30)
  uint8_t receivedByte2 = I2C_WriteThenRead(0x17, 0x34); // Pass only buffer[1] (0x30)
  uint8_t receivedByte3 = I2C_WriteThenRead(0x17, 0x38); // Pass only buffer[1] (0x30)
  uint8_t receivedByte4 = I2C_WriteThenRead(0x17, 0x3C); // Pass only buffer[1] (0x30)

  Serial.print("Received Byte: 0x");
  Serial.println(receivedByte1, HEX);
  
  Serial.print("Received Byte: 0x");
  Serial.println(receivedByte2, HEX);
  
  Serial.print("Received Byte: 0x");
  Serial.println(receivedByte3, HEX);
  
  Serial.print("Received Byte: 0x");
  Serial.println(receivedByte4, HEX);

}

void loop() {

}
