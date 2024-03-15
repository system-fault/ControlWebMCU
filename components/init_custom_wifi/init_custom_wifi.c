/**
 * @file init_custom_wifi.c
 * 
 * @brief Implementación de las funciones para manejar la conexión WiFi en dispositivos ESP32.
 *        
 * Descripción:
 * Este archivo contiene la implementación de las funciones para manejar la conexión WiFi en dispositivos ESP32.
 * Incluye funciones para realizar la conexión WiFi, manejar eventos relacionados con la conexión WiFi
 * y lanzar la conexión WiFi.
 * 
 * @authors David Martinez Henares
 * @email: thpuppetmaster@gmail.com
 * @universidad: UPV-EHU
 *
 * @ingroup wifi
 * @{
 *
 * @tipo: ESP-IDF app
 */ 


#include "init_custom_wifi.h"




const char *ssid = SSID; //& Sustituye por tu ssid
const char *pass = PASS; //& Sustituye por tu password

int retryNum = 0;

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *even_data);

/**
 * @brief Realiza la conexión WiFi
 */
esp_err_t wifi_connection()
{

    //? Second fase wifi configuration
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation);

    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);

    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = "ssid",
            .password = "pass",

        }

    };

    strcpy((char *)wifi_configuration.sta.ssid, ssid);
    stpcpy((char *)wifi_configuration.sta.password, pass);

    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    //? 3 wifi start fase
    esp_wifi_start();
    esp_wifi_set_mode(WIFI_MODE_STA);
    //? 4 connect fase
    esp_wifi_connect();
    printf("wifi_init_softap finished. SSID: %s  PASSWORD: %s", ssid, pass);

    return ESP_OK;
    
}


/**
 * @brief Inicia la conexión WiFi
 */
esp_err_t wifi_launch(){
    nvs_flash_init();
    wifi_connection();

    return ESP_OK;
}


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
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *even_data)
{
    if (event_id == WIFI_EVENT_STA_START)
    {
        printf("WIFI CONECTING...\n");
    }
    else if (event_id == WIFI_EVENT_STA_CONNECTED)

    {
        printf("WIFI CONECTED...\n");
    }
    else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        printf("Wifi lost connection\n");
        if (retryNum < 5)
        {
            esp_wifi_connect();
            retryNum++;
            printf("Retrying to Connect...\n");
        }
    }
    else if (event_id == IP_EVENT_STA_GOT_IP)
    {
        printf("Wifi got IP...\n\n");
    }
}