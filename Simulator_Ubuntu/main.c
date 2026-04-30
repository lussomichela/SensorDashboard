#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <fcntl.h>

#pragma pack(push, 1)
typedef struct {
    float temperature;
    float humidity;
    float pressure;
    float airQuality;
    float lightLevel;
} SensorPayload;
#pragma pack(pop)

int main() {
    srand(time(NULL));

    int pipe = open("/dev/ttyS0", O_RDWR); 
    if (pipe <0) { 
        perror("ERROR");
        return 1; 
    }

    printf("Waiting for Master to be READY \n");


    uint8_t handshake = 0;
    while (handshake != 1) {
            read(pipe, &handshake, 1);
            sleep(2); 
        
    }

    printf("Master is READY \n");

    SensorPayload data;
    while (1) {
        data.temperature = (float)(rand() % 701) / 10.0f - 20.0f;
        data.humidity = (float)(rand() % 701) / 10.0f + 30.0f;
        data.pressure = (float)(rand() % 3501) / 10.0f + 900.0f;
        data.airQuality = (float)(rand() % 7001) / 10.0f;
        data.lightLevel = (float)(rand() % 70001) / 10.0f;

        write(pipe, &data, sizeof(SensorPayload));

        printf("Dashboard: temperature: %.1f   | humidity: %.1f   | pressure: %.1f   | Air Quality: %.1f   | Light Level: %.1f\n", data.temperature, data.humidity, data.pressure, data.airQuality, data.lightLevel);
        sleep(2);
    }

    close(pipe);
    return 0;
}