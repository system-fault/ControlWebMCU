/*
* Nombre: David Martinez Henares
* Email: thpuppetmaster@gmail.com
* Universidad: UPV-EHU
*
* Archivo: custom_HTTP_client.h
*
* Descripción:


*/

/**
 * @file custom_HTTP_client.h
 * @defgroup wifi http
 * @{
 *
 * ESP-IDF app
 */

#ifndef CUSTOM_HTTTP_CLIENT_H
#define CUSTOM_HTTTP_CLIENT_H


#include <stdio.h>
#include <string.h>
#include "esp_http_client.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

#ifndef DELAY_LED_REQUEST
#define DELAY_LED_REQUEST 200
#endif



#endif /* CUSTOM_HTTTP_CLIENT_H */



esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt);

void lectura_estado_led_Task(void *pvParameters);

esp_err_t actualizar_led(int *estado);