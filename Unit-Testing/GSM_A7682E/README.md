# GSM Module A7682E Testing Guide

This document outlines the steps to test the GSM module A7682E connected to UART5 using Minicom and some basic AT commands for initial testing.

## 1. Prerequisites

- Ensure the GSM module A7682E is properly connected to UART5.
- Install `minicom` if not already installed:

```bash
sudo apt update
sudo apt install minicom
```

## 2. Connect to the GSM Module

To communicate with the GSM module over UART5, open Minicom with the correct serial port settings:
```
sudo minicom -D /dev/ttyS5
```

**Configuring Minicom**

To ensure proper communication, configure Minicom as follows:

1. Press Ctrl + A then Z to open the Minicom menu.
2. Press O to configure Minicom settings.
3. Navigate to Serial port setup and set:
    - Serial Device: /dev/ttyS4
    - Bps/Par/Bits: 115200 8N1 (115200 baud rate, 8 data bits, no parity, 1 stop bit)
4. Save the configuration and exit.

## 3. Basic AT Commands for Testing

Once connected, you can use the following basic AT commands to test the GSM module:

- Check Module Connection:
```
AT
```
You should receive an OK response, indicating that the module is responding.

- Check SIM Status:
```
AT+CPIN?
```
This will return the SIM status. If a SIM is inserted and ready, it should return `+CPIN: READY`.

- Check Signal Strength:
```
AT+CPIN?
```
This will return the signal quality. A response like `+CSQ: 15,99` means a signal strength of 15 (out of 31).

- Check Network Registration:

```
AT+CREG?
```
This command checks the module's network registration status. A response of `+CREG: 0,1` means it is registered on the network.

## 4. Further Testing

For more advanced testing, including sending SMS, establishing data connections, and voice calls, refer to the complete AT command guide provided by SIMCOM:

[SIMCOM A7682E AT Commands Guide](http://df.mchobby.be/HAT-GSM-4G-A7682E/A76XX_Series_AT_Command_Manual_V1_04.pdf)