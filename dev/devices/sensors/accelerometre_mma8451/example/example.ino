#include <Wire.h>
#include <Adafruit_MMA8451.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(115200);
  Serial.println("Adafruit MMA8451 test");

  mma.init();
}

void loop() {
  Serial.print("Accelerations: \t"); Serial.print(mma.computeAcceleration()); Serial.println(" \tm/s^2");
  Serial.println();
  delay(100);
}
