#ifndef _COMMITTER_TEMPERATURE_HPP
#define _COMMITTER_TEMPERATURE_HPP

#define N_SAMPLES 100

class TemperatureSensor {
private:
  uint8_t sensorInput;

public:
  TemperatureSensor(uint8_t sensorInput): sensorInput(sensorInput) {}

  float measureCelsiusTemperature()
  {
    float sum = 0.0;

    for (unsigned int i = 0; i < N_SAMPLES; i++) {
      int sensor_val = analogRead(this->sensorInput);

      float voltage = sensor_val / 1024.0 * 5.0;

      sum += (voltage - .5) * 100;
    }

    return sum / N_SAMPLES;
  }
};

#endif /* _COMMITTER_TEMPERATURE_HPP */
