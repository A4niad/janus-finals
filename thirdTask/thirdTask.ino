#include <Wire.h>
#include <math.h> // Literally just for one square root

#define MS4525DO_ADDRESS 0x28  // I2C address for the sensor

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize I2C communication
}

float toPa(data){
  return 6894 * (6553.2*(data/pressureRange) - 4914.9)
}

void loop() {
  // Request 4 bytes of data (2 bytes for static pressure and 2 bytes for dynamic pressure)
  Wire.beginTransmission(MS4525DO_ADDRESS);
  Wire.requestFrom(MS4525DO_ADDRESS, 4);

  if (Wire.available() == 4) {
    // Read 4 bytes of data
    byte msb1 = Wire.read();
    byte lsb1 = Wire.read();
    byte msb2 = Wire.read();
    byte lsb2 = Wire.read();

    // Combine bytes to form pressure values
    int staticPressureRaw = (msb1 << 8) | lsb1;
    int dynamicPressureRaw = (msb2 << 8) | lsb2;

    // Convert data to Pascal
    float staticPressurePa = toPa(staticPressurePa);
    float dynamicPressurePa = toPa(dynamicPressurePa);

    float pressureDiff = dynamicPressurePa - staticPressurePa;

    // Calculate velocity from formula
    float velocity = 1.2437 * sqrt(pressureDiff)

    Serial.println("Pressure Difference: ");
    Serial.println(pressureDiff);
    Serial.println("Pa, Velocity: ");
    Serial.println(velocity);
    Serial.println("m/s");

  } else {
    Serial.println("Error: Insufficient data available");
  }

  delay(1000); 
}