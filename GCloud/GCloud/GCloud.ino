#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

const char* ssid = "Sudarshan 1 ";
const char* password = "16867986";


// Replace with your Firebase project details
const char* firebaseHost = "test-esp2fire.firebaseapp.com";
const char* firebaseAuth = "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDxWHMpfChWxG8N\n3EfpumwiYC6KGSVDbjnOj9YYk4UGyZFmjEhPhjanN6kKVTgLE7Eva7qd8xpuosv8\n8VHm4CNOP9kgfy8s04AfoDtCcHSGDV6wXwfZOMIQSIK5fLo+F7xcB/1m3n7hzwTH\ntOIKo5ks3MnlFbeCq0Hm0Ou4zN32uLtFlc9PDy4Lq+L28Vkvw7tBszcy6lGE7Fxs\nSRtR9hkDikI89CBsJeLcqZ4211qrCTkZx1eqFwTlr4ksC0Yz9ZoJltl456FiLqx4\ntqeVuZwJjG4phF5L9rDINn1wPfx5tDaz1CGPuIk7+0lK199ZG0uJ7d/kUDTypf2B\n0ESapaTBAgMBAAECggEAHqHhhWTxq8hP6NGfkQjChn8bDm0ln9A4PGxg5LVTSkAV\nmTn58u9aitEo6UZVZYEw2TonsWTfOHv86dRpVvqg5eLQY2xb0lPf7GOxJybQgLPm\nuPppgRvP9IgiNiUgxcEhJ7SIkwtveFKxzR/mHCqVRllEXjQU8DFeHSFBogQ4B1iT\nqlXmngAjnKKy85lLYHpcVP9eTJtQo+I4OqnAA7tnTBMqumSQkv1IPJXK0QANQO1i\nl/Rvo0svW4KQBYHmqNHbD93dd9sErpRlOJqZWF6sMSbLKaSe/FyTsgSwWjVv6AsF\nrWQ8EF+dMhOpxzMbfcRYvnPNx33LGLzxmpBSqArk5wKBgQD8wsPN7qmT0h565PDR\ns+FMGkYPbv65zQrxMQRH5RfUfAdGG2aJZQDtVACPSZAlPC2noSgURnetHUM5pC5g\nfxdLK6cz6yZ2Y7tOauIZi1CVVI9xu6bJGv9dLNWTZRyqdhd+MUv2jnnJqxzfbn22\nxn9SNTXLe6NvQKoAM4TuTmWNOwKBgQD0cDwWLIVqj0jmzUl8CYDWy+2i1D+iZDXD\nHwRhbSSCBo5feWTqU58+6w43is3Z4VMl1kXKFWPftZx0IanLMPox3SyRWP1QOYsY\nwbi8IkLYvkh0XX/XF/ArXpgpQWO94SfPr9ePq3zGdX91Zp3v0Lmyt2fv3mFx+8iy\nI+xQhB9mMwKBgBd73QdgGj9SsWRHqxxAszkH4+SBMod+xnp8TGKFpX4ne+GGoDM5\nwClMubSWaB8dhTxi279ugKYD5wAPAgQTKs3gI2vOeEddosR5Z8Jp0DXfomg1wBxF\nNt6oULueFFi+Ghaua9lfiW80R712nZWCwceYjAP428l1X5YfM0WU4RiLAoGBAJZ9\nMsEED++W328ZHBC9WRDk5BzHR5YW0/KY+f1xUHSszKKC/lo1uWjnFg2j6zAkxSga\nT0Um/iIQkY3926c5NA/W90VU4D+v7a8ENVO+VCFUpQ7fMYGfP0G0L0HW/C0+nWAE\nBlZxYZRdamdBEiM/AdTBjb/jzWJ7fQgPjcHUVfB5AoGBAMrTSJ1DUf8Hsmt9At3/\nOWSkG6csJSgp/lHY7HZWX9Gtq8AvVFYRCshV/e42Ym/Ee3SoNZA698umxQMvW0kT\nSwWdiW4Pq0P5x0tF6aX1p0mkhSK4Avs+P2z6i71xxBLCthWWBLMvoxV/T6/01hWu\n+UGm8A3ajsf3ij23Ad4CC0Sp\n-----END PRIVATE KEY-----\n";

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  Firebase.begin(firebaseHost, firebaseAuth);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Set the value to be sent to the Firebase database
    String value = "Hello, Firebase!";

    // Set the database path where the value will be stored
    String path = "/test";

    // Send the value to the Firebase database
    if (Firebase.setString(path, value)) {
      Serial.println("Data sent to Firebase successfully");
    } else {
      Serial.println("Failed to send data to Firebase");
    }

    // Wait for 5 seconds before sending the next data
    delay(5000);
  }
}

