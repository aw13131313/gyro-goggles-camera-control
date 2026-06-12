#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h> 

Adafruit_MPU6050 mpu;

float angleY = 90;
float angleZ = 90;

float alpha = 0.96; // untuk complementary filter
float gz_offset = 0;
float gy_offset = 0;

unsigned long lastTime = 0;

// Pin kalibrasi
#define PIN_KALIBRASI A1

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  pinMode(PIN_KALIBRASI, INPUT_PULLUP); // tombol dengan active LOW

  Serial.println("Inisialisasi MPU6050...");
  if (!mpu.begin()) {
    Serial.println("MPU6050 tidak ditemukan!");
    while (1) delay(10);
  }
  Serial.println("MPU6050 ditemukan.");

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ); // lebih smooth

  Serial.println("Inisialisasi LoRa...");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Konfigurasi LoRa:
  LoRa.setTxPower(20);                // Daya pancar maksimum (2 - 20)
  LoRa.setSpreadingFactor(7);        // Jangkauan maksimum, kecepatan rendah (6 - 12)
  LoRa.setSignalBandwidth(125E3);    // Lebar pita sinyal (default 125E3)
  LoRa.setCodingRate4(5);             // Rasio coding 4/8 (range: 5 - 8)
  LoRa.setGain(6);                    // Gain maksimum (0 - 6)

  Serial.println("Kalibrasi dalam 3 detik...");
  delay(3000);
  calibrateGyro();

  lastTime = millis();
}

void loop() {
  // Cek tombol kalibrasi
  if (digitalRead(PIN_KALIBRASI) == HIGH) {
    Serial.println("\nTombol ditekan, kalibrasi ulang...");
    delay(1000); // debounce delay
    calibrateGyro();
  }

  sensors_event_t acc, gyro, temp;
  mpu.getEvent(&acc, &gyro, &temp);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  if (dt <= 0 || dt > 1) return;

  // Ambil data accelerometer dan gyroscope
  float ax = acc.acceleration.x;
  float az = acc.acceleration.z;
  float gy_dps = (gyro.gyro.y - gy_offset) * 57.2958;
  float gz_dps = (gyro.gyro.z - gz_offset) * 57.2958;

  // Hitung sudut dari accelerometer (pitch)
  float accAngleY = atan2(az, ax) * 180.0 / PI;

  // Filter gabungan gyro + accel
  angleY = alpha * (angleY + gy_dps * dt) + (1 - alpha) * accAngleY;
  angleZ += gz_dps * dt;

  angleY = constrain(angleY, 0, 180);
  angleZ = constrain(angleZ, 0, 180);

  // Kirim ke receiver
  String val = String(int(angleY)) + "&" + String(int(angleZ));
  Serial.println(val);

  LoRa.beginPacket();
  LoRa.print(val);
  LoRa.endPacket();

  delay(20);
}

void calibrateGyro() {
  Serial.println("Kalibrasi... jangan gerakkan sensor!");
  float sum_gz = 0;
  float sum_gy = 0;
  const int samples = 500;

  for (int i = 0; i < samples; i++) {
    sensors_event_t acc, gyro, temp;
    mpu.getEvent(&acc, &gyro, &temp);
    sum_gz += gyro.gyro.z;
    sum_gy += gyro.gyro.y;
    delay(5);
  }

  gz_offset = sum_gz / samples;
  gy_offset = sum_gy / samples;

  Serial.print("Offset Z: "); Serial.println(gz_offset, 6);
  Serial.print("Offset Y: "); Serial.println(gy_offset, 6);
  Serial.println("Kalibrasi selesai.\n");
}
