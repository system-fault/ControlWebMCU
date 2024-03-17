/**
 * @file custom_HTTP_client.c
 *
 * @brief Este archivo contiene las funciones para el manejo de solicitudes GET y POST
 *        a un servidor web utilizando la librería custom_HTTP_client.
 *        
 * Descripción:
 * Este código proporciona funciones para manejar solicitudes GET y POST a un servidor web.
 * Incluye funciones para manejar eventos relacionados con la recepción y envío de datos,
 * así como tareas para consultar periódicamente el estado del LED y enviar datos de temperatura
 * y presión al servidor mediante solicitudes HTTP.
 * Además, define constantes y variables globales necesarias para el funcionamiento del programa.
 * 
** Nombre: David Martinez Henares
** Email: thpuppetmaster@gmail.com
** Universidad: UPV-EHU
 */


#include "custom_HTTP_client.h"

#define IP_SERVER IP_TACHIKOMA2 //& Introduce la ip de tu servidor

static const char *TAG_http_client = "HTTP-CLIENT";


static int level;
datosSensor http_medidas_var;

//$ FUNCIONES PARA MANEJAR LAS PETICIONES GET AL SERVIDOR WEB //

/**
 * @brief Maneja los eventos relacionados con la recepción de datos en una solicitud GET al 
 *        servidor web.
*/
esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("%s\n", (char *)evt->data);
        sscanf((char *)evt->data, "%d", &level);
        ESP_LOGI(TAG_http_client, "Datos led actualizados.");
        gpio_set_level(LED_PIN_R,true);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(LED_PIN_R,false);
        break;

    default:
        // ESP_LOGE(TAG_http_client,"ERROR AL RECIVIR RESPUESTA DEL SERVER!!!");
        break;
    }
    return ESP_OK;
}

/**
 * @brief Tarea que consulta el estado del LED mediante una solicitud GET al servidor web.
 */
void lectura_estado_led_Task(void *pvParameters)
{
    while (1)
    {
            char url[200]; // Asegúrate de que el tamaño del buffer sea suficiente
            snprintf(url, sizeof(url),"http://%s/control/php/variable.php", IP_SERVER);
        // Get estado led
        esp_http_client_config_t config_get = {
            .url = url,
            .method = HTTP_METHOD_GET,
            .cert_pem = NULL,
            .event_handler = client_event_get_handler};

        esp_http_client_handle_t client = esp_http_client_init(&config_get);
        esp_http_client_perform(client);
        esp_http_client_cleanup(client);

        vTaskDelay(pdMS_TO_TICKS(DELAY_LED_REQUEST));
    }
}

/**
 * @brief Actualiza el estado del LED.
 */
esp_err_t actualizar_led(int *estado)
{

    *estado = level;

    return ESP_OK;
}

//& FUNCIONES PARA MANEJAR LOS ENVIOS POST AL SERVIDOR WEB //



/**
 * @brief Adquiere las medidas de temperatura y presión para su posterior envío al servidor.
 */
esp_err_t adq_medidas(datosSensor datos)
{

    float temp = datos.temperaturaMain;
    float pres = datos.presionMain;

    http_medidas_var.temperaturaMain = temp;
    http_medidas_var.presionMain = pres;

    return ESP_OK;
}

/**
 * @brief Maneja los eventos relacionados con el envío de datos de temperatura mediante una solicitud POST al servidor web.
 */
esp_err_t client_event_post_handler_temp(esp_http_client_event_handle_t evt)
{

    switch (evt->event_id)
    {
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGI(TAG_http_client, "Datos de temperatura enviados al servidor.");
        break;

    default:
        break;
    }
    return ESP_OK;
}

/**
 * @brief Maneja los eventos relacionados con el envío de datos de presión mediante una solicitud POST al servidor web.
 */
esp_err_t client_event_post_handler_pres(esp_http_client_event_handle_t evt)
{

    switch (evt->event_id)
    {
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGI(TAG_http_client, "Datos de presion enviados al servidor.");
        

        break;

    default:
        break;
    }
    return ESP_OK;
}

/**
 * @brief Tarea que envía periódicamente datos de temperatura y presión al servidor mediante solicitudes POST.
 */
void envio_datos_post_Task(void *pvParameters)
{

    while (1)
    {
        float temp_debug = http_medidas_var.temperaturaMain;
        float pres_debug = http_medidas_var.presionMain;

        // Direcciones para hacer POST

        //! Temperatura
        char url_temp[200]; // Asegúrate de que el tamaño del buffer sea suficiente
        snprintf(url_temp, sizeof(url_temp), "http://%s/control/php/temperatura.php?temperatura=%.2f", IP_SERVER, temp_debug);
        
        //$ Presion
        char url_pres[200]; // Asegúrate de que el tamaño del buffer sea suficiente
        snprintf(url_pres, sizeof(url_pres), "http://%s/control/php/presion.php?presion=%.2f",IP_SERVER, pres_debug);

        //! POST temperatura
        esp_http_client_config_t config_post_temp = {
            .url = url_temp,
            .method = HTTP_METHOD_POST,
            .cert_pem = NULL,
            .event_handler = client_event_post_handler_temp};

        esp_http_client_handle_t client_temp = esp_http_client_init(&config_post_temp);

        esp_http_client_perform(client_temp);
        esp_http_client_cleanup(client_temp);
        
        //$ POST presion
        esp_http_client_config_t config_post_pres = {
            .url = url_pres,
            .method = HTTP_METHOD_POST,
            .cert_pem = NULL,
            .event_handler = client_event_post_handler_pres};

        esp_http_client_handle_t client_pres = esp_http_client_init(&config_post_pres);

        esp_http_client_perform(client_pres);
        esp_http_client_cleanup(client_pres);

        gpio_set_level(LED_PIN_B,true);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(LED_PIN_B,false);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}