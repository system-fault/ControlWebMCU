/**
 * @headerfile sensor_bmp280.h
 * 
 * @brief Cabecera para el sensor BMP280, que implementa la función init_led para inicializar el LED RGB en un dispositivo ESP32.
 *        
 * Descripción:
 * Este archivo implementa la función init_led, que se encarga de inicializar el LED RGB en un dispositivo ESP32.
 * La función configura los pines correspondientes como salidas GPIO y realiza un parpadeo del LED en verde tres veces como indicador visual
 * de la inicialización.
 * 
 * @authors David Martinez Henares
 * @email: thpuppetmaster@gmail.com
 * @universidad: UPV-EHU
 *
 * @defgroup driver/gpio
 * @{
 *
 * @tipo: ESP-IDF app
 */ 


#ifndef INIT_GPIO_H
#define INIT_GPIO_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


#ifndef LED_PIN_R
#define LED_PIN_R 0
#endif

#ifndef LED_PIN_G
#define LED_PIN_G 2
#endif

#ifndef LED_PIN_B
#define LED_PIN_B 4
#endif

#ifndef DELAY_INIT_GPIO
#define DELAY_INIT_GPIO 500
#endif



#endif /* INIT_GPIO_H */

/**
 * @brief Inicializa el LED RGB
 * 
 * ?@method: init_led();
 * 
 * Esta función inicializa el LED RGB configurando los pines correspondientes como salidas GPIO.
 * Luego realiza un parpadeo del LED en verde tres veces.
 * 
 * @return esp_err_t        
 */
esp_err_t init_led();
