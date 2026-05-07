/* Necessary libraries for kernel functions and IPC*/
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/random/random.h>
#include <stdio.h>
#include <zephyr/ipc/rpmsg_service.h>

/*define a name for the communication channel*/
#define ENDPOINT_NAME "rpmsg-client"
static int endpoint_id;

/* From dashboard to sensor (currently unused but required) */
int rpmsg_recv_callback(struct rpmsg_endpoint *myEndpoint, void *data, size_t len, uint32_t src, void *priv)
{
    return RPMSG_SUCCESS;
}

int main(void)
{
    char message_buffer[128];
    int check_value;

    printk("Zephyr Dashboard Bridge Start\n");

    /* register the endpoint to start the communication service*/
    endpoint_id = rpmsg_service_register_endpoint(ENDPOINT_NAME, rpmsg_recv_callback);
    
    /*Check if the initialization was successful*/
    if (endpoint_id < 0) {
        printk("Error: %d\n", endpoint_id);
    }

    /* infinite loop to simulate real-time sensor monitoring*/
    while (1) {
        /* generate random values */
        float temperature = (float)(sys_rand32_get() % 701) / 10.0f - 20.0f;
        float humidity    = (float)(sys_rand32_get() % 701) / 10.0f + 30.0f;
        float pressure    = (float)(sys_rand32_get() % 3501) / 10.0f + 900.0f;
        float airQuality  = (float)(sys_rand32_get() % 7001) / 10.0f;
        float light       = (float)(sys_rand32_get() % 70001) / 10.0f;

        /* format the data into a string*/
        int len = snprintf(message_buffer, sizeof(message_buffer), "DATA|%.1f|%.1f|%.1f|%.1f|%.1f\n", 
                          (double)temperature, (double)humidity, (double)pressure, 
                          (double)airQuality, (double)light);

        /*print the string to the serial console for python bridge*/
        printk("%s", message_buffer);

        if (endpoint_id >= 0) {
            /* forward the message through the RPMsg channel*/
            check_value = rpmsg_service_send(endpoint_id, message_buffer, len);
            if (check_value < 0) {
            }
        }

        k_sleep(K_SECONDS(2));
    }

    return 0;
}