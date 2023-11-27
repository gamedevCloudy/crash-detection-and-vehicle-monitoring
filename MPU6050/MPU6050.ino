
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  Wire.begin();
  mpu.begin();

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t gyro;
  mpu.getGyroSensor()->getEvent(&gyro);

  int orientation = getOrientation(gyro);

  switch (orientation) {
    case 0:
      Serial.println("No rotation");
      break;
    case 1:
      Serial.println("Rotating forward");
      break;
    case 2:
      Serial.println("Rotating backward");
      break;
    case 3:
      Serial.println("Rotating left");
      break;
    case 4:
      Serial.println("Rotating right");
      break;
    case 5:
      Serial.println("Upside down");
      break;
  }

  delay(1000); // Delay for 1 second
}

int getOrientation(sensors_event_t gyro) {
  // Adjust the threshold values based on your sensor and requirements
  const int rotationThreshold = 200;

  if (gyro.gyro.x > rotationThreshold) {
    return 1; // Rotating forward
  } else if (gyro.gyro.x < -rotationThreshold) {
    return 2; // Rotating backward
  } else if (gyro.gyro.y > rotationThreshold) {
    return 3; // Rotating left
  } else if (gyro.gyro.y < -rotationThreshold) {
    return 4; // Rotating right
  } else if (gyro.gyro.z < -rotationThreshold) {
    return 5; // Upside down
  } else {
    return 0; // No rotation
  }
}
