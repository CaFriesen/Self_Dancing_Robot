#include <Encoder.h>

Encoder myEnc(18, 52); //encoderpins for left encoder wheel

#define motorSpeed 5
#define motorDir 48

#define sampleAmount 5
#define testTime 5000.0



void setup() {

  Serial.begin(115200);
  pinMode(motorDir, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  Serial.println();
  Serial.println("P = power, v = velocity");
}

void loop() {
  float averageSpeed[sampleAmount];
  float motorPosition = 0;
  digitalWrite(motorDir, HIGH);

  for(int i = 0; i < sampleAmount; i++) 	                    // Test loop for different speeds
  {
    analogWrite(motorSpeed, -1*map(i,sampleAmount,0,255,0));  //speed wheel up
    delay(500);
    long long startTime = millis();
    myEnc.write(0);                                           //start logging

    while(startTime + testTime > millis());                   // Wait for a set testTime amount of milliseconds

    averageSpeed[i] = myEnc.read()*1000/(testTime*632);       //Calculate average speed

    analogWrite(motorSpeed, 0);                               // Slow down
    delay(500);
    myEnc.write(0);

    Serial.print("P = ");                                     // Print the logged data to the Serial monitor
    Serial.print(-1*map(i,sampleAmount,0,255,0));
    Serial.print(" v = ");
    Serial.print(averageSpeed[i]);
    Serial.print("; ");
    
  }

  Serial.println();
  
}