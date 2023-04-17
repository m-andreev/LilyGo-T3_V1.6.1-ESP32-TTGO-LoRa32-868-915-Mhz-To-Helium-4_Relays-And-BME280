#include "sensors.h"
// #include "LMIC-Node.h"

/// Constructors for initialization of the sensor from cactus.io files
sensorBME280::sensorBME280() : bme280_()
{
    // Initializiation is automatically done to address 0x77 (default address) -> check cactus.io file
}
sensorBME280::sensorBME280(uint8_t Address) : bme280_(0x76) {}

bool sensorBME280::init()
{
    return bme280_.begin();
}

/*
void sensorBME280::init(BME280_I2C &obj)
{
    // Serial.begin(115200);
    if (!obj.begin())
    {
        Serial.println("Could not find a First BME280 sensor, check wiring!");
        while (1)
            ;
    }
}
*/

void sensorBME280::printBMETable()
{
    Serial.println("BME280 Sensors data:");
    Serial.println("Device\tPressure\tHumdity\t\tTemp");
    Serial.print("BME 1\t");
    bme280_.readSensor();
    Serial.print(this->getPressure());
    Serial.print(" mb\t"); // Pressure in millibars
    Serial.print(this->getHumidity());
    Serial.print(" %\t\t");
    Serial.print(this->getTemperature());
    Serial.print(" *C\t");
}

void sensorBME280::printPacket()
{
    char temp1[5];
    char fullbuffer1[32];
    fullbuffer1[0] = '\0'; // initialize fullbuffer1 with null characters
    
    // s1temp values
    // we need to convert from float to uint8_t/char the value
    float temperature1 = this->getTemperature();
    snprintf(temp1, sizeof(temp1), "%.2f", temperature1);
    // 5 is mininum width, 2 is precision; float value is copied onto buff temp1
    /// dtostrf(temperature1, 4, 2, temp1); ///double to string conversion function
    // sprintf(temp1, "%g", temperature1);

    strcat(fullbuffer1, "t1: ");
    strcat(fullbuffer1, temp1);
    strcat(fullbuffer1, " *C ");

    /// Printing the fullbuffer1 variable
    uint8_t Ccounter = 0;
    for (int i = 0; i < sizeof(fullbuffer1); i++)
    {
        char c = (char)fullbuffer1[i];

        if (Ccounter == 1)
        {
            fullbuffer1[i] = '\0';
            break;
        }

        if (c == 'C')
        {
            Ccounter++;
        }
        Serial.print((char)fullbuffer1[i]);
    }
    Serial.println();
}

void sensorBME280::buildPacket(uint8_t txBuffer[], uint8_t &payloadSize)
{
    /// Preparing the txBuffer
    float temperature1 = this->getTemperature();
    char tempBuff[6]; // here we store the value, which we will send with uplink
    snprintf(tempBuff, sizeof(tempBuff), "%.2f", temperature1);

    for (int i = 0; i < sizeof(tempBuff); i++)
    {
        if (!(tempBuff[i] >= '0' && tempBuff[i] <= '9') && tempBuff[i] != '.')
        {
            tempBuff[i] = '\0';
            txBuffer[i] = '\0';
            this->payload[i] = '\0';
            payloadSize = i;
            break;
        }
        txBuffer[i] = tempBuff[i];
        this->payload[i] = tempBuff[i]; /// assign the temperature to the payload variable of the object
        Serial.print(tempBuff[i]);      /// this is the char array of temp1
    }
    Serial.println();
}