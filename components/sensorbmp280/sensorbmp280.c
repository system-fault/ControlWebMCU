/*
* Nombre: David Martinez Henares
* Email: thpuppetmaster@gmail.com
* Universidad: UPV-EHU
* 
* Archivo: sensor_bmp280.c
* 
* Descripción:
* Este archivo de implementación define las funciones necesarias para interactuar con un sensor BMP280 en el framework ESP-IDF. 
* Incluye funciones para inicializar el sensor, 
* leer datos de presión y temperatura, y actualizar una estructura de datos con los valores obtenidos del sensor.

*/

#include "sensorbmp280.h"

static const char* TAG_bmp280 = "SENSOR-BMP280";

bmp280_params_t params;
bmp280_t dev;

float pressure, temperature;


/**
 * @brief Task de lectura bmp280
 */
void bmp280_Task(void *pvParameters)
{
    while (1)
    {
        if (bmp280_read_float(&dev, &temperature, &pressure, NULL) != ESP_OK)
        {
            ESP_LOGE(TAG_bmp280,"Temperature/pressure reading failed");
            continue;
        }
        
        ESP_LOGI(TAG_bmp280,"Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);

        vTaskDelay(pdMS_TO_TICKS(60000));
    }
}


/**
 * @brief Inicializa el sensor bmp280 y la cominicacion I2C
 */
esp_err_t init_bmp280(){
    
    ESP_ERROR_CHECK(i2cdev_init());

    bmp280_init_default_params(&params);
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS, 0, SDA_PIN, SLC_PIN));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bool bme280p = dev.id == BME280_CHIP_ID;
    printf("BMP280: found %s\n", bme280p ? "BME280" : "BMP280");

    return ESP_OK;
}

/**
 * @brief Actualiza los datos del sensor y los devuelve en una estructura datosSensor
 */
esp_err_t actualizarDatos(datosSensor *datos){

    bmp280_read_float(&dev, &temperature, &pressure, NULL);

    datos->presionMain = pressure * pow(10,-5);
    datos->temperaturaMain = temperature;

    return ESP_OK;
}
