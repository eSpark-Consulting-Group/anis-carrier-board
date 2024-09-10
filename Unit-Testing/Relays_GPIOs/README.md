# TCA6424ARGJR Relay and GPIO Control

This document guides you through controlling relays and GPIOs connected to the TCA6424ARGJR I/O expander. The relays are connected to Port 0, and GPIOs are connected to Ports 1 and 2. The TCA6424ARGJR is connected to the I2C3 bus with address `0x22`.

## Prerequisites

- Ensure that the TCA6424ARGJR is properly connected to the I2C3 bus.
- Install `i2c-tools` to scan the I2C bus and control the I/O expander.

## 1. Check I2C Address

Before controlling the relays and GPIOs, confirm that the TCA6424ARGJR is detected on the I2C3 bus at address `0x22`. Use the following command to scan the I2C3 bus:

```bash
i2cdetect -y 3
```
You should see 0x22 listed, indicating that the device is properly connected.

## 2. Configure Ports for Output

Ports 0, 1, and 2 need to be configured as output ports before you can control the relays and GPIOs. Each port has a specific configuration register.

- Port 0 (Relays): Register 0x0C
- Port 1 (GPIOs): Register 0x0D
- Port 2 (GPIOs): Register 0x0E

To configure these ports as outputs (all bits set to 0), run the following commands:

## 3. Control Relays (Port 0)

The relays are connected to Port 0. You can control each relay by writing to the output register 0x04. Setting a bit to 1 will turn the corresponding relay ON, and setting it to 0 will turn it OFF.

For example, to turn ON the relay connected to the first bit and turn OFF all others, run:
```bash
i2cset -y 3 0x22 0x04 0x01
```

To turn all relays ON:
```
i2cset -y 3 0x22 0x04 0xFF
```

To turn all relays OFF:
```
i2cset -y 3 0x22 0x04 0x00
```

## 4. Control GPIOs (Ports 1 and 2)
You can control the GPIOs connected to Ports 1 and 2 by writing to the output registers 0x05 (Port 1) and 0x06 (Port 2).

- Port 1 (Register 0x05)
- Port 2 (Register 0x06)

To set specific GPIOs HIGH or LOW, you can use the following commands. For example, to set all GPIOs on Port 1 to HIGH:
```
i2cset -y 3 0x22 0x05 0xFF
```

To set all GPIOs on Port 2 to LOW:
```
i2cset -y 3 0x22 0x06 0x00
```
You can control individual bits similarly by changing the byte values.

## Note
The TCA6424ARGJR datasheet is also attached for further details on controlling GPIOs and relays, including advanced configurations and register descriptions.
