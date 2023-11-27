#include <SoftwareSerial.h>
#include <TinyGPS++.h>
// Define the pin connections for GPS module
#define GPS_TX_PIN 2 // Connect GPS RX to this pin
#define GPS_RX_PIN 3 // Connect GPS TX to this pin

TinyGPSPlus gps; 
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN); // Create a SoftwareSerial object


void setup() {
  Serial.begin(9600); // Start the hardware serial communication for debugging
  gpsSerial.begin(9600); // Start the software serial communication with the GPS module
}

void loop() {
  if (gpsSerial.available()) {
    char c = gpsSerial.read();
    // Process the received character from the GPS module
    // You can parse the GPS data or perform any other required operations
    Serial.print(c); // Print the received character for debugging
    gps.encode(c); 

    Serial.print("Latitude: "); 
    Serial.println(gps.location.lat(),6); 
    Serial.print("Longitude: "); 
    Serial.println(gps.location.lng(),6); 
    Serial.print("Time: "); 
    Serial.println(GMTtoIST(gps.time.hour(),gps.time.minute(),gps.time.second()));
  }

  delay(2000); 
}


String GMTtoIST(int hr, int min, int sec)
{
   min=min+30;
   if(min>60)
   {
     min-=60; 
     hr+=1; 
   } 
   hr+=5; 

  String time = (" "+String(hr)+":"+String(min)+":"+String(sec)); 
  return time; 

}
