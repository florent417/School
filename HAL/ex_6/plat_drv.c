#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define SW_MAJOR 2
#define SW_MINOR 0
#define SW_NBR_MINORS 1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HALboys420");
MODULE_DESCRIPTION("Returns the status of SW2(pressed/!pressed)");

//Driver
static struct platform_driver SW_plat_drv_driver;
static struct class *SW_plat_drv_class;

static unsigned int gpioButton = 16;
static int devno;
struct cdev gpio16_cdev;
struct file_operations SW_fops;

static int mygpio_16_init(void)
{
  //Error handling variable
  int err = 0;
// Register Device
  err = alloc_chrdev_region(&devno,SW_MINOR, SW_NBR_MINORS, "SW2");
  if(err < 0)
    goto err_exit;
// Cdev Init
  cdev_init(&gpio16_cdev, &SW_fops);
// Add Cdev
  err = cdev_add(&gpio16_cdev, devno, SW_NBR_MINORS);
  if(err < 0)
    goto err_dev_unregister;

  //Sys Fs class
  SW_plat_drv_class=class_create(THIS_MODULE,"SW_plat_drv_class");
  if(IS_ERR(SW_plat_drv_class))
    goto err_cdev_delete;
  //Register driver
  err = platform_driver_register(&SW_plat_drv_driver);
  if(err < 0)
    goto err_class_destroy;

  printk(KERN_ALERT "SW-Module-init\n");
  return 0;

  err_class_destroy:
    class_destroy(SW_plat_drv_class);
  err_cdev_delete:
    cdev_del(&gpio16_cdev);
  err_dev_unregister:
    unregister_chrdev_region(devno, SW_NBR_MINORS);
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

/*************************** Opgave 6 *******************************************
***************** Hot pluggable device drivers *******************************/
const int minor_to_use = 1;
static unsigned int gpioButton2 = 12;

static int mygpio_16_p_drv_probe(struct platform_device *pdev)
{
  int err = 0;
  struct device *gpio_device;
  printk(KERN_DEBUG "Hello from probe\n");

  // Request GPIO
  err = gpio_request(gpioButton2, "SW0_p_dev_gpio");
  if(err < 0)
    goto err_exit;

  // Set GPIO direction (in or out)
  err = gpio_direction_input(gpioButton2);
  if(err<0)
    goto err_free_buff;

  // Dynamically add Device
  gpio_device = device_create(SW_plat_drv_class, NULL, MKDEV(MAJOR(devno),minor_to_use)
                              , NULL, "mygpio_%d", gpioButton2);

  if(IS_ERR(gpio_device))
  {
    printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
    err = -EFAULT;
    goto err_free_buff;

  }

  printk(KERN_ALERT "Created /dev/my_gpio_%d with MAJOR %d, and minor %d",
          gpioButton2, MAJOR(devno), minor_to_use);
  return 0;

  err_free_buff:
    gpio_free(gpioButton);
  err_exit:
    return err;
}

ssize_t mygpio_16_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
  int gpio_val = gpio_get_value(gpioButton);
  char internal_buffer[50];
  sprintf(internal_buffer, "%i", gpio_val);

  int internal_buffer_len = strlen(internal_buffer) + 1;
  internal_buffer_len = internal_buffer_len > count ? count : internal_buffer_len;
  unsigned long n = copy_to_user(buf, internal_buffer, internal_buffer_len);
  n = n; // To stop warnings of unused variable.

  *f_pos += internal_buffer_len;
  return internal_buffer_len;
}

static int mygpio_16_p_drv_remove(struct platform_device *pdev)
{
  printk(KERN_ALERT "Removing device %s\n", pdev->name);

  gpio_free(gpioButton2);

  device_destroy(SW_plat_drv_class, MKDEV(MAJOR(devno),minor_to_use));
  return 0;
}

static const struct of_device_id mygpio_16_p_de_match[] =
{
  { .compatible = "ase, plat_drv", }, {},
};

static struct platform_driver SW_plat_drv_driver =
{
    .probe = mygpio_16_p_drv_probe,
    .remove = mygpio_16_p_drv_remove,
    .driver =
          {
            .name = "mygpio_16_SW",
            .of_match_table = mygpio_16_p_de_match,
            .owner = THIS_MODULE,
          }
};

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
  printk(KERN_ALERT "SW-Module-release\n");
// Unregister platform_
  platform_driver_unregister(&SW_plat_drv_driver);
//Destroy class
  class_destroy(SW_plat_drv_class);
// Delete Cdevl
  cdev_del(&gpio16_cdev);
// Unregister Device
  unregister_chrdev_region(devno, SW_NBR_MINORS);
// Free GPIO
  //gpio_free(gpioButton);
}

struct file_operations SW_fops = {
  //.write =    SW_write,
  .owner = THIS_MODULE,
  .open =    mygpio_16_open,
  .release =  mygpio_16_release,
};

module_init(mygpio_16_init)
module_exit(mygpio_16_exit)
