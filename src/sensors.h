#pragma once

#include "cactus_io_BME280_I2C.h"

class sensorBME280 : private BME280_I2C
{
private:
    uint8_t payload[32]; // used to sprintf for Serial output
    // uint8_t payloadSize; // size of payload
    BME280_I2C bme280_; // Creating an instance of the cactus.io .h file :)
public:
    sensorBME280();
    sensorBME280(uint8_t Address);
    bool init();
    //void init(BME280_I2C &obj);
    void printBMETable();                                       /// Prints the table with the sensor data in Serial Monitor
    void printPacket();                                         // Prints the temperature
    void buildPacket(uint8_t txBuffer[], uint8_t &payloadSize); // prepares uplink packet
    

    float getPressure()
    {
        bme280_.readSensor();
        return bme280_.getPressure_MB();
    };
    float getHumidity()
    {
        bme280_.readSensor();
        return bme280_.getHumidity();
    };
    float getTemperature()
    {
        bme280_.readSensor();
        return bme280_.getTemperature_C();
    };
    uint8_t *getPayload()
    {
        return this->payload;
    }
};