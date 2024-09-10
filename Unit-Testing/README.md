# Initial Setup for Carrier Board

This document provides the steps to perform the initial setup after uploading and booting the custom Ubuntu-based image on your Carrirer Board.

## 1. System Update and Upgrade

After booting up the system, it's essential to update and upgrade the package lists and installed packages to ensure that you have the latest security updates and software versions.

Run the following commands to update and upgrade the system:

```bash
sudo apt update
sudo apt upgrade -y
```

## 2. Install Essential Libraries and Tools
Once the system is updated, you need to install some essential tools and libraries that are commonly required for embedded system development.

**2.1. Install minicom for Serial Communication**

`minicom` is a serial communication tool that can be used for interacting with other hardware over serial connections.

Install `minicom` using the following command:
```bash
sudo apt install minicom -y
```

**2.1. Install GCC for C/C++ Compilation**

The GNU Compiler Collection (GCC) is essential for compiling C/C++ files. You can install GCC using:
```bash
sudo apt install build-essential -y
```

**2.6. Install Networking Tools**

For debugging or configuring network interfaces, it's helpful to have networking tools such as net-tools and curl:
```bash
sudo apt install net-tools curl -y
```

**2.7. Install Other Common Utilities**

Here are some other common utilities you might need:

- Vim/ Nano (Text Editors):
```bash
sudo apt install vim nano -y
```

- I2C/SPI Tools (For working with I2C or SPI devices):
```bash
sudo apt install i2c-tools -y
```

