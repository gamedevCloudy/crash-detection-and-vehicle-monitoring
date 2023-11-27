const int vibrationPin = A0;
const int threshold = 500;

void setup() {
  SetupVibrationSensor(); 
}


void SetupVibrationSensor()
{
  Serial.begin(9600);

  pinMode(vibrationPin, INPUT);

//   const int vibrationPin = A0;
// const int threshold = 500;
}
void loop() {
  int vibrationValue = analogRead(vibrationPin);

  if (IsSlammed()) {
    Serial.println("Status: Crashed");
  }
  else
  Serial.println("Status: Safe");

  delay(100); 
}

bool IsSlammed()
{
  int vibrationValue = analogRead(vibrationPin);

  if (vibrationValue > threshold) {
    return true; 
  }

  return false; 
}
