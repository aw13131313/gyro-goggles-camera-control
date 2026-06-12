#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

int LED = 3;
String inString = "";    // string to hold input
String valRecv = "";
 
Servo servo1;
Servo servo2;
int valServoY = 0;
int valServoZ = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  
  servo1.attach(5);  // Hubungkan servo1 ke pin 5
  servo2.attach(6);  // Hubungkan servo2 ke pin 6

  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Tambahkan setting agar cocok dengan TX
  LoRa.setSpreadingFactor(7);        // Jangkauan maksimum, kecepatan rendah (6 - 12)
  LoRa.setSignalBandwidth(125E3);    // Lebar pita sinyal (default 125E3)
  LoRa.setCodingRate4(5);             // Rasio coding 4/8 (range: 5 - 8)
  LoRa.setGain(6);                    // Gain maksimum (0 - 6)
}
 
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    while (LoRa.available()) { 
      int inChar = LoRa.read();
      inString += (char)inChar;
      valRecv = inString;
    }   
    inString = "";     

    // Parsing valRecv, contoh format: "61&17"
    int separatorIndex = valRecv.indexOf('&');
    if (separatorIndex > 0) {
      String val1Str = valRecv.substring(0, separatorIndex);
      String val2Str = valRecv.substring(separatorIndex + 1);

      valServoY = val1Str.toInt();
      valServoZ = val2Str.toInt();

      // Kirim ke servo
      servo1.write(valServoY);
      servo2.write(valServoZ);

      Serial.print("Servo Y: ");
      Serial.print(valServoY);
      Serial.print("  Servo Z: ");
      Serial.println(valServoZ);
    }

    valRecv = "";
  }
}
