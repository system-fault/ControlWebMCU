#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sensorbmp280.h"
#include "init_gpio.h"
#include "init_custom_wifi.h"
#include "custom_HTTP_client.h"

#define DELAY 250

static const char *TAG_MAIN = "MAIN";

float temperatura, presionBar;
int nivel_led;

datosSensor datos;

void mainTask(void *pvParameters);

void app_main(void)
{
    ESP_ERROR_CHECK(wifi_launch());
    ESP_ERROR_CHECK(init_bmp280());
    ESP_ERROR_CHECK(init_led());
    xTaskCreatePinnedToCore(bmp280_Task, "bmp280_Task", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(lectura_estado_led_Task, "lectura_estado_led_Task", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(envio_datos_post_Task, "envio_datos_post_Task", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(mainTask, "mainTask", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, PRO_CPU_NUM);
    
}


//? TAREA PRINCIPAL(MAIN)
void mainTask(void *pvParameters)
{

    while (1)
    {
        ESP_ERROR_CHECK(actualizarDatos(&datos));
        temperatura = datos.temperaturaMain;
        presionBar = datos.presionMain;
        ESP_LOGI(TAG_MAIN, "Presion: %.2f Bar, Temperatura: %.2f ºC", presionBar, temperatura);
        ESP_ERROR_CHECK(actualizar_led(&nivel_led));
        ESP_ERROR_CHECK(adq_medidas(datos));
        gpio_set_level(LED_PIN_G, nivel_led);

        vTaskDelay(pdMS_TO_TICKS(DELAY));
    }
}