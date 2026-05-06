#include <zephyr/kernel.h>
#include <zephyr/device.h>
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