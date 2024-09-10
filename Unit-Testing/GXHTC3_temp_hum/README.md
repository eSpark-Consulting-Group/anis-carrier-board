# GXHTC3 Temperature and Humidity Sensor Setup

This guide will help you set up and retrieve data from the GXHTC3 temperature and humidity sensor using the I2C5 bus on an embedded system.

## Prerequisites

- Ensure that the GXHTC3 sensor is properly connected to the I2C5 bus.
- Install the necessary tools (e.g., `i2c-tools` and `gcc`).

## 1. Check I2C Address

Before running any code, confirm that the sensor is detected on the I2C5 bus at address `0x70`. Run the following command to scan the I2C5 bus:

```bash
sudo i2cdetect -y 5
```
You should see the address 0x70 listed in the output, indicating that the sensor is correctly connected.

## 2. Compile the C Program

The file `read_T_H.c` contains the code to read temperature and humidity values from the GXHTC3 sensor. To compile the program, use the following command:
```bash
gcc -o read read_T_H.c
```
This will compile the C code and create an executable named `read`.

## 3. Run the Program

After compiling, run the program to retrieve temperature and humidity values from the sensor:
```bash
sudo ./read
```