#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/module.h>

#define SW_MAJOR 2
#define SW_MINOR 0
#define SW_NBR_MINORS 1


MODULE_LICENSE("GPL");
MODULE_AUTHOR("HALboys420");
MODULE_DESCRIPTION("Returns the status of SW2(pressed/!pressed)");

static unsigned int gpioButton = 16;
static int devno;
struct cdev gpio16_cdev;
struct file_operations SW_fops;

static int mygpio_16_init(void)
{
  //Error handling variable
  int err;
// Request GPIO
  err = gpio_request(gpioButton, "Switch");
  if(err < 0)
    goto err_exit;
// Set GPIO direction (in or out)
  gpio_direction_input(gpioButton);
// Make device no (vælg - Enten bruger I statisk eller også
// bruger I dynamisk major/minor nummer allokering)
  devno = MKDEV(SW_MAJOR, SW_MINOR);
// Register Device
  err = register_chrdev_region(devno, SW_NBR_MINORS, "SW2");
  if(err < 0)
    goto err_free_buff;
// Cdev Init
  cdev_init(&gpio16_cdev, &SW_fops);
// Add Cdev
  err = cdev_add(&gpio16_cdev, devno, SW_NBR_MINORS);
  if(err < 0)
    goto err_dev_unregister;

  printk(KERN_ALERT "SW-Module-init");
  return 0;

  err_dev_unregister:
    unregister_chrdev_region(devno, SW_NBR_MINORS);
  err_free_buff:
    gpio_free(gpioButton);
  err_exit:
    return err;
}

int mygpio_16_open(struct inode *inode, struct file *filep)
{
  int major, minor;
  major = MAJOR(inode->i_rdev);
  minor = MINOR(inode->i_rdev);
  printk("Opening MyGpio Device SW2 [major], [minor]: %i, %i\n", major, minor);

  return 0;
}

int mygpio_16_release(struct inode *inode, struct file *filep)
{
 int minor, major;

 major = MAJOR(inode->i_rdev);
 minor = MINOR(inode->i_rdev);
 printk("Closing/Releasing MyGpio SW2 Device [major], [minor]: %i, %i\n", major, minor);

 return 0;
}

static void mygpio_16_exit(void)
{
// Delete Cdevl
  cdev_del(&gpio16_cdev);
// Unregister Device
  unregister_chrdev_region(devno, SW_NBR_MINORS);
// Free GPIO
  gpio_free(gpioButton);

  printk(KERN_ALERT "SW-Module-release");
}

struct file_operations SW_fops = {
  //.write =    SW_write,
  .owner = THIS_MODULE,
  .open =    mygpio_16_open,
  .release =  mygpio_16_release,
};

module_init(mygpio_16_init)
module_exit(mygpio_16_exit)
