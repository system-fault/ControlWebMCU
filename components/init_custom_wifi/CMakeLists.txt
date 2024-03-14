idf_component_register(SRCS "init_custom_wifi.c"
                    INCLUDE_DIRS "include"
                    REQUIRES "esp_system" "esp_system" "esp_wifi" "esp_event" "nvs_flash")
