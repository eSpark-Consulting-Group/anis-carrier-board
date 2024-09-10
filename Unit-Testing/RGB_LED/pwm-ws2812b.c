#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pwm.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define DEVICE_NAME "ws2812b"
#define CLASS_NAME  "ws2812b_class"

static struct class *ws2812b_class;
static struct device *ws2812b_device;
static struct pwm_device *pwm0 = NULL;
static int major_number;
static int period_ns = 1250;   // PWM period in nanoseconds for WS2812B (~800kHz)
static int t1h_ns = 900;       // High time for a '1' bit
static int t0h_ns = 400;       // High time for a '0' bit

// Function to send a single bit to the WS2812B LED
static void ws2812b_send_bit(int bit) {
    if (bit == 1) {
        pwm_config(pwm0, t0h_ns, period_ns);
    } else {
        pwm_config(pwm0, t1h_ns, period_ns);
    }
    
}

// Function to send a full byte (8 bits) to the WS2812B LED
static void ws2812b_send_byte(uint8_t byte) {
    int i;
    for (i = 2; i >= 0; i--) {
        ws2812b_send_bit((byte >> i) & 0x1);
    }
}

// Function to send an RGB value (3 bytes)
static void ws2812b_send_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    // WS2812B expects Green, Red, Blue (GRB) format

	pwm_config(pwm0, period_ns, period_ns);
	pwm_enable(pwm0);
	udelay(1);

    
    	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	pwm_config(pwm0, period_ns, period_ns);
	udelay(1);

	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	pwm_config(pwm0, period_ns, period_ns);
	udelay(1);

	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	pwm_config(pwm0, period_ns, period_ns);
	udelay(1);

	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	pwm_config(pwm0, period_ns, period_ns);
	udelay(1);

	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	udelay(1);

	ws2812b_send_byte(green);
    	ws2812b_send_byte(red);
    	ws2812b_send_byte(blue);
	udelay(60);


	pwm_config(pwm0, period_ns, period_ns);


}

// Character device write function to control the LED strip
static ssize_t ws2812b_write(struct file *file, const char *buffer, size_t len, loff_t *offset) {
    uint8_t rgb[3];

    // Copy RGB values from user space
    if (copy_from_user(rgb, buffer, sizeof(rgb))) {
        return -EFAULT;
    }

    
    // Send RGB values to the WS2812B LEDs
    ws2812b_send_rgb(rgb[0], rgb[1], rgb[2]);

    // Return the number of bytes written
    return sizeof(rgb);
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = ws2812b_write,
};

// Module initialization function
static int __init ws2812b_init(void) {
    printk(KERN_INFO "WS2812B: module initialization\n");
    // Register a character device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "WS2812B failed to register a major number\n");
        return major_number;
    }

    // Create the device class
    ws2812b_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(ws2812b_class)) {
        printk(KERN_INFO "WS2812B: create class error\n");
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(ws2812b_class);
    }

    // Create the device
    ws2812b_device = device_create(ws2812b_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(ws2812b_device)) {
        printk(KERN_INFO "WS2812B: create device error\n");
        class_destroy(ws2812b_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        return PTR_ERR(ws2812b_device);
    }
    
    // Initialize PWM
    pwm0 = pwm_request(0, "ws2812b_pwm");
    if (IS_ERR(pwm0)) {
	printk(KERN_ALERT "WS2812B: pwm error: %ld\n", PTR_ERR(pwm0));
	device_destroy(ws2812b_class, MKDEV(major_number, 0));
	class_destroy(ws2812b_class);
	unregister_chrdev(major_number, DEVICE_NAME);
	return PTR_ERR(pwm0);
    }
    

    printk(KERN_INFO "WS2812B: module loaded\n");
    return 0;
}

// Module exit function
static void __exit ws2812b_exit(void) {
    pwm_disable(pwm0);
    pwm_free(pwm0);

    device_destroy(ws2812b_class, MKDEV(major_number, 0));
    class_destroy(ws2812b_class);
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "WS2812B: module unloaded\n");
}

module_init(ws2812b_init);
module_exit(ws2812b_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Waqar Khanzada");
MODULE_DESCRIPTION("A kernel module to control WS2812B LEDs using PWM");
MODULE_VERSION("0.1");