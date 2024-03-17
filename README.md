| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# Sistema de Monitorización con ESP32 y BMP280

Este proyecto implementa un sistema de monitorización de datos de presión y temperatura utilizando un microcontrolador ESP32 y un sensor BMP280. El sistema está diseñado para ejecutarse en el framework ESP-IDF y utiliza una conexión Wi-Fi para enviar los datos a un servidor web.

## Características

- **Lectura de Datos:** Utiliza el sensor BMP280 para leer datos de presión y temperatura con precisión.
- **Control de LEDs RGB:** Proporciona indicadores visuales utilizando LEDs RGB para mostrar el estado del sistema.
- **Envío de Datos:** Utiliza solicitudes HTTP para enviar los datos de presión y temperatura al servidor web.
- **Gestión de Wi-Fi:** Implementa la gestión de la conexión Wi-Fi para establecer la comunicación con el servidor.

## Configuración del Proyecto

### Requisitos

- **Microcontrolador ESP32:** Se requiere un microcontrolador ESP32 compatible con el framework ESP-IDF.
- **Sensor BMP280:** El sensor BMP280 debe estar conectado al ESP32 para la lectura de datos.
- **Conexión a Internet:** Se necesita acceso a una red Wi-Fi para enviar los datos al servidor web.

### Instalación y Configuración

1. **Clonar el Repositorio:** Clona este repositorio en tu entorno de desarrollo local utilizando el siguiente comando:

    ```
    git clone [https://tu-repositorio.git](https://github.com/system-fault/ControlWebMCU)
    ```

2. **Configurar `sdkconfig`:** Asegúrate de configurar el archivo `sdkconfig` con la configuración específica de tu proyecto, incluidas las credenciales de la red Wi-Fi y la dirección del servidor web.

3. **Compilar y Cargar:** Compila el firmware utilizando el framework ESP-IDF y carga el programa resultante en tu microcontrolador ESP32.

### Configuraciones Adicionales

- **Archivos de Configuración:** Los archivos `mydata_custom_HTTP_client.h` y `mydata_init_custom_wifi.h` son archivos de configuración personal y no son necesarios, ya que las configuraciones pueden realizarse directamente en los archivos `.c` de las respectivas librerías.

## Uso

1. **Conexión del Hardware:** Conecta el ESP32 a una fuente de alimentación y asegúrate de que esté conectado a la red Wi-Fi configurada.
   
2. **Ejecución del Sistema:** El sistema se iniciará automáticamente y comenzará a leer los datos de presión y temperatura utilizando el sensor BMP280.

3. **Visualización de Datos:** Observa el estado del sistema a través de los LEDs RGB, que proporcionan indicadores visuales según las lecturas de presión y temperatura.

4. **Envío de Datos:** Los datos de presión y temperatura se enviarán automáticamente al servidor web a través de solicitudes HTTP, donde pueden ser procesados y almacenados según sea necesario.

## Contribución y Soporte

- **Contribuciones:** Las contribuciones al proyecto son bienvenidas. Si tienes ideas para mejorar este proyecto, no dudes en abrir un issue o enviar un pull request con tus sugerencias.
  
- **Soporte:** Para obtener más información sobre este proyecto o para recibir soporte técnico, ponte en contacto con David a través de Github.

## Licencia

Este proyecto está licenciado bajo la [Licencia MIT](LICENSE).







