
#include "custom_HTTP_client.h"

static const char *TAG_http_client = "HTTP-CLIENT";

//$ FUNCIONES PARA MANEJAR LAS PETICIONES GET AL SERVIDOR WEB //

static int level;

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

void lectura_estado_led_Task(void *pvParameters)
{
    while (1)
    {
        // Get estado led
        esp_http_client_config_t config_get = {
            .url = "http://192.168.1.34/control/Proyecto_empotrados/php/variable.php",
            .method = HTTP_METHOD_GET,
            .cert_pem = NULL,
            .event_handler = client_event_get_handler};

        esp_http_client_handle_t client = esp_http_client_init(&config_get);
        esp_http_client_perform(client);
        esp_http_client_cleanup(client);

        vTaskDelay(pdMS_TO_TICKS(DELAY_LED_REQUEST));
    }
}

esp_err_t actualizar_led(int *estado)
{

    *estado = level;

    return ESP_OK;
}

//& FUNCIONES PARA MANEJAR LOS ENVIOS POST AL SERVIDOR WEB //

datosSensor http_medidas_var;

esp_err_t adq_medidas(datosSensor datos)
{

    float temp = datos.temperaturaMain;
    float pres = datos.presionMain;

    http_medidas_var.temperaturaMain = temp;
    http_medidas_var.presionMain = pres;

    return ESP_OK;
}

esp_err_t client_event_post_handler_temp(esp_http_client_event_handle_t evt)
{

    switch (evt->event_id)
    {
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGI(TAG_http_client, "Datos de temperatura enviados al servidor.");
        gpio_set_level(LED_PIN_B,true);
        vTaskDelay(pdMS_TO_TICKS(50));
        gpio_set_level(LED_PIN_B,false);
        break;

    default:
        break;
    }
    return ESP_OK;
}
esp_err_t client_event_post_handler_pres(esp_http_client_event_handle_t evt)
{

    switch (evt->event_id)
    {
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGI(TAG_http_client, "Datos de presion enviados al servidor.");
        gpio_set_level(LED_PIN_B,true);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_set_level(LED_PIN_B,false);

        break;

    default:
        break;
    }
    return ESP_OK;
}

void envio_datos_post_Task(void *pvParameters)
{

    while (1)
    {
        float temp_debug = http_medidas_var.temperaturaMain;
        float pres_debug = http_medidas_var.presionMain;

        // Direcciones para hacer POST

        // Temperatura
        char url_temp[200]; // Asegúrate de que el tamaño del buffer sea suficiente
        snprintf(url_temp, sizeof(url_temp), "http://192.168.1.34/control/Proyecto_empotrados/php/temperatura.php?temperatura=%.2f", temp_debug);
        
        // Presion
        char url_pres[200]; // Asegúrate de que el tamaño del buffer sea suficiente
        snprintf(url_pres, sizeof(url_pres), "http://192.168.1.34/control/Proyecto_empotrados/php/presion.php?presion=%.2f", pres_debug);

        //POST temperatura
        esp_http_client_config_t config_post_temp = {
            .url = url_temp,
            .method = HTTP_METHOD_POST,
            .cert_pem = NULL,
            .event_handler = client_event_post_handler_temp};

        esp_http_client_handle_t client_temp = esp_http_client_init(&config_post_temp);

        esp_http_client_perform(client_temp);
        esp_http_client_cleanup(client_temp);

        vTaskDelay(pdMS_TO_TICKS(500));
        
        //POST presion
        esp_http_client_config_t config_post_pres = {
            .url = url_pres,
            .method = HTTP_METHOD_POST,
            .cert_pem = NULL,
            .event_handler = client_event_post_handler_pres};

        esp_http_client_handle_t client_pres = esp_http_client_init(&config_post_pres);

        esp_http_client_perform(client_pres);
        esp_http_client_cleanup(client_pres);

        vTaskDelay(pdMS_TO_TICKS(DELAY_POST_DATA));
        
    }
}