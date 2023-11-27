#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}


void loop() {

  if(IsRolled())
  {
    Serial.println("Status: Crashed"); 
  }
  else Serial.println("Status: Safe"); 
  delay(2000);
}

void SetupMPU()
{
  Serial.begin(9600);
  while (!Serial);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}
bool IsRolled()
{
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float pitch = atan2(-accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
  float roll = atan2(accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;

  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" Roll: ");
  Serial.println(roll);
  Serial.print(" Heat: ");
  Serial.println(temp.temperature);

  if ( pitch> 40 || pitch < -40)
    return true; 
  if ( roll> 40 || roll < -40)
    return true; 
  return false; 
}
