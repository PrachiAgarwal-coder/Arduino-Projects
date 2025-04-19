// Basic OV7670 Test (No FIFO version)
// Just to check camera ID over SCCB (I2C-like protocol)

#include <Wire.h>

#define OV7670_SDA 21  // Adjust according to your wiring
#define OV7670_SCL 22

void writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(0x21); // OV7670 write address
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t readReg(uint8_t reg) {
  Wire.beginTransmission(0x21);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(0x21, 1);
  if (Wire.available()) {
    return Wire.read();
  }
  return 0xFF;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(OV7670_SDA, OV7670_SCL);
  delay(1000);

  Serial.println("Checking OV7670...");

  uint8_t pid = readReg(0x0A);  // PID = 0x76
  uint8_t ver = readReg(0x0B);  // VER = 0x73 or similar

  Serial.print("PID: 0x");
  Serial.println(pid, HEX);
  Serial.print("VER: 0x");
  Serial.println(ver, HEX);

  if (pid == 0x76) {
    Serial.println("OV7670 detected!");
  } else {
    Serial.println("Camera not detected. Check wiring and power.");
  }
}

void loop() {
  delay(2000);
}