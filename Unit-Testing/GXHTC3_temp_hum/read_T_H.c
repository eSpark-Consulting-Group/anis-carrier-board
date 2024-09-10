#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define I2C_DEVICE_ADDR 0x70 // GXHTC3 I2C address

#define CMD_SLEEP  0xB098
#define CMD_WAKEUP 0x3517
#define CMD_MEASURE_TEMP_FIRST 0x7CA2


// Function to convert raw humidity data to %RH
float convert_humidity(uint16_t raw_humidity) {
    return 100.0f * ((float)raw_humidity / 65536.0f);
}

// Function to convert raw temperature data to degrees Celsius
float convert_temperature(uint16_t raw_temperature) {
    return -45.0f + 175.0f * ((float)raw_temperature / 65536.0f);
}

// Send a 16-bit command to the sensor
int send_command(int file, uint16_t command) {
    uint8_t buf[2];
    buf[0] = (command >> 8) & 0xFF;
    buf[1] = command & 0xFF;

    if (write(file, buf, 2) != 2) {
        perror("Failed to write command to sensor");
        return -1;
    }
    return 0;
}

int main() {
    int file;
    const char *i2c_device = "/dev/i2c-5"; // Replace with your I2C device

    // Open the I2C device
    if ((file = open(i2c_device, O_RDWR)) < 0) {
        perror("Failed to open the I2C bus");
        exit(1);
    }

    // Specify the I2C device address
    if (ioctl(file, I2C_SLAVE, I2C_DEVICE_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }

    // Wake up the sensor
    if (send_command(file, CMD_WAKEUP) != 0) {
        close(file);
        exit(1);
    }

    // Sleep to allow the sensor to wake up
    usleep(2000); // 2ms wake-up time

    // Send measurement command (temperature first, normal mode, clock stretching enabled)
    if (send_command(file, CMD_MEASURE_TEMP_FIRST) != 0) {
        close(file);
        exit(1);
    }

    // Sleep to allow the sensor to perform the measurement
    usleep(10000); // 10ms measurement time

    // Read 4 bytes (temperature and humidity data)
    uint8_t data[4];
    if (read(file, data, 4) != 4) {
        perror("Failed to read data from sensor");
        close(file);
        exit(1);
    }

    // Combine the bytes to get the raw temperature and humidity
    uint16_t raw_temperature = (data[0] << 8) | data[1];
    uint16_t raw_humidity = (data[2] << 8) | data[3];
    
    float humidity = convert_humidity(raw_humidity);
    float temperature = convert_temperature(raw_temperature);

    // Print the raw data (convert it as necessary based on the sensor datasheet)
    printf("Relative Humidity: %.2f%%\n", humidity);
    printf("Temperature: %.2f`C\n", temperature);

    // Put the sensor back to sleep
    if (send_command(file, CMD_SLEEP) != 0) {
        close(file);
        exit(1);
    }

    // Close the I2C file
    close(file);

    return 0;
}
