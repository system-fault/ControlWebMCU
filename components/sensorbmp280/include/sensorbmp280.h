/*
* Nombre: David Martinez Henares
* Email: thpuppetmaster@gmail.com
* Universidad: UPV-EHU
*
* Archivo: sensor_bmp280.h
*
* Descripción:
* Este archivo de cabecera define las funciones y estructuras necesarias para la lectura de un sensor BMP280 en el framework ESP-IDF.
* La biblioteca proporciona funciones para inicializar el sensor, leer datos de presión y temperatura, y actualizar una estructura de datos con
* los valores obtenidos del sensor.

*/

/**
 * @file sensorbmp280.h
 * @defgroup bmp280 bmp280
 * @{
 *
 * ESP-IDF app
 */

#ifndef SENSOR_BMP280_H
#define SENSOR_BMP280_H

#include "bmp280.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

#ifndef SDA_PIN
#define SDA_PIN 18
#endif

#ifndef SLC_PIN
#define SLC_PIN 19
#endif
#ifndef BMP280_I2C_ADDRESS
#define BMP280_I2C_ADDRESS 0x76
#endif

extern bmp280_params_t params;
extern bmp280_t dev;
extern float pressure, temperature;

/**
 * Estrucutura para manejar los datos de presion y temperatura
 */
typedef struct
{
    float presionMain;
    float temperaturaMain;
} datosSensor;

#endif /* SENSOR_BMP280_H */

/**
 * @brief Inicializa el sensor bmp280 y la cominicacion I2C
 *
 * ?@method: esp_err_t init_bmp280();

 * Descripción:
 * La función init_bmp280 se encarga de inicializar el sensor BMP280.
 * Realiza las siguientes tareas:
 *   1. Inicializa el bus I2C necesario para la comunicación con el sensor.
 *   2. Inicializa los parámetros predeterminados para el sensor BMP280.
 *   3. Inicializa la estructura del dispositivo dev a cero para evitar datos residuales.
 *   4. Inicializa la descripción del dispositivo dev con la dirección I2C y los pines SDA y SLC especificados.
 *   5. Inicializa el sensor BMP280 con los parámetros y la descripción del dispositivo proporcionados.
 *   6. Verifica si se ha detectado un sensor BMP280 o BME280 y muestra un mensaje en consecuencia.
 *   7. Devuelve ESP_OK si la inicialización del sensor se ha completado con éxito.

 * @return esp_err_t
 */
esp_err_t init_bmp280();

/**
 * @brief Task de lectura bmp280
 *
 * ?@method: esta funcion es llamada desde xTaskCreatePinnedToCore();
 *
 * Descripción:
 * La función bmp280_Task es una tarea de FreeRTOS que se encarga de leer periódicamente los datos de presión y temperatura del sensor BMP280.
 * Realiza las siguientes tareas:
 *   1. Utiliza un bucle infinito para leer continuamente los datos del sensor.
 *   2. Utiliza la función bmp280_read_float para leer los datos de presión y temperatura del sensor.
 *   3. Verifica si la lectura de datos es exitosa. Si no lo es, registra un mensaje de error utilizando ESP_LOGE y continúa con la siguiente iteración del bucle.
 *   4. Si la lectura de datos es exitosa, registra un mensaje informativo utilizando ESP_LOGI que muestra la presión y la temperatura leídas del sensor.
 *   5. Espera un intervalo de tiempo de 60 segundos antes de realizar la siguiente lectura de datos.
 *
 *
 * @param pvParameters
 *
 */
void bmp280_Task(void *pvParameters);

/**
 * @brief Actualiza los datos del sensor y los devuelve en una estructura datosSensor
 *
 * ?@method: actualizarDatos(datosSensor *datos);
 *
 * Descripción:
 * La función actualizarDatos se encarga de actualizar la estructura datosSensor con los valores de presión y temperatura obtenidos del sensor BMP280.
 * Realiza las siguientes tareas:
 *   1. Utiliza la función bmp280_read_float para leer los datos de presión y temperatura del sensor.
 *   2. Calcula la presión en bares multiplicando la presión obtenida por 10 elevado a -5.
 *   3. Actualiza los miembros presionMain y temperaturaMain de la estructura datosSensor con los valores obtenidos del sensor.
 *
 * @param datos
 * 
 * @return esp_err_t
 *
 */
esp_err_t actualizarDatos(datosSensor *datos);