/**
 * @headerfile custom_HTTP_client.h
 * 
 * @brief Cabecera para la librería custom_HTTP_client, que permite realizar conexiones HTTP GET y POST
 *        con un servidor web para intercambiar información de un LED y datos de temperatura y presión.
 *        
 * Descripción:
 * Este archivo contiene las funciones para el manejo de solicitudes GET y POST
 * a un servidor web utilizando la librería custom_HTTP_client.
 * Incluye funciones para manejar eventos relacionados con la recepción y envío de datos,
 * así como tareas para consultar periódicamente el estado del LED y enviar datos de temperatura
 * y presión al servidor mediante solicitudes HTTP.
 * Además, define constantes y variables globales necesarias para el funcionamiento del programa.
 * 
 * @authors: David Martinez Henares
 * @email: thpuppetmaster@gmail.com
 * @universidad: UPV-EHU
 *
 * @defgroup wifi http
 * @{
 *
 * @tipo:ESP-IDF app
 * 
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
#include "sensorbmp280.h"
#include "driver/gpio.h"
#include "init_gpio.h"
#include "mydata_custom_HTTP_client.h"

#ifndef DELAY_LED_REQUEST
#define DELAY_LED_REQUEST 200
#endif

#ifndef DELAY_POST_DATA
#define DELAY_POST_DATA 5000
#endif

extern datosSensor http_medidas_var;

#endif /* CUSTOM_HTTTP_CLIENT_H */

//$ FUNCIONES PARA MANEJAR LAS PETICIONES GET AL SERVIDOR WEB //


/**
 * @brief Maneja los eventos relacionados con la recepción de datos en una solicitud GET al 
 *        servidor web.
 *
 * ?@method: Se llama automaticamente desde
 * 
 * Descripción:
 * Esta función maneja los eventos recibidos durante una solicitud GET al servidor web.
 * Actualiza el estado del LED basado en los datos recibidos.
 *
 * @param evt Puntero al evento HTTP.
 * 
 * @return esp_err_t
 */
esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt);

/**
 * @brief Tarea que consulta el estado del LED mediante una solicitud GET al servidor web.
 *
 * ?@method: Se llama como tarea con xTaskCreatePinnedToCore()
 * 
 * Descripción:
 * Esta tarea realiza periódicamente una solicitud GET al servidor web para obtener el estado del LED.
 * Utiliza la función client_event_get_handler para manejar la respuesta del servidor.
 */
void lectura_estado_led_Task(void *pvParameters);

/**
 * @brief Actualiza el estado del LED.
 *
 * ?@method: actualizar_led(int *parametro)
 * 
 * Descripción:
 * Esta función actualiza el estado del LED basado en el valor recibido en la solicitud GET al servidor web.
 *
 * @param estado Puntero al estado del LED.
 * 
 * @return esp_err_t
 */
esp_err_t actualizar_led(int *estado);

//& FUNCIONES PARA MANEJAR LOS ENVIOS POST AL SERVIDOR WEB //


/**
 * @brief Adquiere las medidas de temperatura y presión para su posterior envío al servidor.
 *
 * ?@method: adq_medidas(datosSensor estrucutura) (pasamos una estrucutura de datos)
 * 
 * Descripción:
 * Esta función adquiere las medidas de temperatura y presión y las almacena en una estructura para su posterior envío al servidor.
 *
 * @param datos Estructura donde se almacenarán las medidas.
 * 
 * @return esp_err_t
 */
esp_err_t adq_medidas(datosSensor datos);


/**
 * @brief Maneja los eventos relacionados con el envío de datos de temperatura mediante una solicitud POST al servidor web.
 *
 * ?@method: manejador de eventos se lanza desde una peticion post
 * 
 * Descripción:
 * Esta función maneja los eventos recibidos durante una solicitud POST al servidor web para enviar datos de temperatura.
 * Realiza acciones basadas en los eventos, como indicar el éxito del envío mediante el LED.
 *
 * @param evt Puntero al evento HTTP.
 * 
 * @return esp_err_t
 */
esp_err_t client_event_post_handler_temp(esp_http_client_event_handle_t evt);

/**
 * @brief Maneja los eventos relacionados con el envío de datos de presión mediante una solicitud POST al servidor web.
 *
 * ?@method: manejador de eventos se lanza desde una peticion post
 * 
 * Descripción:
 * Esta función maneja los eventos recibidos durante una solicitud POST al servidor web para enviar datos de presión.
 * Realiza acciones basadas en los eventos, como indicar el éxito del envío mediante el LED.
 *
 * @param evt Puntero al evento HTTP.
 * 
 * @return esp_err_t
 */
esp_err_t client_event_post_handler_pres(esp_http_client_event_handle_t evt);


/**
 * @brief Tarea que envía periódicamente datos de temperatura y presión al servidor mediante solicitudes POST.
 *
 * ?@method: Se llama como tarea con xTaskCreatePinnedToCore()
 * 
 * Descripción:
 * Esta tarea se encarga de enviar periódicamente datos de temperatura y presión al servidor mediante solicitudes POST.
 * Utiliza las funciones client_event_post_handler_temp y client_event_post_handler_pres para manejar la respuesta del servidor.
 */
void envio_datos_post_Task(void *pvParameters);