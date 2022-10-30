#include <Arduino_BHY2.h>

struct Data
{
  double gx, gy, gz;
  double ax, ay, az;
  double mx, my, mz;
  double pressure;
  double temperature;
  double humidity;
};

SensorXYZ gyro{SENSOR_ID_GYRO};
SensorXYZ accelerometer{SENSOR_ID_ACC};
SensorXYZ magnetometer{SENSOR_ID_MAG};
Sensor barometer{SENSOR_ID_BARO};
Sensor temperature{SENSOR_ID_TEMP};
Sensor humidity{SENSOR_ID_HUM};

struct Data lastData;

void setup()
{
  Serial.begin(115200);
  BHY2.begin();

  gyro.begin();
  accelerometer.begin();
  magnetometer.begin();
  barometer.begin();
  temperature.begin();
  humidity.begin();

  lastData = {0};
}

void loop()
{
  BHY2.update();

  struct Data data;

  data.gx = gyro.x();
  data.gy = gyro.y();
  data.gz = gyro.z();

  data.ax = accelerometer.x();
  data.ay = accelerometer.y();
  data.az = accelerometer.z();

  data.mx = magnetometer.x();
  data.my = magnetometer.y();
  data.mz = magnetometer.z();

  data.pressure = barometer.value();
  data.temperature = temperature.value();
  data.humidity = humidity.value();

  if (data.gx == lastData.gx && data.gy == lastData.gz && data.gz == lastData.gz && data.ax == lastData.ax && data.ay == lastData.ay && data.az == lastData.az && data.mx == lastData.mx && data.my == lastData.my && data.mz == lastData.mz && data.pressure == lastData.pressure && data.temperature == lastData.temperature && data.humidity == lastData.humidity)
    return;

  lastData = data;

  Serial.print("imu:");

  Serial.print(data.gx);
  Serial.print(":");
  Serial.print(data.gy);
  Serial.print(":");
  Serial.print(data.gy);
  Serial.print(":");

  Serial.print(data.ax);
  Serial.print(":");
  Serial.print(data.ay);
  Serial.print(":");
  Serial.print(data.az);
  Serial.print(":");

  Serial.print(data.mx);
  Serial.print(":");
  Serial.print(data.my);
  Serial.print(":");
  Serial.print(data.mz);
  Serial.print(":");

  Serial.print(data.pressure);
  Serial.print(":");

  Serial.print(data.temperature);
  Serial.print(":");

  Serial.print(data.humidity);

  Serial.println("");
  Serial.flush();
}
