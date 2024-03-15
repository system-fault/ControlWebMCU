/**
 * @file init_gpio.c
 * 
 * @brief Implementación de la función init_led para inicializar el LED RGB en un dispositivo ESP32.
 *        
 * Descripción:
 * Este archivo implementa la función init_led, que se encarga de inicializar el LED RGB en un dispositivo ESP32.
 * La función configura los pines correspondientes como salidas GPIO y realiza un parpadeo del LED en verde tres veces como indicador visual
 * de la inicialización.
 * 
 * @authors David Martinez Henares
 * @email: thpuppetmaster@gmail.com
 * @universidad: UPV-EHU
 *
 * @ingroup driver/gpio
 * @{
 *
 * @tipo: ESP-IDF app
 */ 


#include "init_gpio.h"

static const char* TAG_gpio = "GPIO";





/**
 * @brief Inicializa el LED RGB
 */

esp_err_t init_led()
{

    gpio_reset_pin(LED_PIN_R);
    gpio_reset_pin(LED_PIN_G);
    gpio_reset_pin(LED_PIN_B);

    gpio_set_direction(LED_PIN_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_G, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN_B, GPIO_MODE_OUTPUT);

    for (size_t i = 0; i < 3; i++)
    {
        gpio_set_level(LED_PIN_R, true);
        gpio_set_level(LED_PIN_G, true);
        gpio_set_level(LED_PIN_B, true);
        vTaskDelay(pdMS_TO_TICKS(DELAY_INIT_GPIO));
        gpio_set_level(LED_PIN_R, false);
        gpio_set_level(LED_PIN_G, false);
        gpio_set_level(LED_PIN_B, false);
        vTaskDelay(pdMS_TO_TICKS(DELAY_INIT_GPIO));
    }

    ESP_LOGI(TAG_gpio, "init_led OK...");

    return ESP_OK;
}