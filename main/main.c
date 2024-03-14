#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sensorbmp280.h"
#include "init_custom_wifi.h"


#define DELAY 5000

static const char *TAG_MAIN = "MAIN";

float temperatura, presionBar;

datosSensor datos;

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_launch());
    ESP_ERROR_CHECK(init_bmp280());
    xTaskCreatePinnedToCore(bmp280_Task, "bmp280_Task", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);

    while (1)
    {
        ESP_ERROR_CHECK(actualizarDatos(&datos));
        temperatura = datos.temperaturaMain;
        presionBar = datos.presionMain;
        ESP_LOGI(TAG_MAIN,"Presion: %.2f Bar, Temperatura: %.2f ºC",presionBar,temperatura);
        vTaskDelay(pdMS_TO_TICKS(DELAY));
    }
}
