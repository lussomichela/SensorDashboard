#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/random/random.h>
#include <stdint.h>

#include <stdint.h>

#pragma pack(1)
typedef struct {
    float temperature;
    float humidity;
    float pressure;
    float airQuality;
    float lightLevel;
} SensorPayload;
#pragma pack()

int main(void)
{
    const struct device *uart_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    if (!device_is_ready(uart_dev)) {
        return 0; 
    }
        

    SensorPayload data;

    while (1) {

        data.temperature = (float)(sys_rand32_get() % 701) / 10.0f - 20.0f;
        data.humidity    = (float)(sys_rand32_get() % 701) / 10.0f + 30.0f;
        data.pressure    = (float)(sys_rand32_get() % 3501) / 10.0f + 900.0f;
        data.airQuality  = (float)(sys_rand32_get() % 7001) / 10.0f;
        data.lightLevel  = (float)(sys_rand32_get() % 70001) / 10.0f;

 
        
        printk("DATA|%.1f|%.1f|%.1f|%.1f|%.1f\n", data.temperature, data.humidity, data.pressure, data.airQuality, data.lightLevel);


        uint8_t *ptr = (uint8_t *)&data;
        for (int i = 0; i < sizeof(SensorPayload); i++) {
            uart_poll_out(uart_dev, ptr[i]);
        }

        k_sleep(K_MSEC(10000));
    }

    return 0;
}


