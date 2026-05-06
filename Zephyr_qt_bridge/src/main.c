#include <zephyr/kernel.h>
#include <zephyr/device.h>
<<<<<<< HEAD
#include <zephyr/random/random.h>
#include <stdio.h>
#include <zephyr/ipc/rpmsg_service.h>

#define ENDPOINT_NAME "rpmsg-client"

/* Global variables for the endpoint */
static int endpoint_id;
static bool bound = false;

/* Callback */
int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
    return RPMSG_SUCCESS;
}

/* Callback: when RPMsg is ready*/
void rpmsg_service_unbind(struct rpmsg_endpoint *ept)
{
    bound = false;
}

int main(void)
{
    char tx_buf[128];
    int ret;

    printk("Inizialization RPMsg Service...\n");

    endpoint_id = rpmsg_service_register_endpoint(ENDPOINT_NAME, rpmsg_recv_callback);
    
    if (endpoint_id < 0) {
        printk("Error: %d\n", endpoint_id);
        return 0;
    }


    while (1) {
        float temperature = (float)(sys_rand32_get() % 701) / 10.0f - 20.0f;
        float humidity    = (float)(sys_rand32_get() % 701) / 10.0f + 30.0f;
        float pressure    = (float)(sys_rand32_get() % 3501) / 10.0f + 900.0f;
        float airQuality  = (float)(sys_rand32_get() % 7001) / 10.0f;
        float light       = (float)(sys_rand32_get() % 70001) / 10.0f;

        int len = snprintf(tx_buf, sizeof(tx_buf), "DATA|%.1f|%.1f|%.1f|%.1f|%.1f\n", 
                          (double)temperature, (double)humidity, (double)pressure, 
                          (double)airQuality, (double)light);

        /* Send via RPMsg*/
        ret = rpmsg_service_send(endpoint_id, tx_buf, len);

        if (ret < 0) {
            printk("Error (%d)\n", ret);
        } else {
            printk("RPMsg Sent: %s\n", tx_buf);
        }

        k_sleep(K_SECONDS(2));
    }

    return 0;
}
=======
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


>>>>>>> 07c14b93bb730c8b3ce93aa8e57a1c531f380ac1
