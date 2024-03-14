
#include "custom_HTTP_client.h"

static const char* TAG_http_client = "HTTP-CLIENT";


int level;

esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("%s\n", (char *)evt->data);
        sscanf((char *)evt->data, "%d", &level);
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

esp_err_t actualizar_led(int *estado){

    *estado = level;

    return ESP_OK;
}
