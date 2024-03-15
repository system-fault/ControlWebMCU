/**
 * @headerfile init_custom_wifi.h
 * 
 * @brief Cabecera para la biblioteca init_custom_wifi, que proporciona funciones para manejar la conexión WiFi en dispositivos ESP32.
 *        
 * Descripción:
 * Esta biblioteca proporciona funciones para manejar la conexión WiFi en dispositivos ESP32.
 * Incluye funciones para configurar y establecer una conexión WiFi, así como para manejar los eventos
 * relacionados con la conexión WiFi.
 * 
 * @authors David Martinez Henares
 * @email: thpuppetmaster@gmail.com
 * @universidad: UPV-EHU
 *
 * @defgroup wifi
 * @{
 *
 * @tipo: ESP-IDF app
 */ 


#ifndef INIT_CUSTOM_WIFI_H
#define INIT_CUSTOM_WIFI_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "mydata_init_custom_wifi.h"



#endif // INIT_CUSTOM_WIFI_H



/**
 * !SOLO HACE FALTA ESTA FUNCION PARA HACER LA CONEXION WIFI
 */

/**
 * 
 * @brief Lanza la conexion wifi
 * 
 * ?@method: wifi_launch();
 * 
 * Esta función se encarga de iniciar la conexión WiFi en un dispositivo ESP32.
 * Primero inicializa la memoria flash no volátil (NVS) necesaria para el almacenamiento de la configuración.
 * Luego llama a la función wifi_connection para establecer la conexión WiFi.
 * 
 * @return esp_err_t
 */

esp_err_t wifi_launch();


/**
 * @brief Realiza la conexión WiFi
 * 
 * ?@method: wifi_connection();
 * 
 * Esta función se encarga de realizar la conexión WiFi en un dispositivo ESP32.
 * Si la funcion se llama hay que llamar antes: nvs_flash_init();
 * 
 * @return esp_err_t
 */
esp_err_t wifi_connection();
