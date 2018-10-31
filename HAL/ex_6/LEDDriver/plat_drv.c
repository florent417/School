#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>

#define LED_MAJOR 3
#define LED_MINOR 0
#define LED_NBR_MINORS 1


MODULE_LICENSE("GPL");
MODULE_AUTHOR("HALboys420");
MODULE_DESCRIPTION("Writes to the device (/dev/led3) turns LED on/off");

static unsigned int gpioLED = 21;
static int devno;
struct cdev gpio21_cdev;
struct file_operations LED_fops;

static int mygpio_21_init(void)
{
  //Error handling variable
  int err;
// Request GPIO
  err = gpio_request(gpioLED, "LED");
  if(err < 0)
    goto err_exit;
// Set GPIO direction (in or out)
  gpio_direction_input(gpioLED);
// Make device no (vælg - Enten bruger I statisk eller også
// bruger I dynamisk major/minor nummer allokering)
  devno = MKDEV(LED_MAJOR, LED_MINOR);
// Register Device
  err = register_chrdev_region(devno, LED_NBR_MINORS, "LED3");
  if(err < 0)
    goto err_free_buff;
// Cdev Init
  cdev_init(&gpio21_cdev, &LED_fops);
// Add Cdev
  err = cdev_add(&gpio21_cdev, devno, LED_NBR_MINORS);
  if(err < 0)
    goto err_dev_unregister;

  printk(KERN_ALERT "LED-Module-init");
  return 0;

  err_dev_unregister:
    unregister_chrdev_region(devno, LED_NBR_MINORS);
  err_free_buff:
    gpio_free(gpioLED);
  err_exit:
    return err;
}

int mygpio_21_open(struct inode *inode, struct file *filep)
{
  int major, minor;
  major = MAJOR(inode->i_rdev);
  minor = MINOR(inode->i_rdev);
  printk("Opening MyGpio Device LED3 [major], [minor]: %i, %i\n", major, minor);

  return 0;
}

ssize_t mygpio_read(struct file *filep, char __user *buf,
            size_t count, loff_t *f_pos)
 {
 // Hvilke trin er det der skal udføres?
 int gpio_value = gpio_get_value(gpioLED);
 char my_buf[12];
 sprintf(my_buf,"%i",gpio_value);

 int my_buf_len = strlen(my_buf)+1;
 my_buf_len = (my_buf_len > count ? count : my_buf_len);
 unsigned long n = copy_to_user(buf, my_buf,my_buf_len);
 n =n;
 // Hint konvertering fra int til string
 //kan gøres via sprintf() - antagelsen er at det er
 //strenge der sendes til og fra user space. Det gør
 //debugging lettere.

 *f_pos += my_buf_len;
 return my_buf_len;
 }

int mygpio_21_release(struct inode *inode, struct file *filep)
{
 int minor, major;

 major = MAJOR(inode->i_rdev);
 minor = MINOR(inode->i_rdev);
 printk("Closing/Releasing MyGpio Device LED3 [major], [minor]: %i, %i\n", major, minor);

 return 0;
}

static void mygpio_21_exit(void)
{
// Delete Cdevl
  cdev_del(&gpio21_cdev);
// Unregister Device
  unregister_chrdev_region(devno, LED_NBR_MINORS);
// Free GPIO
  gpio_free(gpioLED);

  printk(KERN_ALERT "LED-Module-release");
}

struct file_operations LED_fops = {
  //.write =    LED_write,
  .owner =    THIS_MODULE,
  .open =    mygpio_21_open,
  .release =  mygpio_21_release,
};

module_init(mygpio_21_init)
module_exit(mygpio_21_exit)
