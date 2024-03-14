/*
* Nombre: David Martinez Henares
* Email: thpuppetmaster@gmail.com
* Universidad: UPV-EHU


* Descripción:
* Esta biblioteca proporciona funciones para manejar la conexión WiFi en dispositivos ESP32.
* Incluye funciones para configurar y establecer una conexión WiFi, así como para manejar los eventos
* relacionados con la conexión WiFi.
*/

/**
 * @file init_custom_wifi.h
 * @defgroup wifi
 * @{
 *
 * ESP-IDF app
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
 * @brief Maneja los eventos de la conexión WiFi
 * 
 * ?@method: static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *even_data);
 * 
 * Esta función se encarga de manejar los eventos relacionados con la conexión WiFi en un dispositivo ESP32.
 * 
 * @param event_handler_arg  Argumento del controlador de eventos
 * @param event_base         Base del evento
 * @param event_id           ID del evento
 * @param even_data          Datos del evento
 */
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *even_data);


/**
 * @brief Realiza la conexión WiFi
 * 
 * ?@method: wifi_connection();
 * 
 * Esta función se encarga de realizar la conexión WiFi en un dispositivo ESP32.
 * 
 * @return esp_err_t
 */
esp_err_t wifi_connection();


