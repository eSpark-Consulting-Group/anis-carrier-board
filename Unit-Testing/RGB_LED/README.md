# RGB LED Testing with PWM Driver

This guide explains how to test an RGB LED strip controlled by WS2812B using a custom kernel module driver. We'll be placing the driver file `pwm-ws2812b.c` in the `/kernel/drivers/pwm` directory, updating the necessary configuration files, and then building and loading the image. After booting up, you'll be able to control the RGB LED by passing color codes.

## Steps to Build and Test

### 1. Add the Kernel Module

1. **Place the driver file**  
   Place the `pwm-ws2812b.c` file in the following directory:
   ```bash
   /kernel/drivers/pwm

2. **Update Makefile**  
   In the `/kernel/drivers/pwm/Makefile`, add the following line to include the new driver:
   ```bash
   obj-$(CONFIG_PWM_WS2812B) += pwm-ws2812b.o

3. **Update Kconfig**  
   In the `/kernel/drivers/pwm/Kconfig` file, add the following to define the driver configuration::
   ```bash
   config PWM_WS2812B
    tristate "PWM driver for WS2812B RGB LEDs"
    default y
    help
      This driver controls WS2812B LEDs using the PWM interface.

4. **Build the Kernel** 
    Build the kernel according to the steps defined in the guide [Core-3568J](https://wiki.t-firefly.com/en/Core-3568J/linux_compile.html#:~:text=build.sh%20uboot-,kernel,-Notice%EF%BC%9AFirefly%20kernel)

5. **Boot the New Kernel**
    Reboot the system with the newly built kernel image.

6. **Set Device Permissions**
    After the system boots up, you'll need to set the necessary permissions to access the WS2812B device file. Run the following command:
    ```bash
    sudo chmod 666 /dev/ws2812b

7. **Test RGB LED**
    To control the RGB LED, you can pass a color code to the device file using the following command:
    ```bash
    echo -ne '\x00\xFF\x00' > /dev/ws2812b
    ```

    In this example, \x00\xFF\x00 represents the RGB value, where:

    - \x00 is the red component (0% brightness).
    - \xFF is the green component (100% brightness).
    - \x00 is the blue component (0% brightness).
    
Feel free to change these values to control the color output of the LED.