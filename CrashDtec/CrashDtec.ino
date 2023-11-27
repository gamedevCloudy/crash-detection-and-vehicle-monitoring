#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include<TinyGPS++.h>

#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;

#define SSID "galaxy F22"
#define PASS "jaimahakall"

#define RXPin 3
#define TXPin 2

SoftwareSerial gpsSerial(TXPin, RXPin); 
TinyGPSPlus gps; 

const int vibrationPin = A0;
const int threshold = 500;


float roll; 
float pitch; 

float temperature; 
bool isRolling; 

bool isSlamming; 

double lat; 
double lng;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWifi(); 

  initGPS(); 

  initMPU(); 

  initVibration(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Handle GYRO Data

  roll = getRoll(); 
  pitch= getPitch(); 
  temperature = getTemperature(); 
  isRolling = isRolled(); 
  isSlamming = isSlammed(); 
  
  getLatLng(); 
  display(); 
  delay(1000); 
}


void display()
{
  Serial.println("------------------------"); 
  Serial.println("Roll: "); 
  Serial.println(roll); 
  Serial.println("Pitch: "); 
  Serial.println(pitch); 
  if(isRolling)
  {
    Serial.println("Vechile FLIPPED"); 
  }

  Serial.println("Heat: "); 
  Serial.println(temperature); 
  

  if(isSlamming)
  {
    Serial.println("Vechile SLAMMED"); 
  }

  Serial.println("------------------------"); 

  
  Serial.println("Location Data: "); 

  Serial.println("Latitude: "); 
  Serial.println(lat, 6); 
  Serial.println("Longitude: "); 
  Serial.println(lng, 6); 
  Serial.println("------------------------"); 
  
}
void initWifi()
{
  
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  delay(1000); 
}

void initGPS()
{
  gpsSerial.begin(9600); 
}

void initMPU()
{
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

void initVibration()
{
  pinMode(vibrationPin, INPUT);
}


double defLat = 18.507600; 
double defLng = 73.789600; 


bool isRolled()
{
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float pitch = atan2(-accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;
  float roll = atan2(accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;

  // Serial.print("Pitch: ");
  // Serial.print(pitch);
  // Serial.print(" Roll: ");
  // Serial.println(roll);
  // Serial.print(" Heat: ");
  // Serial.println(temp.temperature);

  if ( pitch> 40 || pitch < -40)
    return true; 
  if ( roll> 40 || roll < -40)
    return true; 
  return false; 
}

float getPitch()
{
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
   float pitch = atan2(-accel.acceleration.x, sqrt(accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z)) * 180.0 / PI;

   return pitch; 
}

float getRoll()
{
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  float roll = atan2(accel.acceleration.y, accel.acceleration.z) * 180.0 / PI;

  return roll; 
}

float getTemperature()
{
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
 

  return temp.temperature; 
}

bool isSlammed()
{
  int vibrationValue = analogRead(vibrationPin);

  if (vibrationValue > threshold) {
    return true; 
  }

  return false; 
}


void getLatLng()
{
  if(gpsSerial.available())
  {
    char c = gpsSerial.read(); 

    gps.encode(c); 

    lat = (gps.location.lat(),6); 
    lng = (gps.location.lng(),6); 

    if(lat <1) lat = defLat; 
    if(lng <1) lat = defLng; 
  }

  lat = defLat; 
  lng = defLng; 
}